#include "Student.h"

#include <iomanip>
#include <ostream>

namespace studentmgr {

std::ostream &operator<<(std::ostream &os, const Student &s) {
  os << std::left << std::setw(6) << s.id << std::setw(16) << s.name
     << std::setw(8) << s.gender << std::setw(14) << s.className << std::right
     << std::setw(8) << std::fixed << std::setprecision(2) << s.score;
  return os;
}

} // namespace studentmgr
