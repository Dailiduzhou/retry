#include "linkedlist.h"
#include <iostream>
using namespace std;
void ErrorMessage(const char *s) {
  cout << s << endl;
  exit(1);
}
void InitList(LinkedList &L) {
  L = new LNode;
  L->data = 0;
  L->next = nullptr;
}
void DestoryList(LinkedList &L) {
  LNode *p;
  while (L) {
    p = L->next;
    delete L;
    L = p;
  }
}
void ClearList(LinkedList &L) {
  LNode *p;
  while (L->next) {
    p = L->next;
    L->next = p->next;
    delete p;
  }
}

bool ListEmpty(LinkedList L) {
  if (!L->next)
    return true;
  else
    return false;
}

int ListLength(LinkedList L) {
  LNode *p = L->next;
  int n = 0;
  while (p) {
    p = p->next;
    ++n;
  }
  return n;
}
bool GetElem(LinkedList L, int i, LNode &e) {
  int cnt = 1;
  LNode *p = L->next;
  if (i < 1) {
    return false;
  }
  while (cnt < i && p) {
    p = p->next;
    ++cnt;
  }
  if (cnt == i && p) {
    e.data = p->data;
    return true;
  } else {
    return false;
  }
}

int LocateElem(LinkedList L, ElemType e) {
  int n = 1;
  LNode *p = L->next;
  while (p && p->data != e) {
    p = p->next;
    ++n;
  }
  if (!p) {
    return -1;
  }
  if (p->data == e) {
    return n;
  }
  return -1;
}

void PriorElem(LinkedList L, LNode cur_e, LNode &pre_e) {
  LNode *p = L->next;
  if (!p)
    return;
  while (p->next && p->next->data != cur_e.data) {
    p = p->next;
  }
  if (!p->next) {
    return;
  }
  if (p->next->data == cur_e.data) {
    pre_e = *p;
  }
}
void NextElem(LinkedList L, LNode cur_e, LNode &next) {
  LNode *p = L->next;
  if (!p) {
    return;
  }
  while (p && p->data != cur_e.data) {
    p = p->next;
  }

  if (!p) {
    return;
  }
  if (p->next && p->data == cur_e.data) {
    next = *p->next;
  }
}

void ListInsert(LinkedList &L, int i, LNode e) {
  LNode *p = L;
  int n = 0;
  while (p && n < i - 1) {
    p = p->next;
    ++n;
  }
  if (!p || n > i - 1)
    return;
  LNode *newNode = new LNode;
  newNode->data = e.data;
  newNode->next = p->next;
  p->next = newNode;
}

void ListDelete(LinkedList &L, int i, LNode &e) {
  LNode *p = L;
  int n = 0;
  while (p->next && n < i - 1) {
    p = p->next;
    ++n;
  }
  if (!p->next || n > i - 1)
    return;
  LNode *q = p->next;
  e.data = q->data;
  p->next = q->next;
  delete q;
}
void ListTraverse(LinkedList L) {
  LNode *p = L->next;
  while (p) {
    cout << p->data << " ";
    p = p->next;
  }
  cout << endl;
}
