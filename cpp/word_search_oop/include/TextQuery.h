#pragma once

#include <fstream>
#include <map>
#include <memory>
#include <ostream>
#include <set>
#include <string>
#include <vector>

using line_no = std::vector<std::string>::size_type;

class QueryResult;

class TextQuery {
public:
  explicit TextQuery(std::ifstream &);
  QueryResult query(const std::string &) const;

private:
  std::shared_ptr<std::vector<std::string>> file;
  std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult {
  friend std::ostream &print(std::ostream &, const QueryResult &);

public:
  using line_iter = std::set<line_no>::const_iterator;

  QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p,
              std::shared_ptr<std::vector<std::string>> f);

  line_iter begin() const { return lines->begin(); }
  line_iter end() const { return lines->end(); }
  std::shared_ptr<std::vector<std::string>> get_file() const { return file; }
  std::size_t size() const { return lines->size(); }

private:
  std::string sought;
  std::shared_ptr<std::set<line_no>> lines;
  std::shared_ptr<std::vector<std::string>> file;
};

std::ostream &print(std::ostream &, const QueryResult &);
