#include "sqlist.h"

void InsertSort(SqList &L) {
  for (int i = 2; i <= L.length; ++i) {
    L.r[0] = L.r[i];
    int j = i - 1;
    while (L.r[j].key > L.r[0].key) {
      L.r[j + 1] = L.r[j];
      j--;
    }
    L.r[j + 1] = L.r[0];
  }
}
