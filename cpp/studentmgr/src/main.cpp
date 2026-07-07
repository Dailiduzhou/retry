#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "Student.h"
#include "StudentManager.h"

using studentmgr::ClassStats;
using studentmgr::Student;
using studentmgr::StudentManager;

namespace {

void printMenu() {
  std::cout << "\n========== 学生管理系统 ==========\n"
            << "1. 录入学生信息\n"
            << "2. 删除学生信息（软删除）\n"
            << "3. 修改学生成绩\n"
            << "4. 按学号查询\n"
            << "5. 查询所有学生信息\n"
            << "6. 查询所有成绩\n"
            << "7. 按总分排序\n"
            << "8. 按学号排序\n"
            << "9. 统计全体平均分\n"
            << "10. 恢复已删除学生\n"
            << "11. 查看已删除学生\n"
            << "0. 退出\n"
            << "请选择操作: ";
}

void clearLine() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readInt(const char *prompt) {
  std::cout << prompt;
  int v;
  while (!(std::cin >> v) || v < 0) {
    std::cout << "数值无效，请重新输入: ";
    clearLine();
  }
  clearLine();
  return v;
}

int readId(const char *prompt = "请输入学号: ") {
  std::cout << prompt;
  int v;
  while (!(std::cin >> v) || v <= 0) {
    std::cout << "学号无效，请重新输入: ";
    clearLine();
  }
  clearLine();
  return v;
}

std::string readToken(const char *prompt) {
  std::cout << prompt;
  std::string v;
  if (!(std::cin >> v)) {
    clearLine();
    return "";
  }
  clearLine();
  return v;
}

void printHeader() {
  std::cout << "-----------------------------------------------------"
               "-------------------\n"
            << "学号  姓名        性别    班级        语文  数学  "
               "英语  总分\n"
            << "-----------------------------------------------------"
               "-------------------\n";
}

void printStudents(const std::vector<Student> &list) {
  printHeader();
  for (const auto &s : list) {
    std::cout << s << "\n";
  }
  std::cout << "共 " << list.size() << " 条记录\n";
}

} // namespace

int main() {
  StudentManager mgr("students.db");
  std::string errMsg;

  int choice = -1;
  while (true) {
    printMenu();
    if (!(std::cin >> choice)) {
      clearLine();
      std::cout << "输入无效，请重新选择。\n";
      continue;
    }
    clearLine();

    switch (choice) {
    case 0:
      std::cout << "再见！\n";
      return 0;
    case 1: {
      std::string name = readToken("请输入姓名: ");
      std::string gender = readToken("请输入性别 (男/女): ");
      std::string className = readToken("请输入班级: ");
      int chinese = readInt("请输入语文成绩: ");
      int math = readInt("请输入数学成绩: ");
      int english = readInt("请输入英语成绩: ");
      errMsg.clear();
      if (mgr.addStudent(name, gender, className, chinese, math, english,
                         errMsg)) {
        std::cout << "录入成功，新学号为 " << mgr.lastInsertId() << "，总分 "
                  << (chinese + math + english) << "\n";
      } else {
        std::cout << "录入失败: " << errMsg << "\n";
      }
      break;
    }
    case 2: {
      int id = readId("请输入要删除的学号: ");
      errMsg.clear();
      if (mgr.deleteStudent(id, errMsg)) {
        std::cout << "删除成功（已标记为软删除）\n";
      } else {
        std::cout << "删除失败: " << errMsg << "\n";
      }
      break;
    }
    case 3: {
      int id = readId("请输入要修改的学号: ");
      int chinese = readInt("请输入新的语文成绩: ");
      int math = readInt("请输入新的数学成绩: ");
      int english = readInt("请输入新的英语成绩: ");
      errMsg.clear();
      if (mgr.updateScores(id, chinese, math, english, errMsg)) {
        std::cout << "修改成功\n";
      } else {
        std::cout << "修改失败: " << errMsg << "\n";
      }
      break;
    }
    case 4: {
      int id = readId("请输入要查询的学号: ");
      Student s;
      errMsg.clear();
      if (mgr.queryById(id, s, errMsg)) {
        printHeader();
        std::cout << s << "\n";
      } else {
        std::cout << "查询失败: " << errMsg << "\n";
      }
      break;
    }
    case 5: {
      errMsg.clear();
      std::vector<Student> all = mgr.queryAll(errMsg);
      if (!errMsg.empty()) {
        std::cout << "查询失败: " << errMsg << "\n";
      } else if (all.empty()) {
        std::cout << "暂无学生记录\n";
      } else {
        printStudents(all);
      }
      break;
    }
    case 6: {
      errMsg.clear();
      std::vector<Student> all = mgr.queryAllScores(errMsg);
      if (!errMsg.empty()) {
        std::cout << "查询失败: " << errMsg << "\n";
      } else if (all.empty()) {
        std::cout << "暂无成绩记录\n";
      } else {
        printStudents(all);
      }
      break;
    }
    case 7: {
      errMsg.clear();
      std::vector<Student> list = mgr.sort(StudentManager::ByTotal, errMsg);
      if (!errMsg.empty()) {
        std::cout << "排序失败: " << errMsg << "\n";
      } else if (list.empty()) {
        std::cout << "暂无学生记录\n";
      } else {
        printStudents(list);
      }
      break;
    }
    case 8: {
      errMsg.clear();
      std::vector<Student> list = mgr.sort(StudentManager::ById, errMsg);
      if (!errMsg.empty()) {
        std::cout << "排序失败: " << errMsg << "\n";
      } else if (list.empty()) {
        std::cout << "暂无学生记录\n";
      } else {
        printStudents(list);
      }
      break;
    }
    case 9: {
      errMsg.clear();
      ClassStats stats;
      if (mgr.overallAverage(stats, errMsg)) {
        std::cout.setf(std::ios::fixed);
        std::cout.precision(2);
        std::cout << "学生人数: " << stats.count << "\n"
                  << "语文平均: " << stats.chinese << "\n"
                  << "数学平均: " << stats.math << "\n"
                  << "英语平均: " << stats.english << "\n"
                  << "总分平均: " << stats.total << "\n";
      } else {
        std::cout << "统计失败: " << errMsg << "\n";
      }
      break;
    }
    case 10: {
      int id = readId("请输入要恢复的学号: ");
      errMsg.clear();
      if (mgr.restoreStudent(id, errMsg)) {
        std::cout << "恢复成功\n";
      } else {
        std::cout << "恢复失败: " << errMsg << "\n";
      }
      break;
    }
    case 11: {
      errMsg.clear();
      std::vector<Student> list = mgr.queryDeleted(errMsg);
      if (!errMsg.empty()) {
        std::cout << "查询失败: " << errMsg << "\n";
      } else if (list.empty()) {
        std::cout << "暂无已删除学生记录\n";
      } else {
        printStudents(list);
      }
      break;
    }
    default:
      std::cout << "无效选项，请重新选择。\n";
      break;
    }
  }
}
