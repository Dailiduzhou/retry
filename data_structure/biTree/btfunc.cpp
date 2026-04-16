#include "bitree.h"
#include <cstddef>
#include <iostream>
using namespace std;
void Preorder(BiTree T, void (*visit)(BiTree)) {
  if (T) {
    visit(T);
    Preorder(T->lchild, visit);
    Preorder(T->rchild, visit);
  }
}

void CreatrebiTree(BiTree &T) {
  TElemType ch;
  cin >> ch;
  if (ch == '#') {
    T = NULL;
  } else {
    T = new BiNode;
    T->data = ch;
    CreatrebiTree(T->lchild);
    CreatrebiTree(T->rchild);
  }
}

void BiTreeDepth(const BiTree &T, int h, int &depth) {
  if (T) {
    if (h > depth) {
      depth = h;
    }
    BiTreeDepth(T->lchild, h + 1, depth);
    BiTreeDepth(T->rchild, h + 1, depth);
  }
}

int BiTreeDepth(const BiTree &T) {
  if (T) {
    int hL = BiTreeDepth(T->lchild);
    int hR = BiTreeDepth(T->rchild);
    if (hL >= hR) {
      return hL + 1;
    } else {
      return hR + 1;
    }
  } else {
    return 0;
  }
}
