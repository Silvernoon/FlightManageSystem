#include "window.hpp"
#include "Flight.hpp"
#include "IO.hpp"
#include "Util.hpp"
#include <QMessageBox>
#include <QPushButton>
#include <qcontainerfwd.h>
#include <ranges>
#include <vector>

#define TEXT()

// MainWindow

MainWindow::MainWindow() : ui(new Ui::mainWindow) {
  ui->setupUi(this);
  connect(ui->add, &QPushButton::clicked, this, &MainWindow::add);
  connect(ui->query, &QPushButton::clicked, this, &MainWindow::query);
  connect(ui->sell, &QPushButton::clicked, this, &MainWindow::sell);
}

void MainWindow::add() {
  AddWindow *window = new AddWindow();
  window->exec(); // 阻塞主窗口
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
  for (int i = 0; i < 5; i++)
    if (ui->tableWidget->item(0, i) == nullptr)
      return;

  // 判格式
#define GETTEXT(n) getItemText(ui->tableWidget, 0, n)
  if (!regularCheck("^[0-9]+$", GETTEXT(MAX_CAPACITY)))
    return;

  if (!dateTryFromString(GETTEXT(DATE)).isValid())
    return;

  Flight::emplace(ui->tableWidget);
  this->close();

  WriteAll();
}

// ListWindow
// TODO: Add Passnager show
ListWindow::ListWindow(FlightPtrTable table)
    : ui(new Ui::list), m_table(table) {
  ui->setupUi(this);

  // if (isRefund == false)
  connect(ui->pushButton, &QPushButton::clicked, this, &ListWindow::showBook);
  // else {
  //   ui->pushButton->setText("退票");
  //   connect(ui->pushButton, &QPushButton::clicked, this,
  //           &ListWindow::showRefund);
  // }

  ui->tableWidget->setRowCount(Flight::table().size());
  int i = 0;
  for (const Flight *v : table) {
#define SETTEXT(column, text) setItemText(ui->tableWidget, i, column, text)
#define SET(column, item) SETTEXT(column, v->flightData().item)
#define __SETINT(column, num) SETTEXT(column, QString::number(num))
#define SETINT(column, item) __SETINT(column, v->flightData().item)

    SET(DESTINATION, destination);
    SET(FLIGHT_NUMBER, flightNumber);
    SET(AIRCRAFT_NUMBER, aircraftNumber);
    if (v->isLate())
      SETTEXT(DATE, "已起飞");
    else
      SET(DATE, date.toString("M.d"));
    SETINT(MAX_CAPACITY, maxCapacity);
    __SETINT(REST_COUNT, v->restCount());
    SETINT(DAY_OF_WEEK, date.dayOfWeek());
    i++;
  }
}

void ListWindow::showBook() {
  // 跳过空白
  if (ui->tableWidget->selectedItems().isEmpty())
    return;

  int id = ui->tableWidget->selectedItems()[0]->row();
  Flight *target = m_table[id];
  if (target->isLate())
    QMessageBox::critical(this, "订票", "订票失败，已起飞");
  else if (target->isFull()) {
    QMessageBox::critical(this, "订票", "订票失败，已满");
  } else {
    BookWindow *window = new BookWindow(target);
    window->exec();
  }

  this->close();

  WriteAll();
}
/*
void ListWindow::showRefund() {
  // 跳过空白
  if (ui->tableWidget->selectedItems().isEmpty())
    return;

  int id = ui->tableWidget->selectedItems()[0]->row();
  Flight *target = m_table[id];
  if (target->isLate())
    QMessageBox::critical(this, "退票", "退票失败，已起飞");
  else {
    // BookWindow *window = new BookWindow(target);
    // window->exec();
  }

  this->close();

  WriteAll();
}
*/
// BookWindow

BookWindow::BookWindow(Flight *flight) : ui(new Ui::book), m_target(flight) {
  ui->setupUi(this);

  ui->level->addItem("头等舱", QVariant::fromValue(CabinClass::Fist));
  ui->level->addItem("商务舱", QVariant::fromValue(CabinClass::Business));
  ui->level->addItem("取消", QVariant::fromValue(CabinClass::Economy));
}

void BookWindow::accept() {
  Passenger pass = {ui->name->text(), ui->count->text().toUInt(),
                    ui->level->currentData().value<CabinClass>()};
  if (m_target->book(pass))
    QMessageBox::information(this, "订票", "订票成功");
  else {
    QMessageBox::StandardButton reply =
        QMessageBox::question(this,                              // 父窗口
                              "确认订票",                        // 标题
                              "余票数不足，是否预定？",          // 提示内容
                              QMessageBox::Yes | QMessageBox::No // 按钮组合
        );
    if (reply == QMessageBox::Yes)
      m_target->standby(pass);
  }

  WriteAll();
  this->close();
}

// QueryWindow

QueryWindow::QueryWindow() : ui(new Ui::query) {
  ui->setupUi(this);
  connect(ui->pushButton, &QPushButton::clicked, this, &QueryWindow::query);
}
void QueryWindow::query() {

  const QString &text = ui->lineEdit->text();

  if (text.isEmpty())
    return;

  ListWindow *window = new ListWindow(Flight::query(text));

  window->exec();
}

// SellWindow

SellWindow::SellWindow() : ui(new Ui::sell) {
  ui->setupUi(this);
  connect(ui->refund, &QPushButton::clicked, this, &SellWindow::refund);
}

// void SellWindow::book() {

/*
if (QTime::currentDate() >= Flight::table()[id] {
  QMessageBox::critical(this, "订票", "订票失败，已发车");
  return;
}
if (key.addCount()) {
  QMessageBox::information(this, "订票", "订票成功");
} else
  QMessageBox::critical(this, "订票", "订票失败，已满");

WriteAll();*/
//}

void SellWindow::refund() {
  const QString &name = ui->name->text();
  const QString &flightNumber = ui->flightNumber->text();

  if (flightNumber.isEmpty())
    QMessageBox::critical(this, "退票", "请输入航班号");

  auto &&table = Flight::query(flightNumber);

  bool flag;
  for (auto flight : table) {
    flag = flight->refundAll(name);
    if (flag)
      break;
  }

  if (flag)
    QMessageBox::information(this, "退票", "退票成功");
  else
    QMessageBox::critical(this, "退票", "不存在该用户");

  this->close();
  WriteAll();
}
