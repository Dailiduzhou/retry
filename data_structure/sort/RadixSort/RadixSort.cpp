#include "sqlist_radix.h"

const int bitsnum = 10;
void RadixPass(RcdType A[], RcdType B[], int n, int i);

void RadixSort(SqList &L) {
  RcdType C[L.length];
  int i = bitsnum - 1;
  while (i >= 0) {
    RadixPass(L.r, C, L.length, i);
    --i;
    if (i >= 0) {
      RadixPass(C, L.r, L.length, i);
      --i;
    } else {
      for (int j = 0; j < L.length; ++j) {
        L.r[j] = C[j];
      }
    }
  }
}

void RadixPass(RcdType A[], RcdType B[], int n, int i) {
  KeysType count[RADIX];

  for (int j = 0; j < RADIX; ++j) {
    count[j] = 0;
  }

  for (int k = 0; k < n; ++k) {
    count[A[k].keys[i]]++;
  }

  for (int j = 1; j < RADIX; ++j) {
    count[j] += count[j - 1];
  }

  for (int k = n - 1; k >= 0; --k) {
    int j = A[k].keys[i];
    B[--count[j]] = A[k];
  }
}
