#include <iostream>
#include "linkedlist.h"
#include "linkfunc.cpp"

using namespace std;

void ListTraverse(LinkedList L) {
  LNode *p = L->next;
  while (p) {
    cout << p->data << " ";
    p = p->next;
  }
  cout << endl;
}

LinkedList CreateList(int arr[], int n) {
  LinkedList L = new LNode;
  L->next = nullptr;
  LNode *tail = L;
  for (int i = 0; i < n; i++) {
    LNode *node = new LNode;
    node->data = arr[i];
    node->next = nullptr;
    tail->next = node;
    tail = node;
  }
  return L;
}

LNode *createNode(int data) {
  LNode *node = new LNode;
  node->data = data;
  node->next = nullptr;
  return node;
}

void testWithIntersection() {
  LNode *common = createNode(8);
  common->next = createNode(4);
  common->next->next = createNode(5);

  LinkedList headA = createNode(4);
  headA->next = createNode(1);
  headA->next->next = common;

  LinkedList headB = createNode(5);
  headB->next = createNode(6);
  headB->next->next = createNode(1);
  headB->next->next->next = common;

  LNode *result = getIntersectionNode(headA, headB);
  if (result == common) {
    cout << "testWithIntersection passed\n";
  } else {
    cout << "testWithIntersection failed\n";
  }
}

void testNoIntersection() {
  LinkedList headA = createNode(2);
  headA->next = createNode(6);
  headA->next->next = createNode(4);

  LinkedList headB = createNode(1);
  headB->next = createNode(5);

  LNode *result = getIntersectionNode(headA, headB);
  if (result == nullptr) {
    cout << "testNoIntersection passed\n";
  } else {
    cout << "testNoIntersection failed\n";
  }
}

void testBothEmpty() {
  LNode *result = getIntersectionNode(nullptr, nullptr);
  if (result == nullptr) {
    cout << "testBothEmpty passed\n";
  } else {
    cout << "testBothEmpty failed\n";
  }
}

void testOneEmpty() {
  LinkedList headA = createNode(1);
  headA->next = createNode(2);

  LNode *result = getIntersectionNode(headA, nullptr);
  if (result == nullptr) {
    cout << "testOneEmpty passed\n";
  } else {
    cout << "testOneEmpty failed\n";
  }
}

void testSameList() {
  LinkedList head = createNode(1);
  head->next = createNode(2);
  head->next->next = createNode(3);

  LNode *result = getIntersectionNode(head, head);
  if (result == head) {
    cout << "testSameList passed\n";
  } else {
    cout << "testSameList failed\n";
  }
}

int main() {
  int arr1[] = {1, 3, 5, 7, 9};
  int arr2[] = {2, 3, 4, 7, 10};

  LinkedList La = CreateList(arr1, 5);
  LinkedList Lb = CreateList(arr2, 5);

  cout << "La: ";
  ListTraverse(La);
  cout << "Lb: ";
  ListTraverse(Lb);

  LinkedList Lc = MergeAsc(La, Lb);

  cout << "Merged: ";
  ListTraverse(Lc);

  cout << "\nTesting getIntersectionNode:\n";
  testWithIntersection();
  testNoIntersection();
  testBothEmpty();
  testOneEmpty();
  testSameList();

  return 0;
}
