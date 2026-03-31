#include "sqlist.h"

void SelectSort(SqList &L) {
  RcdType W;
  for (int i = 1; i < L.length; i++) {
    int j = i;
    for (int k = i + 1; k <= L.length; ++k) {
      if (L.r[k].key < L.r[j].key) {
        j = k;
      }
    }
    if (j != i) {
      W = L.r[j];
      L.r[j] = L.r[i];
      L.r[i] = W;
    }
  }
}
