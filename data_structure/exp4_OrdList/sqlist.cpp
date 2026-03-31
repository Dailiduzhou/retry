#include "sqlist.h"
#include <iostream>
using namespace std;

void InitList_Sq(SqList &L) {
  L.elem = new ElemType[LIST_INIT_SIZE];
  L.length = 0;
  L.listsize = LIST_INIT_SIZE;
  L.incrementsize = LISTINCREMENT;
}

void DestoryList_Sq(SqList &L) {
  delete[] L.elem;
  L.elem = nullptr;
  L.length = 0;
  L.listsize = 0;
}

void ClearList_Sq(SqList &L) { L.length = 0; }

bool ListEmpty_Sq(SqList L) { return L.length == 0; }

int ListLength_Sq(SqList L) { return L.length; }

bool GetElem_Sq(SqList L, int i, ElemType &e) {
  if (i < 1 || i > L.length)
    return false;
  e = L.elem[i - 1];
  return true;
}

int LocateElem_Sq(SqList L, ElemType e) {
  for (int i = 0; i < L.length; i++) {
    if (L.elem[i] == e)
      return i + 1;
  }
  return 0;
}

bool PriorElem_Sq(SqList L, ElemType cur_e, ElemType &pre_e) {
  int pos = LocateElem_Sq(L, cur_e);
  if (pos <= 1)
    return false;
  pre_e = L.elem[pos - 2];
  return true;
}

bool NextElem_Sq(SqList L, ElemType cur_e, ElemType &next_e) {
  int pos = LocateElem_Sq(L, cur_e);
  if (pos == 0 || pos >= L.length)
    return false;
  next_e = L.elem[pos];
  return true;
}

void increment(SqList &L) {
  ElemType *a = new ElemType[L.listsize + L.incrementsize];
  for (int i = 0; i < L.length; i++)
    a[i] = L.elem[i];
  delete[] L.elem;
  L.elem = a;
  L.listsize += L.incrementsize;
}

void ListInsert_Sq(SqList &L, int i, ElemType e) {
  if (i < 1 || i > L.length + 1)
    return;
  if (L.length >= L.listsize)
    increment(L);
  for (int j = L.length; j >= i; j--)
    L.elem[j] = L.elem[j - 1];
  L.elem[i - 1] = e;
  L.length++;
}

void ListDelete_Sq(SqList &L, int i, ElemType &e) {
  if (i < 1 || i > L.length)
    return;
  e = L.elem[i - 1];
  for (int j = i; j < L.length; j++)
    L.elem[j - 1] = L.elem[j];
  L.length--;
}

void ListTraverse_Sq(SqList L) {
  for (int i = 0; i < L.length; i++)
    cout << L.elem[i] << " ";
  cout << endl;
}

// Ord List
void OrdInsert(SqList &L, ElemType x) {
  int i = L.length - 1;
  if (L.length + 1 == L.listsize) {
    increment(L);
  }

  while (i >= 0 && x < L.elem[i]) {
    L.elem[i + 1] = L.elem[i];
    --i;
  }

  L.elem[i + 1] = x;
  L.length++;
}

void Pruge_Osq(SqList &L) {
  int prev = -1;
  int cur = 0;
  while (cur < L.length) {
    if (cur == 0 || L.elem[prev] != L.elem[cur]) {
      L.elem[++prev] = L.elem[cur];
    }
    ++cur;
  }
  L.length = prev + 1;
}
