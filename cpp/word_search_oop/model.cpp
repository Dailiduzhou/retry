#include <iostream>
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
  TextQuery(std::ifstream &);
  QueryResult query(const std::string &) const;

private:
  std::shared_ptr<std::vector<std::string>> file;
  std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult {
  friend std::ostream &print(std::ostream &, const QueryResult &);

public:
  QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p,
              std::shared_ptr<std::vector<std::string>> f);

private:
  std::string sought;
  std::shared_ptr<std::set<line_no>> lines;
  std::shared_ptr<std::vector<std::string>> file;
};

class Query_Base {
  friend class Query;

protected:
  virtual ~Query_Base() = default;

private:
  virtual QueryResult eval(const TextQuery &) const = 0;
  virtual std::string rep() const = 0;
};

class Query {
  friend Query operator~(const Query &);
  friend Query operator|(const Query &, const Query &);
  friend Query operator&(const Query &, const Query &);

public:
  Query(const std::string &);
  QueryResult eval(const TextQuery &t) const { return q->eval(t); }
  std::string rep() const { return q->rep(); }

private:
  Query(std::shared_ptr<Query_Base> query) : q(query) {}
  std::shared_ptr<Query_Base> q;
};

std::ostream &operator<<(std::ostream &os, const Query query) {
  return os << query.rep();
}
