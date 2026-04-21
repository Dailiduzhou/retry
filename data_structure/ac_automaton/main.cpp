#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

/**
 * Trie 树节点定义
 *
 * AC 自动机 = Trie 树 + KMP 的失配指针思想
 * 它用于在 O(n + m + z) 时间内完成多模式串匹配
 *   n: 文本长度, m: 所有模式串总长度, z: 匹配次数
 */
struct Node {
  int next[26]; // 指向子节点的索引（假设只包含小写字母 a-z）
                // next[i] = 0 表示该子节点不存在
                // 在 build() 后会通过 Trie 图优化指向 fail 链上的对应节点

  int fail; // 失配指针（failure link）：
            // 指向当前字符串的最长真后缀，且该后缀也是某个模式串的前缀
            // 类比 KMP 的 next 数组，用于匹配失败时快速跳转

  int count; // 以当前节点结尾的模式串数量
             // 在 query() 中被复用：-1 表示已统计过，避免重复计数

  Node() {
    fill(next, next + 26, 0);
    fail = 0; // 根节点的 fail 指向自己（或 0 表示空）
    count = 0;
  }
};

class ACAutomaton {
private:
  vector<Node> tr;

public:
  ACAutomaton() {
    tr.emplace_back(); // 初始化根节点，索引为 0
  }

  /**
   * 第一步：插入模式串，构建基础的 Trie 树
   *
   * 工作原理：
   *   从根节点开始，逐个字符遍历模式串
   *   如果当前字符对应的子节点不存在，则创建新节点
   *   最后在当前节点标记 count++，表示有一个模式串在此结束
   *
   * 时间复杂度：O(|s|)，|s| 为模式串长度
   *
   * 注意：这里只是构建 Trie 树，fail 指针在 build() 中构建
   */
  void insert(const string &s) {
    int u = 0; // u 表示当前节点索引，从根节点 0 开始
    for (char c : s) {
      int v = c - 'a'; // 将字符映射到 0-25 的索引
      if (!tr[u].next[v]) {
        // 子节点不存在，创建新节点
        tr[u].next[v] = tr.size(); // 新节点的索引为当前 vector 大小
        tr.emplace_back();         // 在 vector 末尾添加新节点
      }
      u = tr[u].next[v]; // 移动到子节点，继续处理下一个字符
    }
    tr[u].count++; // 标记模式串在此节点结束，统计以该节点结尾的模式串数量
  }

  /**
   * 第二步：构建 Fail 指针（核心逻辑，使用 BFS）
   *
   * Fail 指针的定义：
   *   对于节点 u，fail[u] 表示 u 对应字符串的最长真后缀，
   *   且该后缀也是某个模式串的前缀（即在 Trie 中存在）
   *
   * 为什么用 BFS？
   *   按层遍历保证深度小的节点先处理，这样计算 fail 时，
   *   fail 指向的节点一定已经计算好了自己的 fail
   *
   * Trie 图优化（Automaton 化）：
   *   传统 AC 自动机查询时需要 while 循环跳 fail
   *   Trie 图优化将空指针指向 fail 链上的对应转移，
   *   使查询时可以直接 O(1) 状态转移，无需回溯
   *
   * 时间复杂度：O(26 × 节点数) = O(节点数)
   */
  void build() {
    queue<int> q;

    // 初始化：将根节点的直接子节点入队
    // 第一层节点的 fail 都指向根节点 0（它们的真后缀只有空串）
    for (int i = 0; i < 26; i++) {
      if (tr[0].next[i]) {
        q.push(tr[0].next[i]);
        // tr[tr[0].next[i]].fail 已经是 0（Node 构造函数初始化）
      }
    }

    while (!q.empty()) {
      int u = q.front(); // u: 当前处理的节点
      q.pop();

      for (int i = 0; i < 26; i++) { // 遍历所有可能的字符 'a'-'z'
        if (tr[u].next[i]) {
          // 情况 A：子节点存在（在 Trie 中有这个转移）
          //
          // 设 u 的子节点为 v（通过字符 c 到达）
          // v 的 fail 应该指向：从 fail[u] 出发，通过字符 c 能到达的节点
          //
          // 原理：
          //   如果 u 对应字符串 S，则 v 对应 S+c
          //   fail[u] 对应 S 的最长真后缀 P
          //   那么 S+c 的最长真后缀且是前缀的，就是 P+c（如果存在）
          //   如果不存在，继续跳 fail[fail[u]]，这就是 while 循环做的事情
          //   但得益于 Trie 图优化，tr[fail[u]].next[i] 已经指向了正确的位置
          //
          // 图示：
          //   root -> ... -> u --c--> v
          //    |             |
          //    |            fail[u]
          //    |             |
          //    +-----> ... -> ? --c--> fail[v] = tr[fail[u]][c]
          //
          tr[tr[u].next[i]].fail = tr[tr[u].fail].next[i];
          q.push(tr[u].next[i]);
        } else {
          // 情况 B：子节点不存在（Trie 图优化核心！）
          //
          // 将空指针指向 fail 节点的对应子节点，实现路径压缩
          // 这样查询时不需要 while 循环跳 fail，直接 O(1) 转移
          //
          // 原理：
          //   当前在节点 u，想走字符 c 但路不存在
          //   按照 fail 的定义，应该跳到 fail[u] 再尝试走 c
          //   我们将这个跳转直接记录在 next[i] 中
          //
          // 注意：这里依赖于 fail[u] 已经处理过（BFS 保证）
          tr[u].next[i] = tr[tr[u].fail].next[i];
        }
      }
    }
  }

