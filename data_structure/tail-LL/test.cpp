#include "linkedlist.h"
#include <iostream>
using namespace std;

int main() {
  LinkList l;
  InitList(l);
  InsertList(l, 1);
  InsertList(l, 2);
  InsertList(l, 3);
  ListTraverse(l);

  ListDelete(l, 2);
  ListTraverse(l);
}
