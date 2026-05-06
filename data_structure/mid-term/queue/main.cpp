#include "queue.h"
void Inqueue(LNode *rear, int x) {
  LNode *p = new LNode;
  p->data = x;
  p->next = rear->next;
  rear->next = p;
  rear = p;
}

void Delqueue(LNode *rear, int &x) {
  if (rear == rear->next) {
    return;
  }
  LNode *head = rear->next;
  LNode *first = head->next;
  x = first->data;

  head->next = first->next;
  if (rear == first) {
    rear = head;
  }
  delete first;
}
