#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string s;
  if (!(cin >> s))
    return 0;

  int n = s.length();

  vector<int> pos[26];

  for (int i = 0; i < 26; ++i) {
    pos[i].push_back(-1);
  }

  for (int i = 0; i < n; ++i) {
    pos[s[i] - 'a'].push_back(i);
  }

  for (int i = 0; i < 26; ++i) {
    pos[i].push_back(n);
  }

  // 注意：总分值可能非常大，超过 2^31-1，必须使用 long long 累加
  long long total_score = 0;

  // 遍历 a 到 z
  for (int i = 0; i < 26; ++i) {
    // 从下标 1 开始遍历到 size-2，只处理真实存在的字符，跳过两个虚拟哨兵
    for (size_t j = 1; j < pos[i].size() - 1; ++j) {
      // 左边可以选择的起点的数量
      long long left_choices = pos[i][j] - pos[i][j - 1];
      // 右边可以选择的终点的数量
      long long right_choices = pos[i][j + 1] - pos[i][j];

      // 累加该字符的贡献值
      total_score += left_choices * right_choices;
    }
  }

  cout << total_score << "\n";

  return 0;
}
