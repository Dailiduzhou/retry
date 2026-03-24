#include "sqlist.h"

void BubbleSort(SqList &L) {
  RcdType W;
  for (int i = L.length; i >= 1; --i) {
    for (int j = 0; j < i; ++j) {
      if (L.r[j].key > L.r[j + 1].key) {
        W = L.r[j + 1];
        L.r[j + 1] = L.r[j];
        L.r[j] = W;
      }
    }
  }
}
