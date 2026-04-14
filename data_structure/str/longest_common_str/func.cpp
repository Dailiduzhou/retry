#include <iostream>
#include <string>
#include <vector>

using std::string;
// 返回两个字符串的最长公共子串（连续）
std::string longest_common_str(const std::string &s1, const std::string &s2) {
  if (s1.empty() || s2.empty()) {
    return "";
  }

  std::vector<std::vector<int>> dp(s1.size() + 1,
                                   std::vector<int>(s2.size() + 1, 0));

  int max_len = 0;
  int end_pos = 0; // 在 s1 中的结束位置（1-based）

  for (size_t i = 1; i <= s1.size(); ++i) {
    for (size_t j = 1; j <= s2.size(); ++j) {
      if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
        if (dp[i][j] > max_len) {
          max_len = dp[i][j];
          end_pos = static_cast<int>(i);
        }
      }
    }
  }

  return s1.substr(end_pos - max_len, max_len);
}

int main() {
  // 示例测试
  string a = "asdfgh";
  string b = "iuasdhll";
  string ans = longest_common_str(a, b);
  std::cout << "a = " << a << '\n';
  std::cout << "b = " << b << '\n';
  std::cout << "Longest common substring: " << ans << "\n\n";

  // 额外测试
  std::vector<std::pair<std::string, std::string>> tests = {
      {"abcdef", "zcdemf"}, // cde
      {"12345", "54321"},   // 任意长度为1的公共子串
      {"hello", "yellow"},  // ello
      {"abc", "def"},       // 空串
      {"aaaa", "aa"},       // aa
  };

  for (const auto &t : tests) {
    std::cout << "s1 = " << t.first << ", s2 = " << t.second << " -> "
              << longest_common_str(t.first, t.second) << '\n';
  }

  return 0;
}
