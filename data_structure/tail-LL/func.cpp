#include "linkedlist.h"
#include <iostream>

void InitList(LinkList &L) { L.tail = nullptr; }

void InsertList(LinkList &L, ElemType val) {
  LNode *newN = new LNode;
  newN->data = val;
  newN->next = nullptr;
  if (!L.tail) {
    L.tail = newN;
    newN->next = newN;
    return;
  }

  LNode *head = L.tail->next;
  L.tail->next = newN;
  newN->next = head;
  L.tail = newN;
}

LNode *getHead(LinkList &L) {
  if (L.tail == nullptr) {
    return nullptr;
  }
  return L.tail->next;
}

void ListDelete(LinkList &L, ElemType val) {
  if (L.tail == nullptr)
    return;

  LNode *head = L.tail->next;

  if (head == L.tail) {
    if (head->data == val) {
      delete head;
      L.tail = nullptr;
    }
    return;
  }

  // int len = ListLength(L);
  // LNode *pre = L.tail;
  // LNode *cur = head;
  //
  // for (int i = 0; i < len; i++) {
  //   if (cur->data == val) {
  //     LNode *next = cur->next;
  //     bool isLastNode = (cur->next == cur);
  //     bool wasTail = (cur == L.tail);
  //
  //     pre->next = next;
  //
  //     if (isLastNode) {
  //       delete cur;
  //       L.tail = nullptr;
  //       return;
  //     }
  //
  //     if (wasTail) {
  //       L.tail = pre;
  //     }
  //
  //     delete cur;
  //     cur = next;
  //   } else {
  //     pre = cur;
  //     cur = cur->next;
  //   }
  // }
  LNode *pre = L.tail;
  LNode *cur = head;
  do {
    if (cur->data == val) {
      LNode *next = cur->next;
      pre->next = next;
      if (cur == L.tail) {
        L.tail = pre;
      }

      if (next == cur) {
        delete cur;
        L.tail = nullptr;
        return;
      }
      delete cur;
      cur = next;
    } else {
      pre = cur;
      cur = cur->next;
    }
  } while (cur != head);
}

int ListLength(LinkList &L) {
  if (L.tail == nullptr) {
    return 0;
  }

  int count = 0;
  LNode *cur = L.tail->next;
  do {
    count++;
    cur = cur->next;
  } while (cur != L.tail->next);
  return count;
}

void ListTraverse(LinkList &L) {
  if (L.tail == nullptr) {
    return;
  }

  LNode *cur = L.tail->next;
  do {
    std::cout << cur->data << ' ';
    cur = cur->next;
  } while (cur != L.tail->next);
  std::cout << "\n\n";
}
