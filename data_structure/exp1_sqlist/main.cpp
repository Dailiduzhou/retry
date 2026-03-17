#include "sqlist.h"
#include <iostream>
using namespace std;

int main() {
  SqList L;
  ElemType e;

  InitList_Sq(L);

  ListInsert_Sq(L, 1, 10);
  ListInsert_Sq(L, 2, 20);
  ListInsert_Sq(L, 3, 30);
  ListInsert_Sq(L, 4, 40);
  ListInsert_Sq(L, 5, 50);
  ListTraverse_Sq(L);

  GetElem_Sq(L, 3, e);
  cout << e << endl;

  cout << LocateElem_Sq(L, 30) << endl;

  PriorElem_Sq(L, 30, e);
  cout << e << endl;

  NextElem_Sq(L, 30, e);
  cout << e << endl;

  ListDelete_Sq(L, 2, e);
  ListTraverse_Sq(L);

  ListInsert_Sq(L, 2, 25);
  ListTraverse_Sq(L);

  cout << ListLength_Sq(L) << endl;
  cout << ListEmpty_Sq(L) << endl;

  ClearList_Sq(L);
  cout << ListEmpty_Sq(L) << endl;
  ListTraverse_Sq(L);

  DestoryList_Sq(L);
  return 0;
}
