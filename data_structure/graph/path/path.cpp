#include <climits>
#include <vector>
using namespace std;

const int IFINITY = INT_MAX;
class UnionFind {
  vector<int> parent, rank;

public:
  UnionFind(int n) : parent(n), rank(n, 0) {
    for (int i = 0; i < n; i++)
      parent[i] = i;
  }
  int find(int x) {
    if (parent[x] != x)
      parent[x] = find(parent[x]);
    return parent[x];
  }
  bool unite(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rx == ry)
      return false;
    if (rank[rx] < rank[ry])
      parent[rx] = ry;
    else if (rank[rx] > rank[ry])
      parent[ry] = rx;
    else {
      parent[ry] = rx;
      rank[rx]++;
    }
    return true;
  }
};

bool haspath_dfs(const vector<vector<int>> &graph, int from, int to,
                 vector<bool> &visited) {
  if (from == to) {
    return true;
  }

  UnionFind uf(graph.size());
  for (int i = 0; i < graph.size(); ++i) {
    for (int j = 0; j < graph[0].size(); ++j) {
      uf.unite(i, j);
    }
  }

  return uf.find(from) == uf.find(to);
}

bool dfs(const vector<vector<int>> &graph, int current, int target, int k,
         vector<bool> &visited) {
  if (k == 0) {
    return current == target;
  }

  visited[current] = true;

  for (const auto &adjvex : graph[current]) {
    if (!visited[adjvex]) {
      if (dfs(graph, adjvex, target, k - 1, visited)) {
        return true;
      }
    }
  }

  visited[current] = false;
  return false;
}

bool hasSimplepath(const vector<vector<int>> &graph, int current, int target,
                   int k) {
  int vexnum = graph.size();
  if (k < 0 || current < 0 || target < 0 ||
      current >= vexnum || target >= vexnum) {
    return false;
  }
  vector<bool> visited(vexnum, false);

  return dfs(graph, current, target, k, visited);
}

#include <cassert>
#include <iostream>

void test_haspath_dfs() {
  /*
   * Graph 1: two connected nodes
   *   0 --- 1
   *   adjacency list: 0:[1], 1:[0]
   */
  {
    vector<vector<int>> g = {{1}, {0}};
    vector<bool> visited(2, false);
    assert(haspath_dfs(g, 0, 1, visited) == true);
    assert(haspath_dfs(g, 1, 0, visited) == true);
  }

  /*
   * Graph 2: line of three nodes
   *   0 --- 1 --- 2
   *   adjacency list: 0:[1], 1:[0,2], 2:[1]
   */
  {
    vector<vector<int>> g = {{1}, {0, 2}, {1}};
    vector<bool> visited(3, false);
    assert(haspath_dfs(g, 0, 2, visited) == true);
  }

  /*
   * Graph 3: isolated nodes (no edges)
   *   0    1
   *   adjacency list: 0:[], 1:[]
   */
  {
    vector<vector<int>> g = {{}, {}};
    vector<bool> visited(2, false);
    assert(haspath_dfs(g, 0, 1, visited) == false);
  }

  /*
   * Graph 4: triangle (3-cycle)
   *   0 --- 1
   *    \   /
   *      2
   *   adjacency list: 0:[1,2], 1:[0,2], 2:[0,1]
   */
  {
    vector<vector<int>> g = {{1, 2}, {0, 2}, {0, 1}};
    vector<bool> visited(3, false);
    assert(haspath_dfs(g, 0, 2, visited) == true);
  }

  cout << "haspath_dfs: all tests passed" << endl;
}

void test_hasSimplepath() {
  /*
   * Graph 5: line of 4 nodes
   *   0 --- 1 --- 2 --- 3
   *   adjacency list: 0:[1], 1:[0,2], 2:[1,3], 3:[2]
   */
  {
    vector<vector<int>> g = {{1}, {0, 2}, {1, 3}, {2}};
    assert(hasSimplepath(g, 0, 3, 3) == true);
    assert(hasSimplepath(g, 0, 3, 1) == false);
    assert(hasSimplepath(g, 0, 3, 2) == false);
    assert(hasSimplepath(g, 0, 2, 2) == true);
  }

  /*
   * Graph 6: triangle with tail
   *      0 --- 1
   *      | \   |
   *      |   2 |
   *      | /   |
   *      3     4
   *   adjacency list: 0:[1,2,3], 1:[0,2,4], 2:[0,1,3,4], 3:[0,2], 4:[1,2]
   */
  {
    vector<vector<int>> g = {
        {1, 2, 3}, {0, 2, 4}, {0, 1, 3, 4}, {0, 2}, {1, 2}};
    assert(hasSimplepath(g, 0, 4, 2) == true);
    assert(hasSimplepath(g, 3, 4, 3) == true);
    assert(hasSimplepath(g, 3, 4, 1) == false);
    assert(hasSimplepath(g, 3, 4, 4) == true);
  }

  /*
   * Graph 7: self-loop edge case (simple path forbids revisiting 0)
   *   0 -- (self-loop)
   *   adjacency list: 0:[0]
   */
  {
    vector<vector<int>> g = {{0}};
    assert(hasSimplepath(g, 0, 0, 0) == true);
    assert(hasSimplepath(g, 0, 0, 1) == false);
  }

  /*
   * Graph 8: star graph (center 0 connected to all)
   *       1
   *       |
   *   3 - 0 - 2
   *   adjacency list: 0:[1,2,3], 1:[0], 2:[0], 3:[0]
   */
  {
    vector<vector<int>> g = {{1, 2, 3}, {0}, {0}, {0}};
    assert(hasSimplepath(g, 1, 2, 2) == true);
    assert(hasSimplepath(g, 1, 2, 1) == false);
    assert(hasSimplepath(g, 1, 3, 2) == true);
  }

  /*
   * Graph 9: invalid inputs (out-of-range vertices, negative k)
   */
  {
    vector<vector<int>> g = {{1}, {0}};
    assert(hasSimplepath(g, -1, 1, 1) == false);
    assert(hasSimplepath(g, 0, 1, -1) == false);
    assert(hasSimplepath(g, 0, 3, 1) == false);
  }

  cout << "hasSimplepath: all tests passed" << endl;
}

int main() {
  test_haspath_dfs();
  test_hasSimplepath();
  return 0;
}
