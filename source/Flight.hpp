#pragma once

#include <QDate>
#include <QDateTime>
#include <qcontainerfwd.h>
#include <qtablewidget.h>
#include <vector>

enum class CabinClass { Fist, Business, Economy };
enum FlightDataHead {
  DESTINATION,
  FLIGHT_NUMBER,
  AIRCRAFT_NUMBER,
  DATE,
  MAX_CAPACITY,
  REST_COUNT,
  DAY_OF_WEEK
};

struct Passenger {
  QString name;
  uint32_t count;
  CabinClass cabinClass;
};

using PassengerList = std::list<Passenger>;

class Flight {
public:
  struct FlightData {
    QString destination;
    QString flightNumber;
    QString aircraftNumber;
    QDate date;
    uint32_t maxCapacity;
  };

  Flight();
  Flight(FlightData);
  Flight(QTableWidget *table);
  ~Flight() = default;

  // Getter

  const FlightData &flightData() const;
  uint32_t bookedCount() const;
  uint32_t restCount() const;
  bool isFull() const;
  bool isLate() const;

  // list

  // copy once
  bool book(Passenger);
  // void refund(PassengerList::iterator);
  //  auto find(QString passName);
  bool refundAll(QString passName);
  void standby(Passenger);

  const PassengerList &bookedList() const;
  const PassengerList &standbyList() const;

private:
  void moveIn();

  // Table
public:
  static const std::vector<Flight> &table();

  static std::vector<Flight *> query(QString str);
  static void emplace(QTableWidget *);

public:
  friend QDataStream &operator<<(QDataStream &out, const Flight &flight);
  friend QDataStream &operator>>(QDataStream &in, Flight &flight);

  friend void LoadAll();
  friend void WriteAll(std::vector<Flight>);

private:
  FlightData m_flight;
  u_int32_t m_count = 0;
  PassengerList m_bookedList;
  PassengerList m_standbyList;

  static std::vector<Flight> s_table;
};

using FlightTable = std::vector<Flight>;
using FlightPtrTable = std::vector<Flight *>;

QDate dateTryFromString(const QString &str);
