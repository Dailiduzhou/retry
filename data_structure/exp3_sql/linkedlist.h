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
void ListDelete_L(LinkedList &L, LNode *p, ElemType &e);
LNode *LocateElem_L(LinkedList L, ElemType e);
void ListInsert_L(LinkedList &L, LNode *p, LNode *s);
LinkedList ListInvert_L(LinkedList &L);
void Union_L(LinkedList &La, LinkedList &Lb);

#endif // !LINKEDLIST
