#include "Flight.hpp"
#include "Util.hpp"
#include <QDate>
#include <QLocale>
#include <cstdint>
#include <qcontainerfwd.h>
#include <qdatetime.h>
#include <qtablewidget.h>
#include <qvariant.h>
#include <ranges>
#include <vector>

#define TEXT(column) getItemText(table, 0, column)

QDate dateTryFromString(const QString &str) {
  static const QStringList formats = {// yMd
                                      "yyyy-M-d", "yyyy-MM-dd", "yyyy.M.d",
                                      "yyyy.MM.dd", "yyyy/M/d", "yyyy/MM/dd",
                                      // Md
                                      "M-d", "MM-dd", "M.d", "MM.dd", "M/d",
                                      "MM/dd"};
  QDate date;
  const QDate today = QDate::currentDate();
  const int year = today.year();

  for (const QString &format : formats) {
    date = QDate::fromString(str, format);
    if (date.isValid()) {
      if (format[0] == "M")
        date.setDate(year, date.month(), date.day());
      break;
    }
  }

  return date;
}

Flight::Flight() {
  m_bookedList = {};
  m_standbyList = {};
}
Flight::Flight(FlightData data) {
  m_flight = std::move(data);
  m_bookedList = {};
  m_standbyList = {};
}
Flight::Flight(QTableWidget *table) {
  m_flight =
      FlightData{TEXT(DESTINATION), TEXT(FLIGHT_NUMBER), TEXT(AIRCRAFT_NUMBER),
                 dateTryFromString(TEXT(DATE)), TEXT(MAX_CAPACITY).toUInt()};
  m_bookedList = {};
  m_standbyList = {};
}

// Getter

const Flight::FlightData &Flight::flightData() const { return m_flight; }

uint32_t Flight::bookedCount() const { return m_count; }

uint32_t Flight::restCount() const { return m_flight.maxCapacity - m_count; }

bool Flight::isFull() const { return bookedCount() == m_flight.maxCapacity; }

bool Flight::isLate() const { return m_flight.date < QDate::currentDate(); }

// list

bool Flight::book(Passenger pass) {
  if (restCount() >= pass.count) {
    m_count += pass.count;
    m_bookedList.push_back(std::move(pass));
    return true;
  }
  return false;
}

// void Flight::refund(PassengerList::iterator it) { m_bookedList.erase(it); }

/*
auto Flight::find(QString passName) {
  return m_bookedList | std::views::filter([passName](Passenger pass) {
           return pass.name == passName;
         });
}*/

/**
 * Return bool, if remove successfully
 */
bool Flight::refundAll(QString passName) {
  int size = m_bookedList.size();

  m_bookedList.remove_if([this, passName](Passenger pass) {
    m_count -= pass.count;
    return pass.name == passName;
  });

  if (size != m_bookedList.size()) {
    moveIn();
    return true;
  } else
    return false;
}

void Flight::standby(Passenger pass) {
  m_standbyList.push_back(std::move(pass));
}

void Flight::moveIn() {
  for (auto it = m_standbyList.begin(); it != m_standbyList.end(); it++)
    if (it->count <= restCount()) {
      book(*it);
      m_standbyList.erase(it);
    }
}

const PassengerList &Flight::bookedList() const { return m_bookedList; }
const PassengerList &Flight::standbyList() const { return m_standbyList; }

// Table

const std::vector<Flight> &Flight::table() { return s_table; }

std::vector<Flight *> Flight::query(QString str) {
  auto view =
      s_table | std::views::filter([str](const Flight &flight) {
        return flight.m_flight.destination == str ||
               flight.m_flight.flightNumber == str;
      }) |
      std::views::transform([](Flight &flight) -> Flight * { return &flight; });
  return std::vector<Flight *>(view.begin(), view.end());
}

void Flight::emplace(QTableWidget *table) { s_table.emplace_back(table); }

QDataStream &operator<<(QDataStream &out, const Passenger &data) {
  out << data.name << data.count << data.cabinClass;
  return out;
}
QDataStream &operator>>(QDataStream &in, Passenger &data) {
  in >> data.name >> data.count >> data.cabinClass;
  return in;
}

#define take(x) flight.m_flight.x
QDataStream &operator<<(QDataStream &out, const Flight &flight) {
  out << take(destination) << take(flightNumber) << take(aircraftNumber)
      << take(date) << take(maxCapacity);

  out << (uint32_t)flight.m_bookedList.size();
  for (const auto &pass : flight.m_bookedList)
    out << pass;

  out << (uint32_t)flight.m_standbyList.size();
  for (const auto &pass : flight.m_standbyList)
    out << pass;

  return out;
}

QDataStream &operator>>(QDataStream &in, Flight &flight) {
  in >> take(destination) >> take(flightNumber) >> take(aircraftNumber) >>
      take(date) >> take(maxCapacity);

  Passenger p;
  uint32_t size;

  in >> size;
  for (; size > 0; size--) {
    // 两次构造，效率低下
    in >> p;
    flight.book(p);
  }

  in >> size;
  for (; size > 0; size--) {
    flight.m_standbyList.emplace_back();
    in >> flight.m_standbyList.back();
  }

  return in;
}

//

std::vector<Flight> Flight::s_table = {};
