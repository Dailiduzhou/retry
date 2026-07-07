#include "Student.h"

#include <iomanip>
#include <ostream>

namespace studentmgr {

std::ostream &operator<<(std::ostream &os, const Student &s) {
  os << std::left << std::setw(6) << s.id << std::setw(12) << s.name
     << std::setw(8) << s.gender << std::setw(12) << s.className << std::right
     << std::setw(7) << s.chinese << std::setw(7) << s.math << std::setw(7)
     << s.english << std::setw(7) << s.total;
  return os;
}

} // namespace studentmgr
