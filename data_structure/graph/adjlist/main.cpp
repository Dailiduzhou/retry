/*
 *   测试图:
 *
 *       0
 *      / \
 *     1---2---5
 *    / \
 *   3   4
 *
 *   邻接表:
 *   0 -> 2 -> 1
 *   1 -> 4 -> 3 -> 2 -> 0
 *   2 -> 5 -> 1 -> 0
 *   3 -> 1
 *   4 -> 1
 *   5 -> 2
 */

#include "graph.h"
#include <iostream>
#include <cassert>
using namespace std;

bool visit(VNode v) {
  cout << v.data << " ";
  return true;
}

void PrintAdjList(const ALGraph &G) {
  for (int i = 0; i < G.vexnum; i++) {
    cout << G.vertices[i].data << ":";
    for (ArcNode *p = G.vertices[i].firstarc; p; p = p->nextarc) {
      cout << " " << G.vertices[p->adjvex].data;
    }
    cout << endl;
  }
}

int main() {
  ALGraph G;
  G.kind = GraphKind::AG;
  G.vexnum = 0;
  G.arcnum = 0;

  vector<VNode> V;
  for (int i = 0; i < 6; i++) {
    VNode v;
    v.data = i;
    v.firstarc = nullptr;
    V.push_back(v);
  }

  vector<pair<VNode, VNode>> VR;
  VR.push_back({V[0], V[1]});
  VR.push_back({V[0], V[2]});
  VR.push_back({V[1], V[2]});
  VR.push_back({V[1], V[3]});
  VR.push_back({V[1], V[4]});
  VR.push_back({V[2], V[5]});

  CreateGraph(G, V, VR);

  cout << "=== CreateGraph ===" << endl;
  cout << "Vexnum: " << G.vexnum << " Arcnum: " << G.arcnum << endl;
  PrintAdjList(G);

  // === LocateVex ===
  cout << endl << "=== LocateVex ===" << endl;
  cout << "LocateVex(3) = " << LocateVex(G, 3) << endl;
  cout << "LocateVex(9) = " << LocateVex(G, 9) << " (not found)" << endl;

  // === GetVex ===
  cout << endl << "=== GetVex ===" << endl;
  VNode tmp = {2};
  cout << "GetVex(V[2]) = " << GetVex(G, tmp) << endl;

  // === PutVex ===
  cout << endl << "=== PutVex ===" << endl;
  tmp = {3};
  cout << "PutVex(V[3], 33)" << endl;
  PutVex(G, tmp, 33);
  PrintAdjList(G);
  PutVex(G, tmp, 3); // restore

  // === FirstAdjVex ===
  cout << endl << "=== FirstAdjVex ===" << endl;
  tmp = {0};
  VNode *adj = FirstAdjVex(G, tmp);
  cout << "FirstAdjVex(0) = " << (adj ? to_string(adj->data) : "null") << endl;
  tmp = {3};
  VNode *adj3 = FirstAdjVex(G, tmp);
  cout << "FirstAdjVex(3) = " << (adj3 ? to_string(adj3->data) : "null") << endl;

  // === NextAdjVex ===
  cout << endl << "=== NextAdjVex ===" << endl;
  VNode v0 = {0}, v2 = {2};
  VNode *next = NextAdjVex(G, v0, v2);
  cout << "NextAdjVex(0, 2) = " << (next ? to_string(next->data) : "null") << endl;

  // === InsertVex ===
  cout << endl << "=== InsertVex ===" << endl;
  VNode v6 = {6};
  InsertVex(G, v6);
  cout << "After InsertVex(6):" << endl;
  PrintAdjList(G);

  // === InsertArc ===
  cout << endl << "=== InsertArc ===" << endl;
  InsertArc(G, v6, V[0]);
  InsertArc(G, v6, V[5]);
  cout << "After InsertArc(6, 0) and InsertArc(6, 5):" << endl;
  PrintAdjList(G);

  // === DeleteArc ===
  cout << endl << "=== DeleteArc ===" << endl;
  DeleteArc(G, v6, V[5]);
  cout << "After DeleteArc(6, 5):" << endl;
  PrintAdjList(G);

  // === DeleteVex ===
  cout << endl << "=== DeleteVex ===" << endl;
  DeleteVex(G, v6);
  cout << "After DeleteVex(6):" << endl;
  PrintAdjList(G);
  cout << "Vexnum: " << G.vexnum << " Arcnum: " << G.arcnum << endl;

  // === Traverse again ===
  cout << endl << "=== DFS & BFS ===" << endl;
  cout << "DFS: ";
  DFSTraverse(G, V[0], visit);
  cout << endl;
  cout << "BFS: ";
  BFSTraverse(G, V[0], visit);
  cout << endl;

  DestroyGraph(G);
  cout << endl << "=== DestroyGraph ===" << endl;
  cout << "vexnum=" << G.vexnum << " arcnum=" << G.arcnum << endl;

  return 0;
}
