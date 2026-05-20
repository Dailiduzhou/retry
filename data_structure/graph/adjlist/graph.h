#ifndef GRAPH_H_
#define GRAPH_H_

#include <climits>
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
#endif // !GRAPH_H_
