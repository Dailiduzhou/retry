#ifndef STUDENTMGR_STUDENT_H
#define STUDENTMGR_STUDENT_H

#include <iosfwd>
#include <string>

namespace studentmgr {

struct Student {
  int id = 0;
  std::string name;
  std::string gender;
  std::string className;
  double score = 0.0;
  bool deleted = false;
};

std::ostream &operator<<(std::ostream &os, const Student &s);

} // namespace studentmgr

#endif // STUDENTMGR_STUDENT_H
