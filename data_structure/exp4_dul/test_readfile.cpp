#include "dulinkedlist.h"
#include <iostream>

using namespace std;

void testReadFromFile() {
  DuLinkList L;
  InitList(L);

  cout << "Reading student data from file..." << endl;

  ReadStuMsg(L, "stumsg.txt");

  cout << "Total students: " << L->i << endl;
  cout << endl;

  cout << "Student List (Original Order):" << endl;
  cout << "ID\tName\tScore\tTime" << endl << endl;
  ShowStuMsg(L);
  cout << endl;

  DestroyList(L);
}

void testReadAndSort() {
  DuLinkList L;
  InitList(L);

  cout << "Reading student data from file..." << endl;
  ReadStuMsg(L, "stumsg.txt");

  cout << "Before Sorting:" << endl;
  cout << "========================================" << endl;
  cout << "ID\tName\tScore\tTime" << endl;
  cout << "----------------------------------------" << endl;
  ShowStuMsg(L);
  cout << endl;

  if (L->next != L) {
    QSort(L->next, L->prior);
  }

  cout << "After Sorting (by score desc, time asc):" << endl;
  cout << "========================================" << endl;
  cout << "ID\tName\tScore\tTime" << endl;
  cout << "----------------------------------------" << endl;
  ShowStuMsg(L);
  cout << "========================================" << endl;
  cout << endl;

  DestroyList(L);
}

int main() {
  testReadFromFile();
  testReadAndSort();

  return 0;
}
