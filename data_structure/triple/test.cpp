#include "triple.h"
#include <cstring>
#include <iostream>

extern int num[100], rpos[100];

static int passed = 0;
static int failed = 0;

static void resetRpos() {
  for (int i = 0; i < 100; ++i) num[i] = rpos[i] = 0;
}

static TSMatrix makeMatrix(int rows, int cols) {
  TSMatrix m;
  m.mu = rows;
  m.nu = cols;
  m.tu = 0;
  return m;
}

static void addElem(TSMatrix &m, int i, int j, ElemType e) {
  ++m.tu;
  m.data[m.tu].i = i;
  m.data[m.tu].j = j;
  m.data[m.tu].e = e;
}

static bool matrixEqual(const TSMatrix &a, const TSMatrix &b) {
  if (a.mu != b.mu || a.nu != b.nu || a.tu != b.tu) return false;
  for (int i = 1; i <= a.tu; ++i) {
    if (a.data[i].i != b.data[i].i ||
        a.data[i].j != b.data[i].j ||
        a.data[i].e != b.data[i].e)
      return false;
  }
  return true;
}

static void check(const char *name, bool cond) {
  if (cond) {
    ++passed;
  } else {
    std::cerr << "FAIL: " << name << std::endl;
    ++failed;
  }
}

static void printMatrix(const TSMatrix &m) {
  std::cout << "  mu=" << m.mu << " nu=" << m.nu << " tu=" << m.tu << std::endl;
  for (int i = 1; i <= m.tu; ++i) {
    std::cout << "  [" << i << "] i=" << m.data[i].i
              << " j=" << m.data[i].j
              << " e=" << m.data[i].e << std::endl;
  }
}

static void printDense(const TSMatrix &m) {
  std::cout << "  dense:" << std::endl;
  int idx = 1;
  for (int r = 1; r <= m.mu; ++r) {
    std::cout << "  ";
    for (int c = 1; c <= m.nu; ++c) {
      if (idx <= m.tu && m.data[idx].i == r && m.data[idx].j == c) {
        std::cout << m.data[idx].e << "\t";
        ++idx;
      } else {
        std::cout << "0\t";
      }
    }
    std::cout << std::endl;
  }
}

bool test_createRpos_basic() {
  TSMatrix m = makeMatrix(2, 3);
  addElem(m, 1, 2, 1);
  addElem(m, 1, 3, 3);
  addElem(m, 2, 1, 2);
  addElem(m, 2, 2, 2);
  resetRpos();
  createRpos(m);
  return rpos[1] == 1 && rpos[2] == 2 && rpos[3] == 4;
}

bool test_createRpos_empty() {
  TSMatrix m = makeMatrix(3, 3);
  m.tu = 0;
  resetRpos();
  createRpos(m);
  for (int col = 1; col <= 3; ++col) if (rpos[col] != 1) return false;
  return true;
}

bool test_fastTranspose_empty() {
  TSMatrix m = makeMatrix(3, 4);
  m.tu = 0;
  TSMatrix t;
  resetRpos();
  status st = FastTransposeSMatrix(m, t);
  return st == status::OK && t.mu == 4 && t.nu == 3 && t.tu == 0;
}

bool test_fastTranspose_single() {
  TSMatrix m = makeMatrix(2, 3);
  addElem(m, 1, 2, 5);
  TSMatrix t;
  resetRpos();
  FastTransposeSMatrix(m, t);
  return t.mu == 3 && t.nu == 2 && t.tu == 1 &&
         t.data[1].i == 2 && t.data[1].j == 1 && t.data[1].e == 5;
}

bool test_fastTranspose_multiple() {
  TSMatrix m = makeMatrix(3, 4);
  addElem(m, 1, 1, 1);
  addElem(m, 1, 4, 2);
  addElem(m, 2, 3, 3);
  addElem(m, 3, 1, 4);
  addElem(m, 3, 2, 5);
  addElem(m, 3, 4, 6);
  TSMatrix t;
  resetRpos();
  FastTransposeSMatrix(m, t);
  if (t.mu != 4 || t.nu != 3 || t.tu != 6) return false;
  TSMatrix expected = makeMatrix(4, 3);
  addElem(expected, 1, 1, 1);
  addElem(expected, 1, 3, 4);
  addElem(expected, 2, 3, 5);
  addElem(expected, 3, 2, 3);
  addElem(expected, 4, 1, 2);
  addElem(expected, 4, 3, 6);
  return matrixEqual(t, expected);
}

bool test_fastTranspose_identity() {
  TSMatrix m = makeMatrix(3, 3);
  addElem(m, 1, 1, 1);
  addElem(m, 2, 2, 1);
  addElem(m, 3, 3, 1);
  TSMatrix t;
  resetRpos();
  FastTransposeSMatrix(m, t);
  return matrixEqual(t, m);
}

