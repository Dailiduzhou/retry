#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stack>

bool isOpMember(char c) {
  switch (c) {
  case '+':
  case '-':
  case '/':
  case '*':
    return true;
    break;
  default:
    return false;
  }
}

int Operation(char ops, int a, int b) {
  switch (ops) {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '/':
    return a / b;
  case '*':
    return a * b;
  default:
    exit(-1);
  }
}

int evaluation(const char *post) {
  std::stack<int> st;
  const char *p = post;
  while (*p != '\0') {
    if (*p == ' ' || *p == '\t') {
      p++;
      continue;
    }
    if (isdigit(*p)) {
      int num = 0;
      while (isdigit(*p)) {
        num = num * 10 + (*p - '0');
        p++;
      }
      st.push(num);
    } else if (isOpMember(*p)) {
      int b = st.top();
      st.pop();
      int a = st.top();
      st.pop();
      st.push(Operation(*p, a, b));
      p++;
    } else {
      p++;
    }
  }
  return st.top();
}

int main() {
  int passed = 0;
  int failed = 0;

  struct TestCase {
    const char *expr;
    int expected;
  };

  TestCase tests[] = {
    {"56 10 + 20 5 / 2 * - 3 +", 61},
    {"3 4 + 5 *", 35},
    {"10 2 3 + *", 50},
    {"1 2 + 3 4 + *", 21},
    {"100 20 - 10 2 * /", 4},
  };

  for (const auto &tc : tests) {
    int result = evaluation(tc.expr);
    if (result == tc.expected) {
      std::cout << "[PASS] " << tc.expr << " = " << result << std::endl;
      passed++;
    } else {
      std::cout << "[FAIL] " << tc.expr << " expected " << tc.expected
                << " but got " << result << std::endl;
      failed++;
    }
  }

  std::cout << std::endl
            << passed << " passed, " << failed << " failed" << std::endl;
  return failed > 0 ? 1 : 0;
}
