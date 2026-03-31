#include "sqlist.h"
#include <utility>

using namespace std;
int Partition(SqList &L, int left, int right) {
  int i = left, j = right;
  while (i < j) {
    while (i < j && L.r[j].key >= L.r[left].key) {
      --j;
    }
    while (i < j && L.r[i].key <= L.r[left].key) {
      ++i;
    }
    swap(L.r[i], L.r[j]);
  }

  swap(L.r[i], L.r[left]);

  return i;
}

void QuickSort(SqList &L, int left, int right) {
  if (left >= right) {
    return;
  }

  int pivot = Partition(L, left, right);

  QuickSort(L, left, pivot - 1);
  QuickSort(L, pivot + 1, right);
}
