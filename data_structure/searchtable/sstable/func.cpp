#include "indextable.h"
#include "sstable.h"

void Create(SSTable &ST, int n) {
  ST.length = n;
  ElemType *tmp = ST.elem;
  ST.elem = new ElemType[n + 1]();
  delete[] tmp;
}

void Destroy(SSTable &ST) {
  ST.length = 0;
  delete[] ST.elem;
}

int Search_Seq(const SSTable &ST, KeyType kval) {
  ST.elem[0].key = kval;
  int i = ST.length;
  for (; ST.elem[i].key != kval; --i) {
  }
  return i;
}

int Search_Bin(const SSTable &ST, KeyType kval) {
  int low = 1;
  int high = ST.length;
  while (low <= high) {
    int mid = (high - low) / 2 + low;
    if (ST.elem[mid].key == kval) {
      return mid;
    } else if (ST.elem[mid].key < kval) {
      low = mid + 1;
    } else {
      high = low - 1;
    }
  }
  return 0;
}

int Search_Idx(SSTable &ST, const indexTable &ID, KeyType kval) {
  int low = 0;
  int high = ID.length - 1;
  bool found = false;
  if (kval > ID.elem[high].key) {
    return 0;
  }

  while (low <= high && !found) {
    int mid = (high - low) / 2 + low;
    if (kval < ID.elem[mid].key) {
      high = mid - 1;
    } else if (kval > ID.elem[mid].key) {
      low = mid + 1;
    } else {
      found = true;
      low = mid;
    }
  }

  int s = ID.elem[low].stadr;
  int t;
  if (low < ID.length - 1) {
    t = ID.elem[low + 1].stadr - 1;
  } else {
    t = ID.length;
  }

  if (kval == ST.elem[t].key) {
    return t;
  } else {
    ST.elem[0] = ST.elem[t];
    ST.elem[t].key = kval;
    int k;
    for (k = s; ST.elem[k].key != kval; ++k) {
    }
    ST.elem[t] = ST.elem[0];
    if (k != t) {
      return k;
    }

    return 0;
  }
}
