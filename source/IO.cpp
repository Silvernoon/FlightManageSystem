#include "IO.hpp"
#include "train.hpp"
#include <QDataStream>
#include <QFile>
#include <QFileDevice>

#define filename "data"

std::vector<Train> LoadAll() {
  Train::Table = {};
  QFile file(filename);
  if (file.open(QIODevice::ReadOnly)) {
    QDataStream in(&file);
    while (!file.atEnd()) {
      Train t;
      in >> t;
      Train::Table.push_back(t);
    }
    file.close();
  }

  return Train::Table;
}

void WriteAll(std::vector<Train> vec) {
  QFile file(filename);
  if (file.open(QIODevice::WriteOnly)) {
    QDataStream out(&file);
    for (auto v : vec)
      out << v;
    file.close();
  }
}
