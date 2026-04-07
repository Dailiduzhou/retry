#ifndef QUEQUE_H_
#define QUEQUE_H_

typedef int ElemType;

typedef struct LNode {
  ElemType data;
  struct LNode *next;
} LNode, *LinkedList;

typedef LinkedList QuequePtr;

typedef struct {
  QuequePtr front;
  QuequePtr rear;
} LinkQueue;

void InitQueue_L(LinkQueue &Q);
void DestroyQueue_L(LinkQueue &Q);
void ClearQueue_L(LinkQueue &Q);
bool QueQueueEmpty_L(LinkQueue Q);
int QueueLength_L(LinkQueue Q);
void GetHead(LinkQueue Q, ElemType &e);
void Enqueue_L(LinkQueue &Q, ElemType e);
void Dequeue_L(LinkQueue &Q, ElemType &e);
void QueueTraverse(LinkQueue Q);

#endif // !QUEQUE_H_
