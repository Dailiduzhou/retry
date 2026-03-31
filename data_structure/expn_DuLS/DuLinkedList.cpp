#include "head.h"
using namespace std;

void ListInsert_DuL(DuLinkedList &L, DuLNode *p, DuLNode *s) {
  s->prior = p->prior;
  p->prior->next = s;
  s->next = p;
  p->prior = s;
}

void ListDelete_DuL(DuLinkedList &L, DuLNode *p, ElemType &e) {
  e = p->data;

  p->prior->next = p->next;
  p->next->prior = p->prior;
  delete p;
}
