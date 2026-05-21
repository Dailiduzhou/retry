#include <bits/stdc++.h>
#include <queue>
#include <vector>

using namespace std;

vector<int> getBFS(const vector<vector<int>> &graph, int vi) {
  int len = graph.size();
  vector<bool> visited(len, false);
  vector<int> res;
  visited[vi] = true;
  queue<int> que;
  que.push(vi);
  while (!que.empty()) {
    int now = que.front();
    que.pop();
    res.push_back(now);
    for (const auto &vert : graph[now]) {
      if (visited[vert]) {
        continue;
      }
      que.push(vert);
      visited[vert] = true;
    }
  }
  return res;
}
