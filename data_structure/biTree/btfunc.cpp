#include "bitree.h"
#include <cstddef>
#include <iostream>
using namespace std;

const TElemType PLUS = -1;
const TElemType MINUS = -2;
const TElemType ASTERISK = -3;
const TElemType SLANT = -4;

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

BiNode *GetTreeNode(TElemType item, BiNode *lptr, BiNode *rptr) {
  BiNode *T = new BiNode;
  T->data = item;
  T->lchild = lptr;
  T->rchild = rptr;
  return T;
}

BiNode *CopyTree(BiNode *T) {
  if (!T) {
    return NULL;
  }
  BiNode *newlptr = NULL;
  BiNode *newrptr = NULL;
  if (T->lchild) {
    newlptr = CopyTree(T->lchild);
  }

  if (T->rchild) {
    newrptr = CopyTree(T->rchild);
  }

  BiNode *newnode = GetTreeNode(T->data, newlptr, newrptr);
  return newnode;
}

double value(BiTree T, float opnd[]) {
  if (!T) {
    return 0;
  }

  if (T->data >= 0) {
    return opnd[T->data];
  }

  TElemType Lv = value(T->lchild, opnd);
  TElemType Rv = value(T->rchild, opnd);

  double v = 0;
  switch (T->data) {
  case PLUS:
    v = Lv + Rv;
    break;
  case MINUS:
    v = Lv - Rv;
    break;
  case ASTERISK:
    v = Lv * Rv;
    break;
  case SLANT:
    v = (Lv * 1.0) / Rv;
    break;
  }

  return v;
}