bool test_ts2rls_preservesData() {
  TSMatrix m = makeMatrix(2, 3);
  addElem(m, 1, 2, 10);
  addElem(m, 1, 3, 20);
  addElem(m, 2, 1, 30);
  RLSMatrix r;
  TSMatrix2RLSMatrix(m, r);
  if (r.mu != 2 || r.nu != 3 || r.tu != 3) return false;
  for (int i = 1; i <= r.tu; ++i) {
    if (r.data[i].i != m.data[i].i || r.data[i].j != m.data[i].j || r.data[i].e != m.data[i].e)
      return false;
  }
  return true;
}

bool test_ts2rls_rpos() {
  TSMatrix m = makeMatrix(3, 4);
  addElem(m, 1, 1, 1);
  addElem(m, 1, 4, 2);
  addElem(m, 2, 3, 3);
  addElem(m, 3, 1, 4);
  addElem(m, 3, 2, 5);
  RLSMatrix r;
  TSMatrix2RLSMatrix(m, r);
  return r.rpos[1] == 1 && r.rpos[2] == 3 && r.rpos[3] == 4;
}

bool test_ts2rls_empty() {
  TSMatrix m = makeMatrix(3, 3);
  m.tu = 0;
  RLSMatrix r;
  TSMatrix2RLSMatrix(m, r);
  return r.mu == 3 && r.nu == 3 && r.tu == 0 &&
         r.rpos[1] == 1 && r.rpos[2] == 1 && r.rpos[3] == 1;
}

bool test_matrixProduct_simple() {
  // A(2x3):      B(3x2):      C=A*B(2x2):
  //  1  2  3      1  2         7  14
  //  4  5  6      3  0        19  32
  //                0  4

  TSMatrix a = makeMatrix(2, 3);
  addElem(a, 1, 1, 1);
  addElem(a, 1, 2, 2);
  addElem(a, 1, 3, 3);
  addElem(a, 2, 1, 4);
  addElem(a, 2, 2, 5);
  addElem(a, 2, 3, 6);

  TSMatrix b = makeMatrix(3, 2);
  addElem(b, 1, 1, 1);
  addElem(b, 1, 2, 2);
  addElem(b, 2, 1, 3);
  addElem(b, 3, 2, 4);

  TSMatrix c;
  status st = matrixProduct(a, b, c);
  if (st != status::OK) return false;

  std::cout << "[matrixProduct_simple] result:" << std::endl;
  printMatrix(c);
  printDense(c);

  TSMatrix expected = makeMatrix(2, 2);
  addElem(expected, 1, 1, 7);
  addElem(expected, 1, 2, 14);
  addElem(expected, 2, 1, 19);
  addElem(expected, 2, 2, 32);

  return matrixEqual(c, expected);
}

bool test_matrixProduct_identity() {
  // A(2x2):      B(2x2):      C=A*B(2x2):
  //  5  0        1  0         5  0
  //  0  7        0  1         0  7

  TSMatrix a = makeMatrix(2, 2);
  addElem(a, 1, 1, 5);
  addElem(a, 2, 2, 7);
  TSMatrix b = makeMatrix(2, 2);
  addElem(b, 1, 1, 1);
  addElem(b, 2, 2, 1);
  TSMatrix c;
  status st = matrixProduct(a, b, c);

  std::cout << "[matrixProduct_identity] result:" << std::endl;
  printMatrix(c);
  printDense(c);

  return st == status::OK && matrixEqual(c, a);
}

bool test_matrixProduct_sparseResult() {
  // A(2x2):      B(2x2):      C=A*B(2x2):
  //  1  0        0  0         0  0
  //  0  0        0  1         0  0

  TSMatrix a = makeMatrix(2, 2);
  addElem(a, 1, 1, 1);
  TSMatrix b = makeMatrix(2, 2);
  addElem(b, 2, 2, 1);
  TSMatrix c;
  status st = matrixProduct(a, b, c);

  std::cout << "[matrixProduct_sparseResult] result:" << std::endl;
  printMatrix(c);
  printDense(c);

  return st == status::OK && c.tu == 0;
}

bool test_matrixProduct_dimensionMismatch() {
  // A(2x3) * B(2x3): A.nu=3 != B.mu=2 -> ERR

  TSMatrix a = makeMatrix(2, 3);
  TSMatrix b = makeMatrix(2, 3);
  TSMatrix c;
  status st = matrixProduct(a, b, c);
  return st == status::ERR;
}

bool test_matrixProduct_emptyInput() {
  // A(2x3):  all zeros
  // B(3x2):  only B[1][1]=5
  // C=A*B should be all zeros -> tu=0

  TSMatrix a = makeMatrix(2, 3);
  TSMatrix b = makeMatrix(3, 2);
  addElem(b, 1, 1, 5);
  TSMatrix c;
  status st = matrixProduct(a, b, c);

  std::cout << "[matrixProduct_emptyInput] result:" << std::endl;
  printMatrix(c);
  printDense(c);

  return st == status::OK && c.tu == 0;
}

