#include "linkedlist.h"
#include <iostream>
using namespace std;

void testListInvert_L();

int main() {
  LinkedList L;
  LNode e;

  InitList(L);

  e.data = 10; ListInsert(L, 1, e);
  e.data = 20; ListInsert(L, 2, e);
  e.data = 30; ListInsert(L, 3, e);
  e.data = 40; ListInsert(L, 4, e);
  e.data = 50; ListInsert(L, 5, e);

  ListTraverse(L);

  GetElem(L, 3, e);
  cout << e.data << endl;

  cout << LocateElem(L, 30) << endl;

  e.data = 30;
  LNode pre, next;
  PriorElem(L, e, pre);
  NextElem(L, e, next);
  cout << pre.data << " " << next.data << endl;

  ListDelete(L, 3, e);
  ListTraverse(L);

  e.data = 25;
  ListInsert(L, 2, e);
  ListTraverse(L);

  ClearList(L);
  ListTraverse(L);

  DestoryList(L);

  cout << endl << "Test ListInvert_L:" << endl;
  testListInvert_L();

  return 0;
}

void testListInvert_L() {
  LinkedList L;
  LNode e;

  InitList(L);

  e.data = 1; ListInsert(L, 1, e);
  e.data = 2; ListInsert(L, 2, e);
  e.data = 3; ListInsert(L, 3, e);
  e.data = 4; ListInsert(L, 4, e);
  e.data = 5; ListInsert(L, 5, e);

  cout << "Before invert:" << endl;
  ListTraverse(L);

  ListInvert_L(L);

  cout << "After invert:" << endl;
  ListTraverse(L);

  DestoryList(L);
}
