#include "Util.hpp"

// Table

// Regular

bool regularCheck(const char *regular, const QString &target) {
  QRegularExpression check(regular);
  return check.match(target).hasMatch();
}
