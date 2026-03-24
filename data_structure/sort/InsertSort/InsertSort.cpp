#include "sqlist.h"

void InsertSort(SqList &L) {
  for (int i = 2; i < L.length; ++i) {
    RcdType base = L.r[i];
    int j = i - 1;
    while (j >= 0 && L.r[j].key > base.key) {
      L.r[j + 1] = L.r[j];
      j--;
    }
    L.r[j + 1] = base;
  }
}
