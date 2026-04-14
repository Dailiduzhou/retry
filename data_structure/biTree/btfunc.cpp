#include "bitree.h"

void Preorder(BiTree T, void (*visit)(BiTree)) {
  if (T) {
    visit(T);
    Preorder(T->lchild, visit);
    Preorder(T->rchild, visit);
  }
}
