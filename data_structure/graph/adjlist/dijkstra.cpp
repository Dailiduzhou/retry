/*
 *   Test graph (undirected network / AN):
 *
 *          (2)
 *       0------1
 *       |\     |
 *      (3)\    |      1->2
 *       |  \   |       (1)
 *       | (4)  (4)
 *       |   \  |
 *       |    \ |
 *       2------3
 *          (1)
 *
 *   Shortest paths from vertex 0:
 *     0->0: 0
 *     0->1: 2  (direct)
 *     0->2: 3  (direct)
 *     0->3: 4  (0->2->3, weight = 3 + 1)
 */

#include "graph.h"
#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Edge {
  int u, v, weight;
  bool operator<(const Edge &other) const { return weight < other.weight; }
};

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

vector<int> Dijkstra(const ALGraph &G, VNode src) {
  int n = G.vexnum;
  int s = LocateVex(G, src.data);
  vector<int> dist(n, INT_MAX);
  vector<bool> visited(n, false);

  dist[s] = 0;
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();

    if (visited[u])
      continue;
    visited[u] = true;

    for (ArcNode *p = G.vertices[u].firstarc; p; p = p->nextarc) {
      int v = p->adjvex;
      int w = p->info ? *(p->info) : 1;
      if (!visited[v] && dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        pq.push({dist[v], v});
      }
    }
  }

  return dist;
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

  cout << "Adjacency list (undirected network):" << endl;
  for (int i = 0; i < G.vexnum; i++) {
    cout << "  " << G.vertices[i].data << ":";
    for (ArcNode *p = G.vertices[i].firstarc; p; p = p->nextarc) {
      cout << " " << G.vertices[p->adjvex].data << "("
           << (p->info ? *(p->info) : 0) << ")";
    }
    cout << endl;
  }
  cout << endl;

  VNode src = {0};
  vector<int> dist = Dijkstra(G, src);
  cout << "Shortest distances from vertex 0:" << endl;
  for (int i = 0; i < G.vexnum; i++) {
    cout << "  dist[0->" << i << "] = ";
    if (dist[i] == INT_MAX)
      cout << "INF";
    else
      cout << dist[i];
    cout << endl;
  }

  int expected[] = {0, 2, 3, 4};
  bool pass = true;
  for (int i = 0; i < G.vexnum; i++) {
    if (dist[i] != expected[i]) {
      pass = false;
      cout << "FAIL: dist[0->" << i << "] = " << dist[i]
           << ", expected " << expected[i] << endl;
    }
  }
  if (pass)
    cout << "\nAll tests passed!" << endl;

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
