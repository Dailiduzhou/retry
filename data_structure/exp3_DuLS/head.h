#ifndef DULINKEDLIST_H
#define DULINKEDLIST_H

typedef int ElemType;

typedef struct DuLNode {
  ElemType data;
  struct DuLNode *prior;
  struct DuLNode *next;
} DuLNode, *DuLinkedList;

void ListInsert_DuL(DuLinkedList &L, DuLNode *p, DuLNode *s);
void ListDelete_DuL(DuLinkedList &L, DuLNode *p, ElemType &e);

#endif // DULINKEDLIST_H
