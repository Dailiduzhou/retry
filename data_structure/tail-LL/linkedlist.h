#ifndef LINKEDLIST
#define LINKEDLIST

typedef int ElemType;

typedef struct LNode {
  ElemType data;
  struct LNode *next;
} LNode;

typedef struct LinkList {
  struct LNode *tail;
} LinkList;

void InitList(LinkList &L);
void InsertList(LinkList &L, ElemType val);
void ListDelete(LinkList &L, ElemType val);
int ListLength(LinkList &L);
void ListTraverse(LinkList &L);
#endif // !LINKEDLIST
