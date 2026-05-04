#ifndef QUEUE_H_
#define QUEUE_H_

typedef int QElemType;

typedef struct LNode {
  QElemType data;
  struct LNode *next;
} LNode, *LinkedList;

typedef LinkedList QueuePtr;

typedef struct {
  QueuePtr front;
  QueuePtr rear;
} LinkQueue;

void InitQueue_L(LinkQueue &Q);
void DestroyQueue_L(LinkQueue &Q);
void ClearQueue_L(LinkQueue &Q);
bool QueQueueEmpty_L(LinkQueue Q);
int QueueLength_L(LinkQueue Q);
bool GetHead(LinkQueue Q, QElemType &e);
void Enqueue_L(LinkQueue &Q, QElemType e);
bool Dequeue_L(LinkQueue &Q, QElemType &e);
void QueueTraverse(LinkQueue Q);

#endif // !QUEUE_H_
