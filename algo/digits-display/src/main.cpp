#include <iostream>
#include <vector>

using namespace std;

// 并查集查找函数
int find_root(int x, vector<int> &parent) {
  if (parent[x] == x)
    return x;
  return parent[x] = find_root(parent[x], parent);
}

int main() {
  // 建立 7x7 的邻接矩阵，0-6 分别代表 a-g
  int adj[7][7] = {0};

  // 定义一个 lambda 表达式方便加边（无向图）
  auto add_edge = [&](int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1;
  };

  // 连线逻辑：相邻的段之间建边
  add_edge(0, 1); // a - b
  add_edge(0, 5); // a - f
  add_edge(1, 2); // b - c
  add_edge(1, 6); // b - g
  add_edge(2, 3); // c - d
  add_edge(2, 6); // c - g
  add_edge(3, 4); // d - e
  add_edge(4, 5); // e - f
  add_edge(4, 6); // e - g
  add_edge(5, 6); // f - g

  int valid_count = 0;

  // 枚举所有状态，从 1 到 127 (即二进制 0000001 到 1111111)
  for (int i = 1; i < 128; ++i) {
    vector<int> active_nodes;
    // 提取当前状态下亮起的灯管
    for (int j = 0; j < 7; ++j) {
      if ((i >> j) & 1) {
        active_nodes.push_back(j);
      }
    }

    // 初始化并查集
    vector<int> parent(7);
    for (int j = 0; j < 7; ++j) {
      parent[j] = j;
    }

    // 遍历所有亮着的灯管，如果它们相邻，则合并集合
    for (int u : active_nodes) {
      for (int v : active_nodes) {
        if (adj[u][v]) {
          int root_u = find_root(u, parent);
          int root_v = find_root(v, parent);
          if (root_u != root_v) {
            parent[root_u] = root_v;
          }
        }
      }
    }

    // 检查当前状态下，亮着的灯管是否只构成 1 个连通块
    int roots = 0;
    for (int u : active_nodes) {
      if (parent[u] == u) {
        roots++;
      }
    }

    // 如果只有一个根节点，说明所有亮起的灯管连成了一片
    if (roots == 1) {
      valid_count++;
    }
  }

  cout << "可以表达的不同字符总数为: " << valid_count << endl;

  return 0;
}
