#include "dulinkedlist.h"
#include <iostream>
#include <cstring>

using namespace std;

void testBasicOperations() {
  DuLinkList L;
  InitList(L);

  cout << "Test InitList: ";
  cout << "List initialized, node count: " << L->i << endl;

  STUDENT s1, s2, s3;
  strcpy(s1.no, "001");
  strcpy(s1.name, "Alice");
  s1.score = 90;
  s1.time = 10;

  strcpy(s2.no, "002");
  strcpy(s2.name, "Bob");
  s2.score = 85;
  s2.time = 15;

  strcpy(s3.no, "003");
  strcpy(s3.name, "Charlie");
  s3.score = 95;
  s3.time = 8;

  InsertAfter(L, L->prior, s1);
  InsertAfter(L, L->prior, s2);
  InsertAfter(L, L->prior, s3);

  cout << "After inserting 3 students:" << endl;
  ShowStuMsg(L);
  cout << "Node count: " << L->i << endl;
  cout << endl;

  ClearList(L);
  cout << "After ClearList: ";
  cout << "Node count: " << L->i << endl;
  cout << endl;

  DestroyList(L);
  cout << "After DestroyList: List destroyed" << endl;
  cout << endl;
}

void testSorting() {
  DuLinkList L;
  InitList(L);

  STUDENT s1, s2, s3, s4, s5;
  
  strcpy(s1.no, "001");
  strcpy(s1.name, "Alice");
  s1.score = 90;
  s1.time = 10;

  strcpy(s2.no, "002");
  strcpy(s2.name, "Bob");
  s2.score = 85;
  s2.time = 15;

  strcpy(s3.no, "003");
  strcpy(s3.name, "Charlie");
  s3.score = 95;
  s3.time = 8;

  strcpy(s4.no, "004");
  strcpy(s4.name, "David");
  s4.score = 90;
  s4.time = 12;

  strcpy(s5.no, "005");
  strcpy(s5.name, "Eve");
  s5.score = 85;
  s5.time = 20;

  InsertAfter(L, L->prior, s1);
  InsertAfter(L, L->prior, s2);
  InsertAfter(L, L->prior, s3);
  InsertAfter(L, L->prior, s4);
  InsertAfter(L, L->prior, s5);

  cout << "Test Sorting - Before:" << endl;
  ShowStuMsg(L);

  if (L->next != L) {
    QSort(L->next, L->prior);
  }

  cout << "After Sorting (by score desc, time asc):" << endl;
  ShowStuMsg(L);
  cout << endl;

  DestroyList(L);
}

void testFileOperation() {
  DuLinkList L;
  InitList(L);

  cout << "Test File Operation:" << endl;
  ReadStuMsg(L, "stumsg.txt");
  
  cout << "Before sorting:" << endl;
  ShowStuMsg(L);

  if (L->next != L) {
    QSort(L->next, L->prior);
  }

  cout << "After sorting:" << endl;
  ShowStuMsg(L);
  cout << endl;

  DestroyList(L);
}

int main() {
  testBasicOperations();
  testSorting();
  testFileOperation();

  return 0;
}
