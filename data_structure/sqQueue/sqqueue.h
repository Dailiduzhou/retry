#ifndef SQQUEUE_H_
#define SQQUEUE_H_

const int QUEUE_INIT_SIZE = 100;
const int QUEUEINCREMENT = 20;

typedef int QElemType;

typedef struct {
  QElemType *elem;
  int front;
  int rear;
  int queuesize;
  int incrementsize;
} SqQueue;

void InitQueue_Sq(SqQueue &Q, int maxsize, int incresize);
void DestroyQueue_Sq(SqQueue &Q);
void ClearQueue_Sq(SqQueue &Q);
bool QueueEmpty_Sq(SqQueue Q);
int QueueLength_Sq(SqQueue Q);
void GetHead_Sq(SqQueue Q, QElemType &e);
void Enqueue_Sq(SqQueue &Q, QElemType e);
bool Dequeue_Sq(SqQueue &Q, QElemType &e);
void QueueTraverse_Sq(SqQueue Q);
void incrementQueuesize(SqQueue &Q);

#endif // !SQQUEUE_H_
