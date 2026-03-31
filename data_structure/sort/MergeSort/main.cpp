#include <iostream>
#include "sqlist.h"
#include "MergeSort.cpp"

using namespace std;

void ListTraverse_Sq(SqList L) {
  for (int i = 0; i < L.length; i++)
    cout << L.r[i].key << " ";
  cout << endl;
}

int main() {
  SqList L;
  L.length = 7;
  L.r[0].key = 49;
  L.r[1].key = 38;
  L.r[2].key = 65;
  L.r[3].key = 97;
  L.r[4].key = 76;
  L.r[5].key = 13;
  L.r[6].key = 27;

  cout << "Before: ";
  ListTraverse_Sq(L);

  Mergesort(L, 0, L.length - 1);

  cout << "After: ";
  ListTraverse_Sq(L);

  return 0;
}
