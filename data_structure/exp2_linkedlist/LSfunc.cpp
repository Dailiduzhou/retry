#include "linkedlist.cpp"
#include "linkedlist.h"

#ifndef LSFunc
#define LSFunc

// 两个链表简单相加
void SetUnion(LinkedList &A, LinkedList B) {
  LNode *p;
  LNode *s;
  p = A;
  s = B;
  while (p->next != NULL) {
    p = p->next;
  }
  while (s->next != NULL) {
    s = s->next;
    LNode *q;
    q = new LNode;
    q->next = NULL;
    q->data = s->data;
    p->next = q;
    p = p->next;
  }
  return;
}

// 集合去重
void SetPrue(LinkedList &A) {
  if (A == NULL || A->next == NULL) {
    return;
  }

  LNode *p = A->next;
  while (p) {
    LNode *q = p;
    while (q->next) {
      if (q->next->data == p->data) {
        LNode *temp = q->next;
        q->next = q->next->next;
        delete q;
      } else {
        q = q->next;
      }
    }
    p = p->next;
  }
  return;
}

#endif // !LSFUNC
