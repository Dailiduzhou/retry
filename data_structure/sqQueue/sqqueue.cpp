#include "sqqueue.h"
#include <iostream>

using namespace std;

void InitQueue_Sq(SqQueue &Q, int maxsize = QUEUE_INIT_SIZE,
                  int incresize = QUEUEINCREMENT) {
  Q.elem = new QElemType[maxsize];
  Q.queuesize = maxsize;
  Q.incrementsize = incresize;
  Q.front = Q.rear = 0;
}

int QueueLength_Sq(SqQueue Q) {
  return (Q.rear - Q.front + Q.queuesize) % Q.queuesize;
}

bool Dequeue_Sq(SqQueue &Q, QElemType &e) {
  if (Q.front == Q.rear) {
    return false;
  }

  e = Q.elem[Q.front];
  Q.front = (Q.front + 1) % Q.queuesize;
  return true;
}

void Enqueue_Sq(SqQueue &Q, QElemType e) {
  if ((Q.rear + 1) % Q.queuesize == Q.front) {
    incrementQueuesize(Q);
  }

  Q.elem[Q.rear] = e;
  Q.rear = (Q.rear + 1) % Q.queuesize;
}

void incrementQueuesize(SqQueue &Q) {
  QElemType *a = new QElemType[Q.queuesize + Q.incrementsize];

  for (int k = 0; k < Q.queuesize; ++k) {
    a[k] = Q.elem[(Q.front + k) % Q.queuesize];
  }

  delete[] Q.elem;
  Q.elem = a;
  Q.front = 0;
  Q.rear = Q.queuesize - 1;
  Q.queuesize += Q.incrementsize;
}

void DestroyQueue_Sq(SqQueue &Q) {
  delete[] Q.elem;
  Q.elem = NULL;
  Q.front = Q.rear = 0;
  Q.queuesize = 0;
  Q.incrementsize = 0;
}

void ClearQueue_Sq(SqQueue &Q) {
  Q.front = Q.rear = 0;
}

bool QueueEmpty_Sq(SqQueue Q) {
  return Q.front == Q.rear;
}

void GetHead_Sq(SqQueue Q, QElemType &e) {
  if (Q.front != Q.rear) {
    e = Q.elem[Q.front];
  }
}

void QueueTraverse_Sq(SqQueue Q) {
  int i = Q.front;
  while (i != Q.rear) {
    cout << Q.elem[i] << " ";
    i = (i + 1) % Q.queuesize;
  }
  cout << endl;
}
