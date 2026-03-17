#ifndef SQLIST
#define SQLIST

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef int ElemType;
typedef struct {
  ElemType *elem;
  int length;
  int listsize;
  int incrementsize;
} SqList;

void InitList_Sq(SqList &L);
void DestoryList_Sq(SqList &L);
void ClearList_Sq(SqList &L);
bool ListEmpty_Sq(SqList L);
int ListLength_Sq(SqList L);
bool GetElem_Sq(SqList L, int i, ElemType &e);
int LocateElem_Sq(SqList L, ElemType e);
bool PriorElem_Sq(SqList L, ElemType cur_e, ElemType &pre_e);
bool NextElem_Sq(SqList L, ElemType cur_e, ElemType &next_e);
void ListInsert_Sq(SqList &L, int i, ElemType e);
void ListDelete_Sq(SqList &L, int i, ElemType &e);
void ListTraverse_Sq(SqList L);

#endif