  /**
   * 第三步：在文本 t 中查找出现的模式串总次数
   *
   * 工作原理：
   *   从根节点开始，逐个字符遍历文本
   *   由于 Trie 图优化，每个字符直接 O(1) 转移，无需回溯
   *   到达每个位置后，沿 fail 链收集所有以当前位置结尾的模式串
   *
   * 时间复杂度：O(|t| + 匹配次数)
   *   |t|: 文本长度，每个字符只处理一次
   *   匹配次数：所有模式串在文本中出现次数的总和
   *
   * 关于 count = -1 的优化：
   *   本实现使用了一种简单的去重策略：
   *   一旦某个节点的模式串被统计过，就将 count 设为 -1
   *   这样后续再访问到该节点时，while 循环会跳过
   *   这种优化适用于只关心"是否匹配"而不关心"匹配次数"的场景
   *
   * 注意：如果需要统计每个模式串的具体出现次数，
   *       需要改用其他方法（如记录每个模式串的 id，最后统一统计）
   */
  int query(const string &t) {
    int u = 0;   // 当前状态，从根节点开始
    int res = 0; // 匹配到的模式串总数

    for (char c : t) {
      // 得益于 Trie 图优化，这里直接 O(1) 转移状态
      // 不需要像传统 AC 自动机那样 while (u && !next[u][c]) u = fail[u];
      u = tr[u].next[c - 'a'];

      // 现在 u 指向当前已匹配前缀的最长后缀对应的节点
      // 需要沿 fail 链向上，找出所有以当前位置结尾的模式串
      //
      // 原理：如果节点 u 对应字符串 S，那么 fail[u] 对应 S 的一个真后缀
      //       如果 S 是某个模式串，那么该模式串在当前位置匹配
      //       继续跳 fail 可以检查更短的后缀是否也是模式串
      //
      // 示例：模式串有 "she", "he", "e"
      //       文本匹配到 "she" 时，u 指向 "she" 节点
      //       跳 fail 到 "he" 节点（"she" 的后缀）
      //       再跳 fail 到 "e" 节点（"he" 的后缀）

      int temp = u;
      while (temp != 0 && tr[temp].count != -1) {
        // temp != 0: 不统计根节点（根节点不代表任何字符）
        // count != -1: 避免重复统计同一位置的模式串

        res += tr[temp].count; // 累加以 temp 结尾的模式串数量
        tr[temp].count = -1;   // 标记为已访问，防止重复统计
        temp = tr[temp].fail;  // 沿 fail 指针继续检查更短的后缀
      }
    }
    return res;
  }
};

/**
 * 主函数：演示 AC 自动机的使用
 *
 * 示例说明：
 *   模式串："he", "she", "his", "hers"
 *   文本："ushers"
 *
 * 匹配过程分析：
 *   位置 0: 'u' - 无匹配
 *   位置 1: 's' - 无匹配
 *   位置 2: 'h' - 开始匹配 "he", "hers", "his"
 *   位置 3: 'e' - 匹配 "he" (位置 2-3)
 *   位置 4: 'r' - 继续匹配 "hers"
 *   位置 5: 's' - 匹配 "she" (位置 1-3, 通过 fail 指针发现)
 *                  匹配 "hers" (位置 2-5)
 *
 *   总计匹配："he", "she", "hers" = 3 个
 */
int main() {
  ACAutomaton ac;

  // 第一步：插入所有模式串，构建 Trie 树
  ac.insert("he");
  ac.insert("she");
  ac.insert("his");
  ac.insert("hers");

  // 第二步：构建 Fail 指针，完成 AC 自动机构建
  ac.build();

  // 第三步：在文本中查询模式串出现次数
  string text = "ushers";
  cout << "在文本 \"" << text << "\" 中共匹配到 " << ac.query(text)
       << " 个模式串。" << endl;
  // 预期输出: 3 (匹配到了 "she", "he", "hers")

  return 0;
}
