#pragma once

#include "TextQuery.h"
#include <memory>
#include <string>

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
  Query(std::shared_ptr<Query_Base> query) : q(std::move(query)) {}
  std::shared_ptr<Query_Base> q;
};

std::ostream &operator<<(std::ostream &os, const Query &query);

class WordQuery : public Query_Base {
  friend class Query;

  explicit WordQuery(const std::string &s) : query_word(s) {}
  QueryResult eval(const TextQuery &t) const override { return t.query(query_word); }
  std::string rep() const override { return query_word; }

  std::string query_word;
};

class NotQuery : public Query_Base {
  friend Query operator~(const Query &);

  explicit NotQuery(const Query &q) : query(q) {}
  std::string rep() const override { return "~(" + query.rep() + ")"; }
  QueryResult eval(const TextQuery &) const override;

  Query query;
};

class BinaryQuery : public Query_Base {
protected:
  BinaryQuery(const Query &l, const Query &r, std::string s)
      : lhs(l), rhs(r), opSym(std::move(s)) {}

  std::string rep() const override {
    return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
  }

  Query lhs, rhs;
  std::string opSym;
};

class AndQuery : public BinaryQuery {
  friend Query operator&(const Query &, const Query &);

  AndQuery(const Query &left, const Query &right)
      : BinaryQuery(left, right, "&") {}

  QueryResult eval(const TextQuery &) const override;
};

class OrQuery : public BinaryQuery {
  friend Query operator|(const Query &, const Query &);

  OrQuery(const Query &left, const Query &right)
      : BinaryQuery(left, right, "|") {}

  QueryResult eval(const TextQuery &) const override;
};

Query operator~(const Query &);
Query operator&(const Query &, const Query &);
Query operator|(const Query &, const Query &);
