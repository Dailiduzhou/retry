#ifndef STUDENTMGR_DATABASE_H
#define STUDENTMGR_DATABASE_H

#include <sqlite3.h>
#include <string>

namespace studentmgr {

// RAII wrapper around a sqlite3* connection handle.
// The database is opened on construction and closed automatically
// when the object goes out of scope, ensuring the file handle and
// any pending transaction are released deterministically.
class Database {
public:
  explicit Database(const std::string &path);
  ~Database();

  Database(const Database &) = delete;
  Database &operator=(const Database &) = delete;

  bool isOpen() const { return db_ != nullptr; }
  sqlite3 *raw() const { return db_; }

  // Execute a SQL statement that does not return rows.
  // Returns true on success; on failure fills `errMsg` with the
  // SQLite error text and returns false.
  bool exec(const std::string &sql, std::string &errMsg);

private:
  sqlite3 *db_;
};

// RAII wrapper around a sqlite3_stmt* prepared statement.
// Steps the statement on demand and finalizes it on destruction.
class Statement {
public:
  Statement(sqlite3 *db, const std::string &sql);
  ~Statement();

  Statement(const Statement &) = delete;
  Statement &operator=(const Statement &) = delete;

  bool valid() const { return stmt_ != nullptr; }
  sqlite3_stmt *raw() const { return stmt_; }

  // Returns SQLITE_ROW, SQLITE_DONE, or an error code.
  int step();

private:
  sqlite3_stmt *stmt_;
};

} // namespace studentmgr

#endif // STUDENTMGR_DATABASE_H
