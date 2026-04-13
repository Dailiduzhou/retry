#include "Query.h"

#include <algorithm>
#include <iterator>

Query::Query(const std::string &s)
    : q(std::shared_ptr<Query_Base>(new WordQuery(s))) {}

std::ostream &operator<<(std::ostream &os, const Query &query) {
  return os << query.rep();
}

Query operator~(const Query &operand) {
  return Query(std::shared_ptr<Query_Base>(new NotQuery(operand)));
}

Query operator&(const Query &lhs, const Query &rhs) {
  return Query(std::shared_ptr<Query_Base>(new AndQuery(lhs, rhs)));
}

Query operator|(const Query &lhs, const Query &rhs) {
  return Query(std::shared_ptr<Query_Base>(new OrQuery(lhs, rhs)));
}

QueryResult NotQuery::eval(const TextQuery &text) const {
  auto result = query.eval(text);
  auto ret_lines = std::make_shared<std::set<line_no>>();

  auto sz = result.get_file()->size();
  auto beg = result.begin();
  auto end = result.end();

  for (line_no n = 0; n < sz; ++n) {
    if (beg == end || *beg != n) {
      ret_lines->insert(n);
    } else if (beg != end) {
      ++beg;
    }
  }

  return QueryResult(rep(), ret_lines, result.get_file());
}

QueryResult AndQuery::eval(const TextQuery &text) const {
  auto left = lhs.eval(text);
  auto right = rhs.eval(text);
  auto ret_lines = std::make_shared<std::set<line_no>>();

  std::set_intersection(left.begin(), left.end(), right.begin(), right.end(),
                        std::inserter(*ret_lines, ret_lines->begin()));

  return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult OrQuery::eval(const TextQuery &text) const {
  auto left = lhs.eval(text);
  auto right = rhs.eval(text);

  auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());
  ret_lines->insert(right.begin(), right.end());

  return QueryResult(rep(), ret_lines, left.get_file());
}
