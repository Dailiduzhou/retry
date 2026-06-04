#include "triple.h"
#include <cstring>
#include <iostream>
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

// 转换为带rpos的矩阵
void TSMatrix2RLSMatrix(const TSMatrix &M, RLSMatrix &R) {
  R.mu = M.mu;
  R.nu = M.nu;
  R.tu = M.tu;

  int rowCount[MAXMN + 1] = {0};
  for (int i = 1; i <= R.tu; ++i) {
    R.data[i] = M.data[i];
    rowCount[R.data[i].i]++;
  }
  R.rpos[1] = 1;
  for (int i = 2; i <= R.mu; ++i) {
    R.rpos[i] = R.rpos[i - 1] + rowCount[i - 1];
  }
}

status matrixProduct(const TSMatrix &A, const TSMatrix &B, TSMatrix &C) {
  if (A.nu != B.mu) {
    std::cout << "Bad input" << std::endl;
    return status::ERR;
  }

  RLSMatrix RA = {}, RB = {};
  TSMatrix2RLSMatrix(A, RA);
  TSMatrix2RLSMatrix(B, RB);

  int m = RA.mu;
  int n = RB.nu;
  int temp[MAXMN] = {0};

  C.mu = m;
  C.nu = n;
  C.tu = 0;

  for (int i = 1; i <= m; ++i) {
    memset(temp, 0, sizeof(ElemType) * n);

    int startA = RA.rpos[i];
    int endA = (i == m) ? RA.tu + 1 : RA.rpos[i + 1];
    for (int p = startA; p < endA; ++p) {
      int t = RA.data[p].j;
      ElemType a_val = RA.data[p].e;

      int startB = RB.rpos[t];
      int endB = (t == RB.mu) ? RB.tu + 1 : RB.rpos[t + 1];
      for (int q = startB; q < endB; ++q) {
        int j = RB.data[q].j;
        temp[j - 1] += a_val * RB.data[q].e;
      }
    }

    for (int j = 1; j <= n; ++j) {
      if (temp[j - 1] != 0) {
        if (C.tu >= MAXSIZE) {
          return status::ERR;
        }
        C.data[++C.tu].i = i;
        C.data[C.tu].j = j;
        C.data[C.tu].e = temp[j - 1];
      }
    }
  }
  return status::OK;
}

status matrixAdd(const TSMatrix &A, const TSMatrix &B, TSMatrix &C) {
  if (A.mu != B.mu || A.nu != B.nu) {
    return status::ERR;
  }

  C.mu = A.mu;
  C.nu = A.nu;
  C.tu = 0;

  int pa = 1, pb = 1;
  // 假设是行先序排列，三种状况用于保持顺序
  while (pa <= A.tu && pb <= B.tu) {
    // A 先
    if (A.data[pa].i < B.data[pb].i ||
        (A.data[pa].i == B.data[pb].i && A.data[pa].j < B.data[pb].j)) {
      if (C.tu >= MAXSIZE)
        return status::ERR;
      C.data[++C.tu] = A.data[pa];
      ++pa;
      // A,B 位置相同
    } else if (A.data[pa].i == B.data[pb].i && A.data[pa].j == B.data[pb].j) {
      ElemType sum = A.data[pa].e + B.data[pb].e;
      if (sum != 0) {
        if (C.tu >= MAXSIZE)
          return status::ERR;
        C.data[++C.tu].i = A.data[pa].i;
        C.data[C.tu].j = A.data[pa].j;
        C.data[C.tu].e = sum;
      }
      ++pa;
      ++pb;
      // B先
    } else {
      if (C.tu >= MAXSIZE)
        return status::ERR;
      C.data[++C.tu] = B.data[pb];
      ++pb;
    }
  }

  while (pa <= A.tu) {
    if (C.tu >= MAXSIZE)
      return status::ERR;
    C.data[++C.tu] = A.data[pa];
    ++pa;
  }

  while (pb <= B.tu) {
    if (C.tu >= MAXSIZE)
      return status::ERR;
    C.data[++C.tu] = B.data[pb];
    ++pb;
  }

  return status::OK;
}
