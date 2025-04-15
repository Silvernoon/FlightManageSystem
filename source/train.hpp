#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <QDateTime>
#include <QTableWidget>
#include <QTime>
#include <cstdint>
#include <vector>

class Train {
  // uint8_t no; //无用
  QTime time;
  QString start, final;
  double duration;
  uint32_t max, count;

public:
  Train() = default;
  Train(QTime time, QString start, QString final, double duration, uint32_t max,
        uint32_t count)
      : time(time), start(start), final(final), duration(duration), max(max),
        count(count) {}

#define v(b) table->item(0, b)->text()
  Train(QTableWidget *table) {
    // no = v(1).toUShort();
    time = QTime::fromString((v(0).length() == 4) ? '0' + v(0) : v(0));
    start = v(1);
    final = v(2);
    duration = v(3).toDouble();
    max = v(4).toUInt();
    count = v(5).toUInt();
  }
#undef v
  ~Train() = default;
  Train(const Train &) = default;

  // Getter
  QTime GetTime() const { return time; }
  QString GetStart() const { return start; }
  QString GetFinal() const { return final; }
  double GetDuration() const { return duration; }
  uint32_t GetMax() const { return max; }
  uint32_t GetCount() const { return count; }
  bool IsFull() const { return count == max; }

  bool AddCount() {
    if (IsFull())
      return false;
    count++;
    return true;
  }
  bool SubCount() {
    if (count == 0)
      return false;
    count--;
    return true;
  }

  static std::vector<Train> Query(uint8_t n) {
    std::vector<Train> result;
    result.push_back(Train::Table[n]);
    return result;
  }
  static std::vector<Train> Query(QString name) {
    std::vector<Train> result;
    for (auto v : Table) {
      if (v.final == name)
        result.push_back(v);
    }
    return result;
  }

// 图省事写的宏
#define d(o)                                                                   \
  train.time o train.start o train.final o train.duration o train.max o        \
      train.count

  friend QDataStream &operator<<(QDataStream &out, const Train &train) {
    out << d(<<);
    return out;
  }

  friend QDataStream &operator>>(QDataStream &in, Train &train) {
    in >> d(>>);
    return in;
  }
#undef d

public:
  static std::vector<Train> Table;
};

inline std::vector<Train> Train::Table; // 初始化

enum tableHead { TIME, START, FINAL, DURATION, MAX, COUNT };

#endif
