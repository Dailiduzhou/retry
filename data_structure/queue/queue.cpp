#include "queue.h"
#include <cstddef>
#include <iostream>

void InitQueue_L(LinkQueue &Q) {
  Q.front = new LNode;
  Q.rear = Q.front;

  Q.front->next = NULL;
}

void DestroyQueue_L(LinkQueue &Q) {
  while (Q.front) {
    Q.rear = Q.front->next;
    delete Q.front;
    Q.front = Q.rear;
  }
}

void Enqueue_L(LinkQueue &Q, QElemType e) {
  LNode *p = new LNode;
  p->data = e;
  p->next = NULL;

  Q.rear->next = p;
  Q.rear = p;
}

bool Dequeue_L(LinkQueue &Q, QElemType &e) {
  if (Q.front == Q.rear) {
    return false;
  }

  LNode *p = Q.front->next;
  e = p->data;
  Q.front->next = p->next;

  if (Q.rear == p) {
    Q.rear = Q.front;
  }

  delete p;
  return true;
}

void ClearQueue_L(LinkQueue &Q) {
  while (Q.front->next) {
    LNode *p = Q.front->next;
    Q.front->next = p->next;
    delete p;
  }
  Q.rear = Q.front;
}

bool QueQueueEmpty_L(LinkQueue Q) { return Q.front == Q.rear; }

int QueueLength_L(LinkQueue Q) {
  int length = 0;
  LNode *p = Q.front->next;
  while (p) {
    length++;
    p = p->next;
  }
  return length;
}

void GetHead(LinkQueue Q, QElemType &e) {
  if (Q.front != Q.rear) {
    e = Q.front->next->data;
  }
}

void QueueTraverse(LinkQueue Q) {
  LNode *p = Q.front->next;
  while (p) {
    std::cout << p->data << " ";
    p = p->next;
  }
  std::cout << std::endl;
}
