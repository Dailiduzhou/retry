#ifndef TRIPLE_H_
#define TRIPLE_H_

// triple represents a sparse matrix

const int MAXSIZE = 100;
const int MAXMN = 100;
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

enum class status : int { OK = 0, ERR = 1 };

void createRpos(TSMatrix M);
status FastTransposeSMatrix(TSMatrix M, TSMatrix &T);
void TSMatrix2RLSMatrix(const TSMatrix &M, RLSMatrix &R);
status matrixProduct(const TSMatrix &A, const TSMatrix &B, TSMatrix &C);

#endif // !TRIPLE_H_
