#ifndef GRAPH_H_
#define GRAPH_H_

#include <bits/stdc++.h>
#include <climits>
using namespace std;
const int MAX_VERTEX_NUM = 20;
// {有向图，有向网，无向图，无向网}
enum class GraphKind : int { DG = 0, DN = 1, AG = 2, AN = 3 };

typedef int VRType;
typedef int InfoType;

typedef struct ArcNode {
  int adjvex;
  struct ArcNode *nextarc;
  InfoType *info;
} ArcNode;

typedef int VertexType;

typedef struct VNode {
  VertexType data;
  ArcNode *firstarc;
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
  AdjList vertices;
  int vexnum, arcnum;
  GraphKind kind;
} ALGraph;

int LocateVex(const ALGraph &G, VertexType u);
VertexType GetVex(const ALGraph &G, VNode v);
void CreateGraph(ALGraph &G, vector<VNode> V, vector<pair<VNode, VNode>> VR);
void DestroyGraph(ALGraph &G);
void PutVex(ALGraph &G, VNode v, VertexType value);
VNode *FirstAdjVex(const ALGraph &G, VNode v);
VNode *NextAdjVex(const ALGraph &G, VNode v, VNode w);
void InsertVex(ALGraph &G, VNode v);
void DeleteVex(ALGraph &G, VNode v);
void InsertArc(ALGraph &G, VNode v, VNode w);
void DeleteArc(ALGraph &G, VNode v, VNode w);
void DFSTraverse(ALGraph &G, VNode v, bool (*visit)(VNode));
void BFSTraverse(ALGraph &G, VNode v, bool (*visit)(VNode));

#endif // !GRAPH_H_
