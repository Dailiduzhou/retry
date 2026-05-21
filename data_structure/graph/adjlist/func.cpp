#include "graph.h"
#include <cstddef>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
void CreateUDG(ALGraph &G) {
  int IncInfo;
  cin >> G.vexnum >> G.arcnum >> IncInfo;

  for (int i = 0; i < G.vexnum; ++i) {
    cin >> G.vertices[i].data;
    G.vertices[i].firstarc = NULL;
  }

  for (int k = 0; k < G.arcnum; ++k) {
    int v1;
    int v2;
    cin >> v1 >> v2;
    int i = LocateVex(G, v1);
    int j = LocateVex(G, v2);

    ArcNode *pi = new ArcNode();
    pi->adjvex = j;
    pi->nextarc = G.vertices[i].firstarc;
    G.vertices[i].firstarc = pi;

    ArcNode *pj = new ArcNode();
    pj->adjvex = i;
    pj->nextarc = G.vertices[j].firstarc;
    G.vertices[j].firstarc = pj;

    if (IncInfo) {
      int info;
      cin >> info;
      pj->info = pi->info = &info;
    }
  }
}

int LocateVex(const ALGraph &G, VertexType u) {
  for (int i = 0; i < G.vexnum; ++i) {
    if (G.vertices[i].data == u) {
      return i;
    }
  }
  return -1;
}

void InsertVex(ALGraph &G, VNode v) {
  G.vexnum++;
  if (G.vexnum >= MAX_VERTEX_NUM) {
    cout << "Vertices full\n";
    return;
  }
  G.vertices[G.vexnum] = v;
  v.firstarc = nullptr;
}

void InsertArc(ALGraph &G, VNode v, VNode w) {
  int vpos = LocateVex(G, v.data);
  int wpos = LocateVex(G, w.data);
  if (vpos == -1 || wpos == -1) {
    cout << "Invalid Vex\n";
    return;
  }

  ArcNode *p = G.vertices[vpos].firstarc;
  ArcNode *newarc = new ArcNode;
  newarc->nextarc = nullptr;
  if (!p) {
    G.vertices[vpos].firstarc = newarc;
    newarc->adjvex = vpos;
  }
  while (!p->nextarc) {
    p = p->nextarc;
  }
  G.arcnum++;

  p->nextarc = newarc;
  newarc->adjvex = wpos;

  if (G.kind == GraphKind::AG || G.kind == GraphKind::AN) {
    ArcNode *p = G.vertices[vpos].firstarc;
    ArcNode *newarc = new ArcNode;
    newarc->nextarc = nullptr;
    if (!p) {
      G.vertices[vpos].firstarc = newarc;
      newarc->adjvex = vpos;
    }
    while (!p->nextarc) {
      p = p->nextarc;
    }

    p->nextarc = newarc;
    newarc->adjvex = vpos;

    G.arcnum++;
  }
}

void CreateGraph(ALGraph &G, vector<VNode> V, vector<pair<VNode, VNode>> VR) {
  for (const auto &vex : V) {
    InsertVex(G, vex);
  }

  for (const auto &[v, w] : VR) {
    InsertArc(G, v, w);
  }
}

void DestroyGraph(ALGraph &G) {
  for (auto &vex : G.vertices) {
    ArcNode *p = vex.firstarc;
    while (!p) {
      InfoType *inf = p->info;
      p->info = nullptr;
      delete inf;
      p = p->nextarc;
      delete p;
    }
  }

  G.arcnum = 0;
  G.vexnum = 0;
}

VertexType GetVex(const ALGraph &G, VNode v) {
  int pos = LocateVex(G, v.data);
  if (pos != -1) {
    return G.vertices[pos].data;
  }
  return -1;
}
void PutVex(ALGraph &G, VNode v, VertexType value) {
  int pos = LocateVex(G, v.data);
  if (pos != -1) {
    G.vertices[pos].data = value;
  }
  return;
}

VNode *FirstAdjVex(const ALGraph &G, VNode v) {
  int pos = LocateVex(G, v.data);
  if (pos == -1) {
    return nullptr;
  }

  ArcNode *p = G.vertices[pos].firstarc;
  if (p) {
    return const_cast<VNode *>(&G.vertices[p->adjvex]);
  } else {
    return nullptr;
  }
}

