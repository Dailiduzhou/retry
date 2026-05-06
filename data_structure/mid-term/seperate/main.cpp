#include "linkedlist.h"

void Seperate(LinkedList A, LinkedList B, LinkedList C) {
  LNode *p = A->next;
  LNode *b = B;
  LNode *c = C;

  while (p != A) {
    LNode *next = p->next;
    if (p->data % 2 == 1) {
      b->next = p;
      b = b->next;
    } else {
      c->next = p;
      c = c->next;
    }
    p = next;
  }

  b->next = B;
  c->next = C;
  A->next = A;
}
