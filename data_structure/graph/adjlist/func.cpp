#include "graph.h"
#include <cstddef>
#include <iostream>
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
