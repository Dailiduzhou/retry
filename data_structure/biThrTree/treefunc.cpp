#include "bithrtree.h"
#include <cstddef>

void InOrder(BiThrTree H, void (*visit)(BiThrTree)) {
  BiThrNode *p = H->succ;
  while (p != H) {
    visit(p);
    p = p->succ;
  }
}

void InOrderThreading(BiThrTree &H, BiThrTree T) {
  H = new BiThrNode;
  H->lchild = T;
  H->rchild = NULL;
  if (!T) {
    H->pred = H;
    H->succ = H;
  } else {
    BiThrNode *pre = H;
    InThreading(T, pre);
    pre->succ = H;
    H->pred = pre;
  }
}

void InThreading(BiThrTree p, BiThrTree &pre) {
  if (p) {
    InThreading(p->lchild, pre);
    pre->succ = p;
    p->pred = pre;
    pre = p;
    InThreading(p->rchild, pre);
  }
}
