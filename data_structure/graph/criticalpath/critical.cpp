#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

// 定义边结构体（活动）
struct Edge {
  int to;     // 目标顶点（事件）
  int weight; // 权重（活动持续时间）
  Edge(int t, int w) : to(t), weight(w) {}
};

// 关键路径算法封装函数
void criticalPath(int n, vector<vector<Edge>> &graph) {
  vector<int> inDegree(n, 0); // 记录每个顶点的入度

  // 1. 统计所有顶点的入度
  for (int u = 0; u < n; ++u) {
    for (const auto &edge : graph[u]) {
      inDegree[edge.to]++;
    }
  }

  queue<int> q;
  stack<int> topoStack; // 用于保存拓扑序列，方便后续逆向遍历计算 vl
  vector<int> ve(n, 0); // 事件最早发生时间，初始化为0

  // 将所有入度为 0 的顶点入队
  for (int i = 0; i < n; ++i) {
    if (inDegree[i] == 0) {
      q.push(i);
    }
  }

  int count = 0; // 记录加入拓扑序列的顶点数

  // 2. 拓扑排序 (计算 ve 数组)
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    topoStack.push(u); // 压入拓扑栈
    count++;

    // 遍历所有邻接边
    for (const auto &edge : graph[u]) {
      int v = edge.to;
      int w = edge.weight;

      // 更新终点的最早发生时间
      if (ve[u] + w > ve[v]) {
        ve[v] = ve[u] + w;
      }

      // 入度减1，若为0则入队
      inDegree[v]--;
      if (inDegree[v] == 0) {
        q.push(v);
      }
    }
  }

  // 判断是否存在环
  if (count < n) {
    cout << "错误：图中存在环，无法进行拓扑排序，工程不可行！" << endl;
    return;
  }

  // 获取工程总耗时（即拓扑序列最后一个节点的最早发生时间，也可能是整个图中 ve
  // 的最大值）
  int max_ve = 0;
  for (int i = 0; i < n; ++i) {
    max_ve = max(max_ve, ve[i]);
  }

  // 3. 逆向拓扑排序 (计算 vl 数组)
  // 初始化最晚发生时间为工程总耗时
  vector<int> vl(n, max_ve);

  while (!topoStack.empty()) {
    int u = topoStack.top();
    topoStack.pop();

    for (const auto &edge : graph[u]) {
      int v = edge.to;
      int w = edge.weight;
      // 更新起点的最晚发生时间
      if (vl[v] - w < vl[u]) {
        vl[u] = vl[v] - w;
      }
    }
  }

  // 4. 寻找并输出关键活动/关键路径
  cout << "工程总最短耗时: " << max_ve << endl;
  cout << "关键路径(关键活动)如下:" << endl;

  // 遍历所有边，计算 e 和 l
  for (int u = 0; u < n; ++u) {
    for (const auto &edge : graph[u]) {
      int v = edge.to;
      int w = edge.weight;

      int e = ve[u];     // 活动最早开始时间
      int l = vl[v] - w; // 活动最晚开始时间

      // 如果最早开始时间 == 最晚开始时间，则为关键活动
      if (e == l) {
        cout << "顶点 " << u << " -> 顶点 " << v << " (权重: " << w << ")"
             << endl;
      }
    }
  }
}

int main() {
  /*
    构建测试AOE网 (顶点0-5表示事件)
    (0) --3--> (1) --2--> (3) --4--> (5)
     |          |          ^
     |2         |2         |2
     v          v          |
    (2) --3--> (4) --------+
  */
  int n = 6; // 顶点数
  vector<vector<Edge>> graph(n);

  graph[0].emplace_back(1, 3);
  graph[0].emplace_back(2, 2);
  graph[1].emplace_back(3, 2);
  graph[1].emplace_back(4, 2);
  graph[2].emplace_back(4, 3);
  graph[3].emplace_back(5, 4);
  graph[4].emplace_back(5, 2);

  criticalPath(n, graph);

  return 0;
}
