#ifndef LINKEDLIST
#define LINKEDLIST

typedef int ElemType;

typedef struct LNode {
  ElemType data;
  struct LNode *next;
} LNode, *LinkedList;

void InitList(LinkedList &L);
void DestoryList(LinkedList &L);
void ClearList(LinkedList &L);

bool ListEmpty(LinkedList L);
int ListLength(LinkedList L);
bool GetElem(LinkedList L, int i, LNode &e);
int LocateElem(LinkedList L, ElemType e);
void PriorElem(LinkedList L, LNode cur_e, LNode &pre_e);
void NextElem(LinkedList L, LNode cur_e, LNode &next);
void ListInsert(LinkedList &L, int i, LNode e);
void ListDelete(LinkedList &L, int i, LNode &e);
void ListTraverse(LinkedList L);

#endif // !LINKEDLIST
