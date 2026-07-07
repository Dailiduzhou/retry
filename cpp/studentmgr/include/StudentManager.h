#ifndef STUDENTMGR_STUDENTMANAGER_H
#define STUDENTMGR_STUDENTMANAGER_H

#include <string>
#include <vector>

#include "Database.h"
#include "Student.h"

namespace studentmgr {

class StudentManager {
public:
  enum SortOrder { ByScore, ById };

  explicit StudentManager(const std::string &dbPath = "students.db");

  // Returns the rowid of the most recent successful INSERT.
  long long lastInsertId() const;

  // Information management.
  bool addStudent(const std::string &name, const std::string &gender,
                  const std::string &className, double score,
                  std::string &errMsg);
  bool deleteStudent(int id, std::string &errMsg);  // soft delete
  bool restoreStudent(int id, std::string &errMsg); // undo soft delete
  bool updateScore(int id, double score, std::string &errMsg);

  // Queries (only non-deleted rows).
  bool queryById(int id, Student &out, std::string &errMsg);
  std::vector<Student> queryAll(std::string &errMsg);
  std::vector<Student> queryAllScores(std::string &errMsg);
  std::vector<Student> queryDeleted(std::string &errMsg);

  // Data processing (only non-deleted rows).
  std::vector<Student> sort(SortOrder order, std::string &errMsg);
  double allAverage(std::string &errMsg, bool &ok);

private:
  void initSchema();

  Database db_;
};

} // namespace studentmgr

#endif // STUDENTMGR_STUDENTMANAGER_H
