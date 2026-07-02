#include "triple.h"
#include <cstring>
#include <iostream>
int num[100], rpos[100];

// 计算 rpos 表
// num[col]  : 原矩阵第 col 列的非零元素个数
// rpos[col] : 原矩阵第 col 列的第一个非零元素,放在转置矩阵 T.data 中的起始下标
// 下标均从 1 开始(与 data[1..tu]、rpos[1..nu] 保持一致)
void createRpos(TSMatrix M) {
  // 第一遍:清零 num
  for (int col = 1; col <= M.nu; ++col) {
    num[col] = 0;
  }

  // 第二遍:遍历所有非零元素,统计各列出现次数
  for (int t = 1; t <= M.tu; ++t) {
    ++num[M.data[t].j];
  }

  // 第三遍:对 num 求前缀和,得到每列在 T.data 中的起始写入位置
  // rpos[1] = 1 表示第 1 列的第一个非零元素写到 T.data[1]
  // rpos[col] = rpos[col-1] + num[col-1] 表示第 col 列紧接第 col-1 列之后写入
  rpos[1] = 1;
  for (int col = 2; col <= M.nu; ++col) {
    rpos[col] = rpos[col - 1] + num[col - 1];
  }
}

// 朴素转置稀疏矩阵
// 思路:对原矩阵的每一列,从头到尾扫描整个三元组,挑出属于该列的元素,
//       行列互换后依次放入 T.data
// 时间复杂度 O(nu * tu):外层遍历 nu 列,内层每次都要扫一遍 tu 个非零元
// 适用场景:矩阵规模较小或非零元分布极端不均时,代码最简,无需额外辅助数组
status NaiveTransposeSMatrix(TSMatrix M, TSMatrix &T) {
  // 转置后行列互换,非零元个数不变
  T.mu = M.nu;
  T.nu = M.mu;
  T.tu = M.tu;

  // q 指向 T.data 下一个可写位置(从 1 开始,与 data[0] 保留不用保持一致)
  int q = 1;

  // 外层:按"原列号"从小到大处理,保证 T.data 自然按行优先有序
  for (int col = 1; col <= M.nu; ++col) {
    // 内层:在 M.data 中找出所有 j == col 的元素
    for (int p = 1; p <= M.tu; ++p) {
      if (M.data[p].j == col) {
        // 行列互换:原 (i, j) 变成 (j, i),值不变
        T.data[q].i = M.data[p].j;
        T.data[q].j = M.data[p].i;
        T.data[q].e = M.data[p].e;
        ++q;
      }
    }
  }

  return status::OK;
}

// 快速转置稀疏矩阵
// 时间复杂度 O(nu + tu),相比朴素转置 O(nu * tu) 有显著提升
// 关键:在主转置循环前,先通过 createRpos 算出"原每列 → T.data 起始位置"的映射,
//      主循环每读到一个元素即可 O(1) 定位其写入位置,无需对每列再扫一遍
status FastTransposeSMatrix(TSMatrix M, TSMatrix &T) {
  // 转置后行数 = 原列数,列数 = 原行数,非零元个数不变
  T.mu = M.nu;
  T.nu = M.mu;
  T.tu = M.tu;

  if (T.tu) {
    // 预计算 rpos 表
    createRpos(M);

    // 主循环:依次处理 M.data 中的每个非零元
    for (int p = 1; p <= M.tu; ++p) {
      int col = M.data[p].j;   // 取出原列号 = 转置后的行号
      int q = rpos[col];       // 由 rpos 表 O(1) 定位该元素在 T.data 中的写入下标

      // 行列互换,完成转置
      T.data[q].i = M.data[p].j;
      T.data[q].j = M.data[p].i;
      T.data[q].e = M.data[p].e;

      // 关键步骤:把该列的"下一个空位"后移一位
      // rpos 在循环中被修改,这样下一个同列元素到来时,自动写到紧邻的下一格
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
