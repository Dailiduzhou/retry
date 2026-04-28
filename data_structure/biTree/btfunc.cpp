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

void InitBiTree(BiTree &T) { T = NULL; }

void DestroyBiTree(BiTree &T) {
  if (T) {
    DestroyBiTree(T->lchild);
    DestroyBiTree(T->rchild);
    delete T;
    T = NULL;
  }
}

bool BiTreeEmpty(const BiTree &T) { return T == NULL; }

BiNode *Parent(BiTree T, BiNode *e) {
  if (!T || !e || T == e) {
    return NULL;
  }

  if (T->lchild == e || T->rchild == e) {
    return T;
  }

  BiNode *p = Parent(T->lchild, e);
  if (p) {
    return p;
  }
  return Parent(T->rchild, e);
}

BiNode *LeftChild(BiTree T, BiNode *e) {
  if (!T || !e) {
    return NULL;
  }
  return e->lchild;
}

BiNode *RightChild(BiTree T, BiNode *e) {
  if (!T || !e) {
    return NULL;
  }
  return e->rchild;
}

BiNode *LeftSibling(BiTree T, BiNode *e) {
  if (!T || !e || T == e) {
    return NULL;
  }

  BiNode *p = Parent(T, e);
  if (p && p->rchild == e) {
    return p->lchild;
  }
  return NULL;
}

BiNode *RightSibling(BiTree T, BiNode *e) {
  if (!T || !e || T == e) {
    return NULL;
  }

  BiNode *p = Parent(T, e);
  if (p && p->lchild == e) {
    return p->rchild;
  }
  return NULL;
}

bool InsertChild(BiTree &T, BiNode *p, int LR, BiNode *child) {
  if (!T || !p || !child) {
    return false;
  }

  BiNode *temp;
  if (LR == 0) {
    temp = p->lchild;
    p->lchild = child;
  } else {
    temp = p->rchild;
    p->rchild = child;
  }

  if (LR == 0) {
    child->rchild = temp;
  } else {
    child->lchild = temp;
  }

  return true;
}

bool DeleteChild(BiTree &T, BiNode *p, int LR) {
  if (!T || !p) {
    return false;
  }

  if (LR == 0) {
    DestroyBiTree(p->lchild);
  } else {
    DestroyBiTree(p->rchild);
  }

  return true;
}

void InorderTraverse(BiTree T, void (*visit)(BiTree)) {
  if (T) {
    InorderTraverse(T->lchild, visit);
    visit(T);
    InorderTraverse(T->rchild, visit);
  }
}

static void PrintNode(BiTree T) {
  if (T) {
    cout << T->data << " ";
  }
}

void Traverse(const BiTree &T) {
  if (!T) {
    cout << "Empty tree" << endl;
    return;
  }
  cout << "Inorder traversal: ";
  InorderTraverse(T, PrintNode);
  cout << endl;
}
