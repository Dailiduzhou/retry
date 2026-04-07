#include "queque.h"
#include <cstddef>
#include <iostream>

void InitQueue_L(LinkQueue &Q) {
  Q.front = new LNode;
  Q.rear = new LNode;

  Q.front->next = NULL;
}

void DestroyQueue_L(LinkQueue &Q) {
  while (Q.front) {
    Q.rear = Q.front->next;
    delete Q.front;
    Q.front = Q.rear;
  }
}
