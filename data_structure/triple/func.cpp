#include "triple.h"
int num[100], rpos[100];

void createRpos(TSMatrix M) {
  for (int col = 1; col <= M.nu; ++col) {
    num[col] = 0;
  }

  for (int t = 1; t <= M.tu; ++t) {
    ++num[M.data[t].j];
  }

  rpos[1] = 1;
  for (int col = 2; col <= M.nu; ++col) {
    rpos[col] = rpos[col - 1] + num[col - 1];
  }
}

status FastTransposeSMatrix(TSMatrix M, TSMatrix &T) {
  T.mu = M.nu;
  T.nu = M.mu;
  T.tu = M.tu;

  if (T.tu) {
    createRpos(M);
    for (int p = 1; p <= M.tu; ++p) {
      int col = M.data[p].j;
      int q = rpos[col];
      T.data[q].i = M.data[p].j;
      T.data[q].j = M.data[p].i;
      T.data[q].e = M.data[p].e;
      ++rpos[col];
    }
  }
  return status::OK;
}
