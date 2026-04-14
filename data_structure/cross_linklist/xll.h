#ifndef XLL_H_
#define XLL_H_

typedef int ElemType;

typedef struct OLNode {
  int i, j;
  ElemType e;
  struct OLNode *rnext, *cnext;
} OLNode, *OLink;

typedef struct {
  OLink *rhead, *chead;
  int m, n, t; // 行，列，非零元个数
} CrossList;
#endif // !XLL_H_
