#pragma once

#include "Flight.hpp"
#include "ui_MainWindow.h"
#include "ui_add.h"
#include "ui_book.h"
#include "ui_list.h"
#include "ui_query.h"
#include "ui_sell.h"
#include <QDialog>
#include <QDialogButtonBox>
#include <QMainWindow>
#include <QMetaObject>

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow();
  ~MainWindow() = default;

private slots:
  // button
  void add();
  void query();
  void sell();

private:
  Ui::mainWindow *ui;
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
  explicit ListWindow(FlightPtrTable);
  ~ListWindow() = default;

private slots:
  void showBook();
  // void showRefund();

private:
  FlightPtrTable m_table;
};

class BookWindow : public QDialog {
  Q_OBJECT

  Ui::book *ui;

public:
  explicit BookWindow(Flight *);
  ~BookWindow() = default;

  void accept() override;

private:
  Flight *m_target;
};

class QueryWindow : public QDialog {
  Q_OBJECT

  Ui::query *ui;

public:
  explicit QueryWindow();
  ~QueryWindow() = default;

private slots:
  void query();
};

class SellWindow : public QDialog {
  Q_OBJECT

  Ui::sell *ui;

public:
  explicit SellWindow();
  ~SellWindow() = default;

private slots:
  void refund();
};
