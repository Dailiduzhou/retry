#include "sqlist.h"
#include <vector>

using std::vector;
void merge(SqList &L, int left, int mid, int right) {
  vector<RcdType> tmp(right - left + 1);

  int i = left, j = mid + 1, k = 0;
  while (i <= mid && j <= right) {
    if (L.r[i].key <= L.r[j].key) {
      tmp[k++] = L.r[i++];
    } else {
      tmp[k++] = L.r[j++];
    }
  }

  while (i <= mid) {
    tmp[k++] = L.r[i++];
  }
  while (j <= right) {
    tmp[k++] = L.r[j++];
  }

  for (int k = 0; k < tmp.size(); ++k) {
    L.r[left + k] = tmp[k];
  }
}

void Mergesort(SqList &L, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;
  Mergesort(L, left, mid);
  Mergesort(L, mid + 1, right);

  merge(L, left, mid, right);
}
