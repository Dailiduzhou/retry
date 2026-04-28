#include "heap.h"

void sift_down(HeapType &H, int n, int i) {
  while (true) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int ma = i;
    if (l < n && H[l] > H[ma]) {
      ma = l;
    }
    if (r < n && H[r] > H[ma]) {
      ma = r;
    }
    if (ma == i) {
      break;
    }

    std::swap(H[i], H[ma]);
    i = ma;
  }
}

void heapsort(HeapType &h) {
  for (int i = h.size() / 2 - 1; i >= 0; --i) {
    sift_down(h, h.size(), i);
  }

  for (int i = h.size() - 1; i > 0; --i) {
    std::swap(h[0], h[i]);
    sift_down(h, i, 0);
  }
}
