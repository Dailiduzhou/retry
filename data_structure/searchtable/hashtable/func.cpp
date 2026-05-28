#include "hashtable.h"

int Hash(int kval) { return kval % hashsize[0]; }

void collision(int &p, int collisions) {
  int flag = (collisions % 2) ? -1 : 1;
  int base = collisions / 2 + 1;
  int offset = flag * base * base;
  p = (p + offset + hashsize[0]) % hashsize[0];
}

Status SearchHash(const HashTable &H, KeyType kval, int &p, int &c) {
  p = Hash(kval);
  int original = p;
  int size = hashsize[H.sizeindex];
  while (H.elem[p].key != NULLKEY && (H.elem[p].key != kval) && c < size) {
    p = original;
    collision(p, ++c);
  }

  if (H.elem[p].key == kval) {
    return Status::SUCCESS;
  } else {
    return Status::UNSUCCESS;
  }
}

void RecreateHashTable(HashTable &H) {
  int old_size = hashsize[H.sizeindex];
  ElemType *old_elem = H.elem;

  ++H.sizeindex;
  H.count = 0;
  int new_size = hashsize[H.sizeindex];
  H.elem = new ElemType[new_size];
  for (int i = 0; i < new_size; ++i) {
    H.elem[i].key = NULLKEY;
  }

  for (int i = 0; i < old_size; ++i) {
    if (old_elem[i].key != NULLKEY) {
      InsertHash(H, old_elem[i]);
    }
  }

  delete[] old_elem;
}

Status InsertHash(HashTable &H, ElemType e) {
  int c = 0;
  int p = 0;
  if (SearchHash(H, e.key, p, c) == Status::SUCCESS) {
    return Status::DUPLICATE;
  } else if (c < hashsize[H.sizeindex] / 2) {
    H.elem[p] = e;
    ++H.count;
    return Status::SUCCESS;
  } else {
    RecreateHashTable(H);
    return InsertHash(H, e);
  }
}
