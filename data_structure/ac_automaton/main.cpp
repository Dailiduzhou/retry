#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;
struct Node {
  int ch[26] = {0}, fail = 0;
  bool is_end = false;
} tr[MAXN];
int idx = 0;

void insert(const string &s) {
  int u = 0;
  for (char c : s) {
    int v = c - 'a';
    if (!tr[u].ch[v])
      tr[u].ch[v] = ++idx;
    u = tr[u].ch[v];
  }
  tr[u].is_end = true;
}

void build_fail() {
  queue<int> q;
  for (int c = 0; c < 26; ++c)
    if (tr[0].ch[c])
      q.push(tr[0].ch[c]);

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int c = 0; c < 26; ++c) {
      int v = tr[u].ch[c];
      if (v) {
        tr[v].fail = tr[tr[u].fail].ch[c];
        q.push(v);
      } else {
        tr[u].ch[c] = tr[tr[u].fail].ch[c]; // Trie图
      }
    }
  }
}

int query(const string &text) {
  int u = 0, cnt = 0;
  for (char c : text) {
    u = tr[u].ch[c - 'a'];
    for (int tmp = u; tmp && tr[tmp].is_end; tmp = tr[tmp].fail) {
      cnt++;                  // 匹配到一个模式串结尾
      tr[tmp].is_end = false; // 防重复计数（按需修改）
    }
  }
  return cnt;
}

int main() {
  vector<string> patterns = {"he", "she", "his", "hers"};
  for (auto &s : patterns)
    insert(s);
  build_fail();

  string text = "ahishers";
  cout << "匹配次数: " << query(text) << "\n";
  return 0;
}
