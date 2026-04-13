#include "TextQuery.h"

#include <cctype>
#include <sstream>
#include <utility>

static std::string cleanup_str(const std::string &word) {
  std::string ret;
  ret.reserve(word.size());
  for (unsigned char ch : word) {
    if (!std::ispunct(ch)) {
      ret.push_back(static_cast<char>(std::tolower(ch)));
    }
  }
  return ret;
}

static std::string make_plural(std::size_t ctr, const std::string &word,
                               const std::string &ending = "s") {
  return (ctr == 1) ? word : word + ending;
}

TextQuery::TextQuery(std::ifstream &is) : file(std::make_shared<std::vector<std::string>>()) {
  std::string text;
  while (std::getline(is, text)) {
    file->push_back(text);
    line_no n = file->size() - 1;
    std::istringstream line(text);
    std::string word;
    while (line >> word) {
      word = cleanup_str(word);
      if (word.empty()) {
        continue;
      }
      auto &lines = wm[word];
      if (!lines) {
        lines.reset(new std::set<line_no>);
      }
      lines->insert(n);
    }
  }
}

QueryResult TextQuery::query(const std::string &s) const {
  static std::shared_ptr<std::set<line_no>> nodata =
      std::make_shared<std::set<line_no>>();
  std::string key = cleanup_str(s);
  auto loc = wm.find(key);
  if (loc == wm.end()) {
    return QueryResult(key, nodata, file);
  }
  return QueryResult(key, loc->second, file);
}

QueryResult::QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p,
                         std::shared_ptr<std::vector<std::string>> f)
    : sought(std::move(s)), lines(std::move(p)), file(std::move(f)) {}

std::ostream &print(std::ostream &os, const QueryResult &qr) {
  os << qr.sought << " occurs " << qr.lines->size() << " "
     << make_plural(qr.lines->size(), "time") << "\n";
  for (auto num : *qr.lines) {
    os << "\t(line " << num + 1 << ") " << (*qr.file)[num] << "\n";
  }
  return os;
}
