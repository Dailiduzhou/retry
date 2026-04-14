#include "xll.h"
#include <iostream>

void CrossSearch(CrossList &M, ElemType x) {
  for (int i = 0; i < M.m; i++) {
    OLNode *p = *(M.rhead + i);
    while (p) {
      if (p->e == x) {
        std::cout << '(' << p->i << ',' << p->j << ')' << std::endl;
      }
      p = p->rnext;
    }
  }
}
