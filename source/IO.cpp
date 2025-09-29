#include "IO.hpp"
#include "Flight.hpp"
#include <QDataStream>
#include <QFile>
#include <QFileDevice>

#define filename "data"

void LoadAll() {
  QFile file(filename);
  if (file.open(QIODevice::ReadOnly)) {
    QDataStream in(&file);
    while (!file.atEnd()) {
      Flight::s_table.emplace_back();
      in >> Flight::s_table.back();
    }
    file.close();
  }
}

void WriteAll(const std::vector<Flight> vec) {
  QFile file(filename);
  if (file.open(QIODevice::WriteOnly)) {
    QDataStream out(&file);
    for (auto v : vec)
      out << v;
    file.close();
  }
}
