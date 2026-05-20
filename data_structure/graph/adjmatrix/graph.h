#ifndef GRAPH_H_
#define GRAPH_H_

#include <climits>
const int IFINITY = INT_MAX;
const int MAX_VERTEX_NUM = 20;
// {有向图，有向网，无向图，无向网}
enum class GraphKind : int { DG = 0, DN = 1, AG = 2, AN = 3 };

typedef int VRType;
typedef int InfoType;

typedef struct ArcCell {
  VRType adj;
  InfoType *info;
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef int VertexType;
typedef struct {
  VertexType vex[MAX_VERTEX_NUM];
  AdjMatrix arcs;
  int vexnum, arcnum;
  GraphKind kind;
} MGraph;
#endif // !GRAPH_H_
