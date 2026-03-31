#ifndef LINKSTACK
#define LINKSTACK

typedef int ElemType;

typedef struct LNode {
  ElemType data;
  struct LNode *next;
} LNode, *LinkedList;

typedef LinkedList LinkStack;

void InitStack_L(LinkStack &S);
void DestoryStack_L(LinkStack &S);
void ClearStack_L(LinkStack &S);

void Push_L(LinkStack &S, ElemType e);
bool Pop_L(LinkStack &S, ElemType &e);

#endif // !LINKEDLIST
