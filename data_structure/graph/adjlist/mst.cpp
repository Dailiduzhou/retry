/*
 *   测试图 (无向网):
 *
 *       (2)
 *    0------1
 *    |\     |
 *   (3)\    |      1->2
 *    |  \   |       (1)
 *    | (4)  (4)
 *    |   \  |
 *    |    \ |
 *    2------3
 *       (1)
 *
 *   MST 期望: 0-1(2), 1-2(1), 2-3(1)  总权重 = 4
 */

#include "graph.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

struct Edge {
  int u, v, weight;
  bool operator<(const Edge &other) const { return weight < other.weight; }
};

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

int Kruskal(const ALGraph &G) {
  vector<Edge> edges;
  for (int i = 0; i < G.vexnum; i++) {
    for (ArcNode *p = G.vertices[i].firstarc; p; p = p->nextarc) {
      if (i < p->adjvex) {
        edges.push_back({i, p->adjvex, p->info ? *(p->info) : 1});
      }
    }
  }
  sort(edges.begin(), edges.end());

  UnionFind uf(G.vexnum);
  int total = 0;
  cout << "Kruskal MST edges:" << endl;
  for (auto &e : edges) {
    if (uf.unite(e.u, e.v)) {
      cout << "  " << G.vertices[e.u].data << " - " << G.vertices[e.v].data
           << " : " << e.weight << endl;
      total += e.weight;
    }
  }
  return total;
}

int Prim(const ALGraph &G, VNode start) {
  int n = G.vexnum;
  vector<bool> inMST(n, false);
  vector<int> key(n, INT_MAX);
  vector<int> parent(n, -1);

  int s = LocateVex(G, start.data);
  if (s == -1)
    return -1;
  key[s] = 0;

  for (int cnt = 0; cnt < n; cnt++) {
    int u = -1, minKey = INT_MAX;
    for (int j = 0; j < n; j++) {
      if (!inMST[j] && key[j] < minKey) {
        minKey = key[j];
        u = j;
      }
    }
    if (u == -1)
      break;
    inMST[u] = true;

    for (ArcNode *p = G.vertices[u].firstarc; p; p = p->nextarc) {
      int v = p->adjvex;
      int w = p->info ? *(p->info) : 1;
      if (!inMST[v] && w < key[v]) {
        key[v] = w;
        parent[v] = u;
      }
    }
  }

  int total = 0;
  cout << "Prim MST edges (start from " << start.data << "):" << endl;
  for (int i = 0; i < n; i++) {
    if (parent[i] != -1) {
      cout << "  " << G.vertices[parent[i]].data << " - " << G.vertices[i].data
           << " : " << key[i] << endl;
      total += key[i];
    }
  }
  return total;
}

static void addWeightedEdge(ALGraph &G, int u, int v, int w) {
  ArcNode *p = new ArcNode;
  p->adjvex = v;
  p->nextarc = G.vertices[u].firstarc;
  p->info = new int(w);
  G.vertices[u].firstarc = p;

  ArcNode *q = new ArcNode;
  q->adjvex = u;
  q->nextarc = G.vertices[v].firstarc;
  q->info = new int(w);
  G.vertices[v].firstarc = q;
  G.arcnum++;
}

int main() {
  ALGraph G;
  G.kind = GraphKind::AN;
  G.vexnum = 4;
  G.arcnum = 0;

  for (int i = 0; i < 4; i++) {
    G.vertices[i].data = i;
    G.vertices[i].firstarc = nullptr;
  }

  addWeightedEdge(G, 0, 1, 2);
  addWeightedEdge(G, 0, 2, 3);
  addWeightedEdge(G, 0, 3, 4);
  addWeightedEdge(G, 1, 2, 1);
  addWeightedEdge(G, 1, 3, 4);
  addWeightedEdge(G, 2, 3, 1);

  cout << "Adjacency list:" << endl;
  for (int i = 0; i < G.vexnum; i++) {
    cout << "  " << G.vertices[i].data << ":";
    for (ArcNode *p = G.vertices[i].firstarc; p; p = p->nextarc) {
      cout << " " << G.vertices[p->adjvex].data << "("
           << (p->info ? *(p->info) : 0) << ")";
    }
    cout << endl;
  }

  cout << endl;
  int totalK = Kruskal(G);
  cout << "Kruskal total weight: " << totalK << endl;

  cout << endl;
  VNode start = {0};
  int totalP = Prim(G, start);
  cout << "Prim total weight: " << totalP << endl;

  for (int i = 0; i < G.vexnum; i++) {
    ArcNode *p = G.vertices[i].firstarc;
    while (p) {
      ArcNode *tmp = p;
      p = p->nextarc;
      if (tmp->info) {
        delete tmp->info;
        tmp->info = nullptr;
      }
      delete tmp;
    }
  }

  return 0;
}
