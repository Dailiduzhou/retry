#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// Trie 树节点定义
struct Node {
  int next[26];
  int fail;
  int id; // 【修改 1】：将 count 改为 id，记录模式串的唯一编号

  Node() {
    fill(next, next + 26, 0);
    fail = 0;
    id = -1; // -1 表示当前节点不是任何模式串的结尾
  }
};

class ACAutomaton {
private:
  vector<Node> tr;

public:
  ACAutomaton() { tr.emplace_back(); }

  // 【修改 2】：插入时，额外传入一个 id 作为参数
  void insert(const string &s, int id) {
    int u = 0;
    for (char c : s) {
      int v = c - 'a';
      if (!tr[u].next[v]) {
        tr[u].next[v] = tr.size();
        tr.emplace_back();
      }
      u = tr[u].next[v];
    }
    // 如果有完全相同的模式串被重复插入，这里会被覆盖。
    // 若需支持重复插入相同单词，可以把 id 改为 vector<int>，这里简化为覆盖。
    tr[u].id = id;
  }

  // 构建 Fail 指针的代码与之前【完全一致】，不需要任何修改
  void build() {
    queue<int> q;
    for (int i = 0; i < 26; i++) {
      if (tr[0].next[i])
        q.push(tr[0].next[i]);
    }
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = 0; i < 26; i++) {
        if (tr[u].next[i]) {
          tr[tr[u].next[i]].fail = tr[tr[u].fail].next[i];
          q.push(tr[u].next[i]);
        } else {
          tr[u].next[i] = tr[tr[u].fail].next[i];
        }
      }
    }
  }

  // 【修改 3】：查询函数返回一个数组，记录每个 id 的出现次数
  vector<int> query(const string &t, int pattern_count) {
    // 初始化一个计分板，大小为模式串的数量，初始值为 0
    vector<int> freq(pattern_count, 0);
    int u = 0;

    for (char c : t) {
      u = tr[u].next[c - 'a'];

      int temp = u;
      // 【修改 4】：去掉了 == -1 就停止的限制，允许重复统计！
      while (temp != 0) {
        // 如果当前节点是一个模式串的结尾
        if (tr[temp].id != -1) {
          freq[tr[temp].id]++; // 对应的模式串频次 +1
        }
        temp = tr[temp].fail; // 沿着 fail 指针继续找更短的后缀
      }
    }
    return freq;
  }
};

int main() {
  ACAutomaton ac;

  // 我们用一个 vector 保存所有的模式串，下标恰好可以作为它们的 ID
  vector<string> patterns = {"he", "she", "his", "hers", "s"};

  for (int i = 0; i < patterns.size(); i++) {
    ac.insert(patterns[i], i); // 传入字符串和它的 ID (i)
  }

  ac.build();

  // 文本串：其中 "she" 出现了 1 次，"he" 出现了 2 次，"s" 出现了 3 次
  string text = "ushershes";

  // 传入文本，以及模式串的总数 (为了初始化计分板)
  vector<int> result = ac.query(text, patterns.size());

  cout << "文本: \"" << text << "\"" << endl;
  cout << "--- 统计结果 ---" << endl;
  for (int i = 0; i < patterns.size(); i++) {
    cout << "模式串 \"" << patterns[i] << "\" 出现了 " << result[i] << " 次。"
         << endl;
  }

  return 0;
}
