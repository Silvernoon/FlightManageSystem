#pragma once

#include <QString>
#include <QTableWidget>

inline QString getItemText(QTableWidget *table, int row, int column) {
  return table->item(row, column)->text();
}

inline void setItemText(QTableWidget *table, int row, int column,
                        QString text) {
  table->setItem(row, column, new QTableWidgetItem(text));
}

// Regular

// 通过正则表达式检查
bool regularCheck(const char *regular, const QString &target);
