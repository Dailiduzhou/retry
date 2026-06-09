#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

typedef struct StudentInfo {
  char name[3];
  int score;
} StudentInfo;

void CreateStuInfo(StudentInfo &stuinfo, const char *name, int score) {
  if (strlen(name) != 2) {
    return;
  }
  strcpy(stuinfo.name, name);
  stuinfo.score = score;
}

int main(int argc, char **argv) {
  std::vector<StudentInfo> stus;

  StudentInfo si;
  CreateStuInfo(si, "A1", 80);
  stus.push_back(si);
  CreateStuInfo(si, "B2", 75);
  stus.push_back(si);
  CreateStuInfo(si, "C1", 85);
  stus.push_back(si);

  std::sort(stus.begin(), stus.end(),
            [](const StudentInfo &a, const StudentInfo &b) {
              return a.score > b.score;
            });

  for (const auto &s : stus) {
    std::cout << s.name << " " << s.score << std::endl;
  }

  return 0;
}
