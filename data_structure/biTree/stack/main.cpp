#include "sbitree.h"

void InOrder_iter(BiTree BT, void (*visit)(BiTree)) {
  SqStack S;
  InitStack_Sq(S);

  SElemType e;
  e.ptr = BT;
  e.task = TaskType::Travel;

  if (BT) {
    Push_Sq(S, e);
  }

  while (!StackEmpty(S)) {
    Pop_Sq(S, e);
    if (e.task == TaskType::Visit) {
      visit(e.ptr);
    } else {
      if (e.ptr) {
        BiNode *p = e.ptr;
        e.ptr = p->rchild;
        Push_Sq(S, e);
        e.ptr = p;
        e.task = TaskType::Visit;
        Push_Sq(S, e);
        e.ptr = p->lchild;
        e.task = TaskType::Travel;
        Push_Sq(S, e);
      }
    }
  }
}
