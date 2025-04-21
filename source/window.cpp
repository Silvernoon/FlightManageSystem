#include "window.hpp"
#include "IO.hpp"
#include "train.hpp"
#include <QMessageBox>
#include <QPushButton>
#include <vector>

#define GETITEM(r, c) ui->tableWidget->item(r, c)

// 通过正则表达式检查
bool regularCheck(const char *regular, const QString &target) {
  QRegularExpression check(regular);
  return check.match(target).hasMatch();
}

// MainWindow

MainWindow::MainWindow() : ui(new Ui::mainWindow) {
  ui->setupUi(this);
  connect(ui->add, &QPushButton::clicked, this, &MainWindow::add);
  connect(ui->list, &QPushButton::clicked, this, &MainWindow::list);
  connect(ui->query, &QPushButton::clicked, this, &MainWindow::query);
  connect(ui->sell, &QPushButton::clicked, this, &MainWindow::sell);
}

void MainWindow::add() {
  AddWindow *window = new AddWindow();
  window->exec(); // 阻塞主窗口
}
void MainWindow::list() {
  ListWindow *window = new ListWindow();
  window->exec();
}
void MainWindow::query() {
  QueryWindow *window = new QueryWindow();
  window->exec();
}
void MainWindow::sell() {
  SellWindow *window = new SellWindow();
  window->exec();
}

// AddWindow

AddWindow::AddWindow() : ui(new Ui::add) { ui->setupUi(this); }
// 传值
void AddWindow::accept() {
  // 判空
  for (int i = 0; i < 6; i++)
    if (GETITEM(0, i) == nullptr)
      return;

  // 判格式
#define text(n) GETITEM(0, n)->text()
  if (!regularCheck("^\\d{1,2}:\\d{2}$", text(TIME)))
    return;

  if (!regularCheck("[0-9]+(\\.[0-9]+)?$", text(DURATION)))
    return;

  if (!regularCheck("^[0-9]+$", text(MAX)))
    return;

  if (!regularCheck("^[0-9]+$", text(COUNT)))
    return;

  if (text(MAX).toInt() < text(COUNT).toInt())
    return;
#undef text

  Train::Table.emplace_back(ui->tableWidget);
  this->close();

  WriteAll();
}

// ListWindow

ListWindow::ListWindow(std::vector<Train> table) : ui(new Ui::list) {
  ui->setupUi(this);

  connect(ui->pushButton, &QPushButton::clicked, this, &ListWindow::book);

  ui->tableWidget->setRowCount(Train::Table.size());
  int i = 0;
  for (const Train &v : table) {
#define tt(c, u) ui->tableWidget->setItem(i, c, new QTableWidgetItem(u))
#define N2S(c) QString::number(c)

    tt(TIME, QTime::currentTime() < v.GetTime() ? v.GetTime().toString("h:mm")
                                                : "此班已发出");
    tt(START, v.GetStart());
    tt(FINAL, v.GetFinal());
    tt(DURATION, N2S(v.GetDuration()));
    tt(MAX, N2S(v.GetMax()));
    tt(COUNT, N2S(v.GetCount()));
#undef tt
#undef N2S
    i++;
  }
}

void ListWindow::book() {
  // 跳过空白
  if (ui->tableWidget->selectedItems().isEmpty())
    return;

  int id = ui->tableWidget->selectedItems()[0]->row();
  Train &key = Train::Table[id];
  if (key.AddCount()) {
    GETITEM(id, COUNT)->setText(QString::number(key.GetCount()));
    QMessageBox::information(this, "订票", "订票成功");
  } else
    QMessageBox::critical(this, "订票", "订票失败，已满");

  WriteAll();
}

// QueryWindow

QueryWindow::QueryWindow() : ui(new Ui::query) {
  ui->setupUi(this);
  connect(ui->pushButton, &QPushButton::clicked, this, &QueryWindow::showTable);
}
void QueryWindow::showTable() {
  ListWindow *window;

  const QString &text = ui->lineEdit->text();

  if (text.isEmpty())
    return;
  else if (regularCheck("^[0-9]+$", text)) {
    int id = text.toInt();
    if (id > 0 && id <= Train::Table.size())
      window = new ListWindow(Train::Query(text.toUShort() - 1));
    else
      return;
  } else
    window = new ListWindow(Train::Query(text));

  window->exec();
}

// SellWindow

SellWindow::SellWindow() : ui(new Ui::sell) {
  ui->setupUi(this);
  connect(ui->book, &QPushButton::clicked, this, &SellWindow::book);
  connect(ui->refund, &QPushButton::clicked, this, &SellWindow::refund);
}

#define WWW                                                                    \
  const QString &text = ui->lineEdit->text();                                  \
  if (text.isEmpty() || !regularCheck("^[0-9]+$", text))                       \
    return;                                                                    \
  int id = text.toInt();                                                       \
  if (id > Train::Table.size() || id < 1)                                      \
    return;                                                                    \
  Train &key = Train::Table[id - 1]

void SellWindow::book() {
  WWW;
  if (key.AddCount()) {
    QMessageBox::information(this, "订票", "订票成功");
  } else
    QMessageBox::critical(this, "订票", "订票失败，已满");

  WriteAll();
}

void SellWindow::refund() {
  WWW;
  if (key.SubCount() || QTime::currentTime() < Train::Table[id].GetTime()) {
    QMessageBox::information(this, "退票", "订票成功");
  } else
    QMessageBox::critical(this, "退票", "退票失败，无票");

  WriteAll();
}
