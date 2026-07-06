#include <cstdio>
#include <vector>
using namespace std;

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

int main(int argc, char **argv) {
  int n, m;
  scanf("%d %d", &n, &m);
  UnionFind uf(n + 1);
  for (int i = 0; i < m; i++) {
    int op, x, y;
    scanf("%d %d %d", &op, &x, &y);
    if (op == 1)
      uf.unite(x, y);
    else
      puts(uf.find(x) == uf.find(y) ? "YES" : "NO");
  }
  return 0;
}
