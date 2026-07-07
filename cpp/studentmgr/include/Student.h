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
  int chinese = 0;
  int math = 0;
  int english = 0;
  int total = 0;
  bool deleted = false;
};

std::ostream &operator<<(std::ostream &os, const Student &s);

} // namespace studentmgr

#endif // STUDENTMGR_STUDENT_H
