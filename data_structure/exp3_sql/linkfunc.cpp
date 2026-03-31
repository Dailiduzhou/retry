#include "linkedlist.h"

LNode *getIntersectionNode(LinkedList headA, LinkedList headB) {
  LNode *lista = headA;
  LNode *listb = headB;

  while (lista != listb) {
    lista = (lista != nullptr) ? lista->next : headB;
    listb = (listb != nullptr) ? listb->next : headA;
  }

  return lista;
}

LinkedList MergeAsc(LinkedList La, LinkedList Lb) {
  LNode *tail = La;
  LNode *p = La->next;
  LNode *q = Lb->next;

  while (p && q) {
    if (p->data < q->data) {
      tail->next = p;
      tail = p;
      p = p->next;
    } else if (p->data > q->data) {
      tail->next = q;
      tail = q;
      q = q->next;
    } else {
      tail->next = p;
      tail = p;
      p = p->next;
      LNode *tmp = q;
      q = q->next;
      delete tmp;
    }
  }

  tail->next = p ? p : q;
  delete Lb;
  return La;
}