bool test_matrixAdd_basic() {
  // A(2x3):      B(2x3):      C=A+B(2x3):
  //  1  0  3      0  2  0      1  2  3
  //  0  4  0      5  0  6      5  4  6

  TSMatrix a = makeMatrix(2, 3);
  addElem(a, 1, 1, 1);
  addElem(a, 1, 3, 3);
  addElem(a, 2, 2, 4);

  TSMatrix b = makeMatrix(2, 3);
  addElem(b, 1, 2, 2);
  addElem(b, 2, 1, 5);
  addElem(b, 2, 3, 6);

  TSMatrix c;
  status st = matrixAdd(a, b, c);

  std::cout << "[matrixAdd_basic] result:" << std::endl;
  printMatrix(c);
  printDense(c);

  if (st != status::OK) return false;

  TSMatrix expected = makeMatrix(2, 3);
  addElem(expected, 1, 1, 1);
  addElem(expected, 1, 2, 2);
  addElem(expected, 1, 3, 3);
  addElem(expected, 2, 1, 5);
  addElem(expected, 2, 2, 4);
  addElem(expected, 2, 3, 6);

  return matrixEqual(c, expected);
}

bool test_matrixAdd_cancelToZero() {
  // A(2x2):      B(2x2):      C=A+B(2x2):
  //  3  0         -3  0         0  0
  //  0  5          0  2         0  7

  TSMatrix a = makeMatrix(2, 2);
  addElem(a, 1, 1, 3);
  addElem(a, 2, 2, 5);

  TSMatrix b = makeMatrix(2, 2);
  addElem(b, 1, 1, -3);
  addElem(b, 2, 2, 2);

  TSMatrix c;
  status st = matrixAdd(a, b, c);

  std::cout << "[matrixAdd_cancelToZero] result:" << std::endl;
  printMatrix(c);
  printDense(c);

  if (st != status::OK) return false;

  TSMatrix expected = makeMatrix(2, 2);
  addElem(expected, 2, 2, 7);

  return matrixEqual(c, expected);
}

bool test_matrixAdd_emptyPlusNonempty() {
  // A(2x2):  all zeros
  // B(2x2):  only B[1][2]=9
  // C=A+B = B

  TSMatrix a = makeMatrix(2, 2);
  TSMatrix b = makeMatrix(2, 2);
  addElem(b, 1, 2, 9);

  TSMatrix c;
  status st = matrixAdd(a, b, c);

  std::cout << "[matrixAdd_emptyPlusNonempty] result:" << std::endl;
  printMatrix(c);
  printDense(c);

  return st == status::OK && matrixEqual(c, b);
}

bool test_matrixAdd_dimensionMismatch() {
  // A(2x3) + B(3x2): dimensions differ -> ERR
  TSMatrix a = makeMatrix(2, 3);
  TSMatrix b = makeMatrix(3, 2);
  TSMatrix c;
  status st = matrixAdd(a, b, c);
  return st == status::ERR;
}

bool test_matrixAdd_bothEmpty() {
  // A(3x3) empty + B(3x3) empty -> tu=0

  TSMatrix a = makeMatrix(3, 3);
  TSMatrix b = makeMatrix(3, 3);
  TSMatrix c;
  status st = matrixAdd(a, b, c);

  std::cout << "[matrixAdd_bothEmpty] result:" << std::endl;
  printMatrix(c);
  printDense(c);

  return st == status::OK && c.tu == 0 && c.mu == 3 && c.nu == 3;
}

int main() {
  check("createRpos_basic", test_createRpos_basic());
  check("createRpos_empty", test_createRpos_empty());
  check("fastTranspose_empty", test_fastTranspose_empty());
  check("fastTranspose_single", test_fastTranspose_single());
  check("fastTranspose_multiple", test_fastTranspose_multiple());
  check("fastTranspose_identity", test_fastTranspose_identity());
  check("ts2rls_preservesData", test_ts2rls_preservesData());
  check("ts2rls_rpos", test_ts2rls_rpos());
  check("ts2rls_empty", test_ts2rls_empty());
  check("matrixProduct_simple", test_matrixProduct_simple());
  check("matrixProduct_identity", test_matrixProduct_identity());
  check("matrixProduct_sparseResult", test_matrixProduct_sparseResult());
  check("matrixProduct_dimensionMismatch", test_matrixProduct_dimensionMismatch());
  check("matrixProduct_emptyInput", test_matrixProduct_emptyInput());
  check("matrixAdd_basic", test_matrixAdd_basic());
  check("matrixAdd_cancelToZero", test_matrixAdd_cancelToZero());
  check("matrixAdd_emptyPlusNonempty", test_matrixAdd_emptyPlusNonempty());
  check("matrixAdd_dimensionMismatch", test_matrixAdd_dimensionMismatch());
  check("matrixAdd_bothEmpty", test_matrixAdd_bothEmpty());

  std::cout << passed << " passed, " << failed << " failed" << std::endl;
  return failed > 0 ? 1 : 0;
}
