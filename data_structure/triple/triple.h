#ifndef TRIPLE_H_
#define TRIPLE_H_

// triple represents a sparse matrix

const int MAXSIZE = 100;
const int MAXMN = 20;
typedef int ElemType;

typedef struct {
  int i, j;
  ElemType e;
} Triple;

typedef struct {
  Triple data[MAXSIZE + 1];
  int mu; // rows
  int nu; // cols
  int tu; // non-zeros
} TSMatrix;

typedef struct {
  Triple data[MAXSIZE + 1];
  int rpos[MAXMN + 1]; // 前缀和，每行开始元素的索引
  int mu;
  int nu;
  int tu;
} RLSMatrix;

#endif // !TRIPLE_H_
