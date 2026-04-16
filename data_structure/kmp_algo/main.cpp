#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

void buildNext(const string &pattern, vector<int> &next) {
  const int m = static_cast<int>(pattern.size());
  if (m == 0) {
    return;
  }

  next[0] = -1;
  int j = 0;
  int k = -1;

  while (j < m - 1) {
    if (k == -1 || pattern[j] == pattern[k]) {
      ++j;
      ++k;
      if (pattern[j] != pattern[k]) {
        next[j] = k;
      } else {
        next[j] = next[k];
      }
    } else {
      k = next[k];
    }
  }
}

int kmpSearch(const string &text, const string &pattern) {
  const int n = static_cast<int>(text.size());
  const int m = static_cast<int>(pattern.size());

  if (m == 0) {
    return 0;
  }
  if (n < m) {
    return -1;
  }

  vector<int> next(m, -1);
  buildNext(pattern, next);

  int i = 0;
  int j = 0;
  while (i < n && j < m) {
    if (j == -1 || text[i] == pattern[j]) {
      ++i;
      ++j;
    } else {
      j = next[j];
    }
  }

  return (j == m) ? (i - j) : -1;
}

void testKMP() {
  const vector<tuple<string, string, int>> testCases{
      {"asdfghjl", "jkl", -1},
      {"qwemn", "nm", -1},
      {"asdasda", "op", -1},
      {"hello", "ll", 2},
      {"aaaaab", "aaab", 2},
      {"abcxabcdabxabcdabcdabcy", "abcdabcy", 15},
      {"", "", 0},
      {"abc", "", 0},
      {"", "a", -1},
      {"a", "a", 0},
      {"aaaaa", "aaa", 0},
      {"mississippi", "issip", 4},
      {"ababababca", "abababca", 2},
      {"abc", "d", -1},
      {"needle in a haystack", "hay", 12},
      {"endswithpattern", "pattern", 8},
      {"patternatstart", "pattern", 0},
      {"short", "longer", -1},
      {"ababaca", "abaca", 2},
      {"zzzabczzz", "abc", 3},
  };

  int passed = 0;
  for (size_t idx = 0; idx < testCases.size(); ++idx) {
    const auto &[text, pattern, expected] = testCases[idx];
    const int actual = kmpSearch(text, pattern);
    const bool ok = (actual == expected);
    cout << "Case " << idx + 1 << ": expected=" << expected
         << ", actual=" << actual << (ok ? " [PASS]" : " [FAIL]") << '\n';
    if (ok) {
      ++passed;
    }
  }

  cout << "Passed " << passed << "/" << testCases.size() << " cases.\n";
}

int main() {
  testKMP();
  return 0;
}
