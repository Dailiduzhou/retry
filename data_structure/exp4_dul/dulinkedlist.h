#ifndef DULINKEDLIST_H
#define DULINKEDLIST_H

#include <fstream>
#include <string>

using namespace std;

typedef struct Student {
  char no[9];
  char name[11];
  int score;
  int time;
} STUDENT;

typedef struct DuLNode {
  STUDENT stu;
  int i;
  struct DuLNode *prior;
  struct DuLNode *next;
} DuLNode, *DuLinkList;

void InitList(DuLinkList &L);
void ClearList(DuLinkList &L);
void DestroyList(DuLinkList &L);
void InsertAfter(DuLinkList &L, DuLNode *p, STUDENT stu);
void ReadStuMsg(DuLinkList &L, const char *filename);
DuLNode *Partition(DuLNode *low, DuLNode *high);
void QSort(DuLNode *low, DuLNode *high);
void ShowStuMsg(DuLinkList L);

#endif // DULINKEDLIST_H