VNode *NextAdjVex(const ALGraph &G, VNode v, VNode w) {
  int vpos = LocateVex(G, v.data);
  int wpos = LocateVex(G, w.data);
  if (vpos == -1 || wpos == -1) {
    return nullptr;
  }

  ArcNode *p = G.vertices[vpos].firstarc;
  while (p && p->adjvex != wpos) {
    p = p->nextarc;
  }

  if (p != nullptr && p->nextarc != nullptr) {
    int nextadj = p->nextarc->adjvex;
    return const_cast<VNode *>(&G.vertices[nextadj]);
  }

  return nullptr;
}

void DeleteArc(ALGraph &G, VNode v, VNode w) {
  int vpos = LocateVex(G, v.data);
  int wpos = LocateVex(G, w.data);
  if (vpos == -1 || wpos == -1) {
    return;
  }

  ArcNode *p = G.vertices[vpos].firstarc;
  ArcNode *pre = nullptr;
  while (p && p->adjvex != wpos) {
    pre = p;
    p = p->nextarc;
  }

  pre->nextarc = p->nextarc;
  delete p;

  if (G.kind == GraphKind::AG || G.kind == GraphKind::AN) {

    ArcNode *p = G.vertices[wpos].firstarc;
    ArcNode *pre = nullptr;
    while (p && p->adjvex != vpos) {
      pre = p;
      p = p->nextarc;
    }

    pre->nextarc = p->nextarc;
    delete p;
  }
}

void DeleteVex(ALGraph &G, VNode v) {
  int vpos = LocateVex(G, v.data);
  if (vpos == -1) {
    return;
  }

  ArcNode *p = G.vertices[vpos].firstarc;
  int delarc = 0;
  while (p) {
    ArcNode *tmp = p;
    p = p->nextarc;
    int wpos = tmp->adjvex;
    delete tmp;
    delarc++;

    ArcNode *q = G.vertices[wpos].firstarc;
    ArcNode *pre = nullptr;
    while (q && q->adjvex != vpos) {
      pre = q;
      q = q->nextarc;
    }
    if (q) {
      if (pre) {
        pre->nextarc = q->nextarc;
      } else {
        G.vertices[wpos].firstarc = q->nextarc;
      }
      delete q;
    }
  }
  G.vertices[vpos].firstarc = nullptr;
  G.arcnum -= delarc;

  for (int i = vpos; i < G.vexnum - 1; i++) {
    G.vertices[i] = G.vertices[i + 1];
  }

  for (int i = 0; i < G.vexnum - 1; i++) {
    for (ArcNode *k = G.vertices[i].firstarc; k; k = k->nextarc) {
      if (k->adjvex > vpos) {
        k->adjvex--;
      }
    }
  }

  G.vexnum--;
}

static void DFS(ALGraph &G, int v, vector<bool> &visited,
                bool (*visit)(VNode)) {
  visited[v] = true;
  visit(G.vertices[v]);
  for (ArcNode *p = G.vertices[v].firstarc; p; p = p->nextarc) {
    int w = p->adjvex;
    if (!visited[w]) {
      DFS(G, w, visited, visit);
    }
  }
}

void DFSTraverse(ALGraph &G, VNode v, bool (*visit)(VNode)) {
  vector<bool> visited(G.vexnum, false);
  int start = LocateVex(G, v.data);
  if (start != -1) {
    DFS(G, start, visited, visit);
  }
  for (int i = 0; i < G.vexnum; i++) {
    if (!visited[i]) {
      DFS(G, i, visited, visit);
    }
  }
}

static void BFS(ALGraph &G, int v, vector<bool> &visited,
                bool (*visit)(VNode)) {
  queue<int> q;
  visited[v] = true;
  q.push(v);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    visit(G.vertices[u]);
    for (ArcNode *p = G.vertices[u].firstarc; p; p = p->nextarc) {
      int w = p->adjvex;
      if (!visited[w]) {
        visited[w] = true;
        q.push(w);
      }
    }
  }
}

void BFSTraverse(ALGraph &G, VNode v, bool (*visit)(VNode)) {
  vector<bool> visited(G.vexnum, false);
  int start = LocateVex(G, v.data);
  if (start != -1) {
    BFS(G, start, visited, visit);
  }
  for (int i = 0; i < G.vexnum; i++) {
    if (!visited[i]) {
      BFS(G, i, visited, visit);
    }
  }
}
