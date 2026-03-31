#include <iostream>
#include "sqlist.h"
#include "InsertSort.cpp"

using namespace std;

void ListTraverse_Sq(SqList L) {
  for (int i = 1; i <= L.length; i++)
    cout << L.r[i].key << " ";
  cout << endl;
}

int main() {
  SqList L;
  L.length = 7;
  L.r[1].key = 49;
  L.r[2].key = 38;
  L.r[3].key = 65;
  L.r[4].key = 97;
  L.r[5].key = 76;
  L.r[6].key = 13;
  L.r[7].key = 27;

  cout << "Before: ";
  ListTraverse_Sq(L);

  InsertSort(L);

  cout << "After: ";
  ListTraverse_Sq(L);

  return 0;
}
