#include "Database.h"

#include <utility>

namespace studentmgr {

Database::Database(const std::string &path) : db_(nullptr) {
  if (sqlite3_open(path.c_str(), &db_) != SQLITE_OK) {
    // Even on failure sqlite3_open may allocate a handle that must be
    // closed; finalizing here keeps ownership tidy.
    if (db_) {
      sqlite3_close(db_);
      db_ = nullptr;
    }
  }
}

Database::~Database() {
  if (db_) {
    sqlite3_close(db_);
    db_ = nullptr;
  }
}

bool Database::exec(const std::string &sql, std::string &errMsg) {
  if (!db_) {
    errMsg = "database is not open";
    return false;
  }
  char *err = nullptr;
  int rc = sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &err);
  if (rc != SQLITE_OK) {
    errMsg = err ? err : "unknown sqlite3_exec error";
    if (err)
      sqlite3_free(err);
    return false;
  }
  return true;
}

Statement::Statement(sqlite3 *db, const std::string &sql) : stmt_(nullptr) {
  if (!db)
    return;
  sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt_, nullptr);
}

Statement::~Statement() {
  if (stmt_)
    sqlite3_finalize(stmt_);
}

int Statement::step() {
  if (!stmt_)
    return SQLITE_ERROR;
  return sqlite3_step(stmt_);
}

} // namespace studentmgr
