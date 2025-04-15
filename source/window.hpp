#include "train.hpp"
#include "ui_MainWindow.h"
#include "ui_add.h"
#include "ui_list.h"
#include "ui_query.h"
#include "ui_sell.h"
#include <QDialogButtonBox>
#include <QMainWindow>
#include <QMetaObject>
#include <qdialog.h>
#include <qtmetamacros.h>
#include <vector>

class MainWindow : public QMainWindow {
  Q_OBJECT

  Ui::mainWindow *ui;

public:
  explicit MainWindow();
  ~MainWindow() = default;

private slots:
  // button
  void add();
  void list();
  void query();
  void sell();
};

class AddWindow : public QDialog {
  Q_OBJECT

  Ui::add *ui;

public:
  explicit AddWindow();
  ~AddWindow() = default;

  void accept() override;
};

class ListWindow : public QDialog {
  Q_OBJECT

  Ui::list *ui;

public:
  explicit ListWindow(std::vector<Train> table = Train::Table);
  ~ListWindow() = default;

private slots:
  void book();
};

class QueryWindow : public QDialog {
  Q_OBJECT

  Ui::query *ui;

public:
  explicit QueryWindow();
  ~QueryWindow() = default;

private slots:
  void showTable();
};

class SellWindow : public QDialog {
  Q_OBJECT

  Ui::sell *ui;

public:
  explicit SellWindow();
  ~SellWindow() = default;

private slots:
  void book();
  void refund();
};
