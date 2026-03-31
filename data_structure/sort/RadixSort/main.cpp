#include <iostream>
#include "sqlist_radix.h"
#include "RadixSort.cpp"

using namespace std;

void ListTraverse_Sq(SqList L) {
  for (int i = 0; i < L.length; i++) {
    for (int j = 0; j < L.r[i].bitsnum; j++)
      cout << L.r[i].keys[j];
    cout << " ";
  }
  cout << endl;
}

int main() {
  SqList L;
  L.length = 7;

  L.r[0].keys[0] = 0; L.r[0].keys[1] = 4; L.r[0].keys[2] = 9; L.r[0].bitsnum = 3;
  L.r[1].keys[0] = 0; L.r[1].keys[1] = 3; L.r[1].keys[2] = 8; L.r[1].bitsnum = 3;
  L.r[2].keys[0] = 0; L.r[2].keys[1] = 6; L.r[2].keys[2] = 5; L.r[2].bitsnum = 3;
  L.r[3].keys[0] = 0; L.r[3].keys[1] = 9; L.r[3].keys[2] = 7; L.r[3].bitsnum = 3;
  L.r[4].keys[0] = 0; L.r[4].keys[1] = 7; L.r[4].keys[2] = 6; L.r[4].bitsnum = 3;
  L.r[5].keys[0] = 0; L.r[5].keys[1] = 1; L.r[5].keys[2] = 3; L.r[5].bitsnum = 3;
  L.r[6].keys[0] = 0; L.r[6].keys[1] = 2; L.r[6].keys[2] = 7; L.r[6].bitsnum = 3;

  cout << "Before: ";
  ListTraverse_Sq(L);

  RadixSort(L);

  cout << "After: ";
  ListTraverse_Sq(L);

  return 0;
}
