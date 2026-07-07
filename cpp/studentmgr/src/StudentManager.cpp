#include "StudentManager.h"

#include <sqlite3.h>

namespace studentmgr {

namespace {

// Reads columns of a SELECT id, name, gender, class, score, deleted projection
// from the currently-stepped statement into a Student.
Student readRow(sqlite3_stmt *stmt) {
  Student s;
  s.id = sqlite3_column_int(stmt, 0);
  const unsigned char *name = sqlite3_column_text(stmt, 1);
  s.name = name ? reinterpret_cast<const char *>(name) : "";
  const unsigned char *gender = sqlite3_column_text(stmt, 2);
  s.gender = gender ? reinterpret_cast<const char *>(gender) : "";
  const unsigned char *cls = sqlite3_column_text(stmt, 3);
  s.className = cls ? reinterpret_cast<const char *>(cls) : "";
  s.score = sqlite3_column_double(stmt, 4);
  s.deleted = sqlite3_column_int(stmt, 5) != 0;
  return s;
}

} // namespace

StudentManager::StudentManager(const std::string &dbPath) : db_(dbPath) {
  initSchema();
}

long long StudentManager::lastInsertId() const {
  if (!db_.isOpen())
    return 0;
  return sqlite3_last_insert_rowid(db_.raw());
}

void StudentManager::initSchema() {
  if (!db_.isOpen()) {
    return;
  }
  std::string err;
  // Fresh-table schema with all columns.
  db_.exec("CREATE TABLE IF NOT EXISTS students ("
           "  id      INTEGER PRIMARY KEY AUTOINCREMENT,"
           "  name    TEXT    NOT NULL,"
           "  gender  TEXT    NOT NULL DEFAULT '',"
           "  class   TEXT    NOT NULL DEFAULT '',"
           "  score   REAL    NOT NULL,"
           "  deleted INTEGER NOT NULL DEFAULT 0"
           ");",
           err);
  // Migrate legacy tables that lack the new columns; ignore errors when the
  // column already exists ("duplicate column name").
  std::string ignore;
  db_.exec("ALTER TABLE students ADD COLUMN gender TEXT NOT NULL DEFAULT ''",
           ignore);
  db_.exec("ALTER TABLE students ADD COLUMN class TEXT NOT NULL DEFAULT ''",
           ignore);
  db_.exec("ALTER TABLE students ADD COLUMN deleted INTEGER NOT NULL DEFAULT 0",
           ignore);
  // Any pre-existing rows are treated as live (deleted=0) by the DEFAULT.
}

bool StudentManager::addStudent(const std::string &name,
                                const std::string &gender,
                                const std::string &className, double score,
                                std::string &errMsg) {
  Statement stmt(db_.raw(), "INSERT INTO students (name, gender, class, score) "
                            "VALUES (?, ?, ?, ?);");
  if (!stmt.valid()) {
    errMsg = "failed to prepare INSERT statement";
    return false;
  }
  sqlite3_bind_text(stmt.raw(), 1, name.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt.raw(), 2, gender.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt.raw(), 3, className.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_double(stmt.raw(), 4, score);
  int rc = stmt.step();
  if (rc != SQLITE_DONE) {
    errMsg = sqlite3_errmsg(db_.raw());
    return false;
  }
  return true;
}

bool StudentManager::deleteStudent(int id, std::string &errMsg) {
  // Soft delete: mark the row as deleted rather than removing it.
  Statement stmt(db_.raw(), "UPDATE students SET deleted = 1 "
                            "WHERE id = ? AND deleted = 0;");
  if (!stmt.valid()) {
    errMsg = "failed to prepare UPDATE statement";
    return false;
  }
  sqlite3_bind_int(stmt.raw(), 1, id);
  int rc = stmt.step();
  if (rc != SQLITE_DONE) {
    errMsg = sqlite3_errmsg(db_.raw());
    return false;
  }
  if (sqlite3_changes(db_.raw()) == 0) {
    errMsg = "no live student with that id";
    return false;
  }
  return true;
}

bool StudentManager::restoreStudent(int id, std::string &errMsg) {
  Statement stmt(db_.raw(), "UPDATE students SET deleted = 0 "
                            "WHERE id = ? AND deleted = 1;");
  if (!stmt.valid()) {
    errMsg = "failed to prepare UPDATE statement";
    return false;
  }
  sqlite3_bind_int(stmt.raw(), 1, id);
  int rc = stmt.step();
  if (rc != SQLITE_DONE) {
    errMsg = sqlite3_errmsg(db_.raw());
    return false;
  }
  if (sqlite3_changes(db_.raw()) == 0) {
    errMsg = "no deleted student with that id";
    return false;
  }
  return true;
}

bool StudentManager::updateScore(int id, double score, std::string &errMsg) {
  Statement stmt(db_.raw(), "UPDATE students SET score = ? "
                            "WHERE id = ? AND deleted = 0;");
  if (!stmt.valid()) {
    errMsg = "failed to prepare UPDATE statement";
    return false;
  }
  sqlite3_bind_double(stmt.raw(), 1, score);
  sqlite3_bind_int(stmt.raw(), 2, id);
  int rc = stmt.step();
  if (rc != SQLITE_DONE) {
    errMsg = sqlite3_errmsg(db_.raw());
    return false;
  }
  if (sqlite3_changes(db_.raw()) == 0) {
    errMsg = "no live student with that id";
    return false;
  }
  return true;
}

bool StudentManager::queryById(int id, Student &out, std::string &errMsg) {
  Statement stmt(db_.raw(), "SELECT id, name, gender, class, score, deleted "
                            "FROM students WHERE id = ? AND deleted = 0;");
  if (!stmt.valid()) {
    errMsg = "failed to prepare SELECT statement";
    return false;
  }
  sqlite3_bind_int(stmt.raw(), 1, id);
  int rc = stmt.step();
  if (rc == SQLITE_ROW) {
    out = readRow(stmt.raw());
    return true;
  }
  errMsg = (rc == SQLITE_DONE) ? "no live student with that id"
                               : sqlite3_errmsg(db_.raw());
  return false;
}

std::vector<Student> StudentManager::queryAll(std::string &errMsg) {
  std::vector<Student> result;
  Statement stmt(db_.raw(), "SELECT id, name, gender, class, score, deleted "
                            "FROM students WHERE deleted = 0 ORDER BY id;");
  if (!stmt.valid()) {
    errMsg = "failed to prepare SELECT statement";
    return result;
  }
  while (stmt.step() == SQLITE_ROW) {
    result.push_back(readRow(stmt.raw()));
  }
  return result;
}

std::vector<Student> StudentManager::queryAllScores(std::string &errMsg) {
  // Same projection; the menu formats the score column prominently.
  return queryAll(errMsg);
}

std::vector<Student> StudentManager::queryDeleted(std::string &errMsg) {
  std::vector<Student> result;
  Statement stmt(db_.raw(), "SELECT id, name, gender, class, score, deleted "
                            "FROM students WHERE deleted = 1 ORDER BY id;");
  if (!stmt.valid()) {
    errMsg = "failed to prepare SELECT statement";
    return result;
  }
  while (stmt.step() == SQLITE_ROW) {
    result.push_back(readRow(stmt.raw()));
  }
  return result;
}

std::vector<Student> StudentManager::sort(SortOrder order,
                                          std::string &errMsg) {
  std::vector<Student> result;
  const char *sql =
      (order == ByScore)
          ? "SELECT id, name, gender, class, score, deleted "
            "FROM students WHERE deleted = 0 ORDER BY score DESC, id ASC;"
          : "SELECT id, name, gender, class, score, deleted "
            "FROM students WHERE deleted = 0 ORDER BY id ASC;";
  Statement stmt(db_.raw(), sql);
  if (!stmt.valid()) {
    errMsg = "failed to prepare SELECT statement";
    return result;
  }
  while (stmt.step() == SQLITE_ROW) {
    result.push_back(readRow(stmt.raw()));
  }
  return result;
}

double StudentManager::allAverage(std::string &errMsg, bool &ok) {
  ok = false;
  Statement stmt(db_.raw(),
                 "SELECT AVG(score) FROM students WHERE deleted = 0;");
  if (!stmt.valid()) {
    errMsg = "failed to prepare AVG statement";
    return 0.0;
  }
  int rc = stmt.step();
  if (rc != SQLITE_ROW) {
    errMsg = (rc == SQLITE_DONE) ? "no students recorded"
                                 : sqlite3_errmsg(db_.raw());
    return 0.0;
  }
  if (sqlite3_column_type(stmt.raw(), 0) == SQLITE_NULL) {
    errMsg = "no students recorded";
    return 0.0;
  }
  ok = true;
  return sqlite3_column_double(stmt.raw(), 0);
}

} // namespace studentmgr
