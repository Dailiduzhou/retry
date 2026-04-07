#include "dulinkedlist.h"
#include <iostream>
#include <cstring>

using namespace std;

void InitList(DuLinkList &L) {
  L = new DuLNode;
  if (L == NULL) {
    cerr << "Memory allocation failed" << endl;
  }
  L->prior = L;
  L->next = L;
  L->i = 0;
  return;
}

void ClearList(DuLinkList &L) {
  DuLNode *p = L->next;
  while (p != L) {
    DuLNode *q = p->next;
    delete p;
    p = q;
  }
  L->prior = L;
  L->next = L;
  L->i = 0;
}

void DestroyList(DuLinkList &L) {
  DuLNode *p = L->next;
  while (p != L) {
    DuLNode *q = p->next;
    delete p;
    p = q;
  }
  delete L;
  L = nullptr;
}

void InsertAfter(DuLinkList &L, DuLNode *p, STUDENT stu) {
  DuLNode *s = new DuLNode;
  strcpy(s->stu.no, stu.no);
  strcpy(s->stu.name, stu.name);
  s->stu.score = stu.score;
  s->stu.time = stu.time;

  s->next = p->next;
  s->prior = p;
  p->next->prior = s;
  p->next = s;
  L->i++;
}

void ReadStuMsg(DuLinkList &L, const char *filename) {
  ifstream infile(filename);
  if (!infile) {
    cerr << "File could not be opened!" << endl;
    return;
  }
  STUDENT stu;
  while (infile >> stu.no >> stu.name >> stu.score >> stu.time) {
    InsertAfter(L, L->prior, stu);
  }
  infile.close();
}

DuLNode *Partition(DuLNode *low, DuLNode *high) {
  STUDENT pivot = low->stu;
  while (low != high) {
    while (low != high &&
           (high->stu.score < pivot.score ||
            (high->stu.score == pivot.score && high->stu.time > pivot.time))) {
      high = high->prior;
    }
    strcpy(low->stu.no, high->stu.no);
    strcpy(low->stu.name, high->stu.name);
    low->stu.score = high->stu.score;
    low->stu.time = high->stu.time;
    while (low != high &&
           (low->stu.score > pivot.score ||
            (low->stu.score == pivot.score && low->stu.time < pivot.time))) {
      low = low->next;
    }
    strcpy(high->stu.no, low->stu.no);
    strcpy(high->stu.name, low->stu.name);
    high->stu.score = low->stu.score;
    high->stu.time = low->stu.time;
  }
  strcpy(low->stu.no, pivot.no);
  strcpy(low->stu.name, pivot.name);
  low->stu.score = pivot.score;
  low->stu.time = pivot.time;
  return low;
}

void QSort(DuLNode *low, DuLNode *high) {
  if (low != high && low->prior != high) {
    DuLNode *pivot = Partition(low, high);
    QSort(low, pivot->prior);
    QSort(pivot->next, high);
  }
}

void ShowStuMsg(DuLinkList L) {
  DuLNode *p = L->next;
  while (p != L) {
    cout << p->stu.no << " " << p->stu.name << " " << p->stu.score << " "
         << p->stu.time << endl;
    p = p->next;
  }
}
