#include "linkstack.h"
#include <cstddef>

void InitStack_L(LinkStack &S) { S = NULL; }

void Push_L(LinkStack &S, ElemType e) {
  LNode *p = new LNode;
  p->data = e;
  p->next = S;
  S = p;
}

bool Pop_L(LinkStack &S, ElemType &e) {
  if (S) {
    LNode *p = S;
    S = S->next;
    e = p->data;
    delete p;
    return true;
  }
  return false;
}
