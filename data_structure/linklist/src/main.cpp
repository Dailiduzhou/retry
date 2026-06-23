#include <iostream>

struct node {
  int data;
  node *next;
  node(int d = 0, node *n = nullptr) : data(d), next(n) {}
};

typedef node *LinkList;

LinkList createList(int arr[], int n) {
  LinkList head = new node();
  head->next = head;
  if (n == 0) {
    return head;
  }
  node *tail = head;
  for (int i = 0; i < n; ++i) {
    node *p = new node(arr[i]);
    tail->next = p;
    tail = p;
  }
  tail->next = head;
  return head;
}

void printList(const LinkList &l) {
  if (l == nullptr) {
    return;
  }
  node *p = l->next;
  if (p == l) {
    std::cout << "Empty\n";
    return;
  }

  while (p != l) {
    std::cout << p->data << " ";
    p = p->next;
  }
  std::cout << '\n';
  return;
}

void destroyList(LinkList &l) {
  if (l == nullptr) {
    return;
  }
  node *p = l->next;
  while (p != l) {
    node *q = p->next;
    delete p;
    p = q;
  }
  delete l;
  l = nullptr;
}

void Union(LinkList &La, LinkList &Lb) {
  if (La == nullptr || Lb == nullptr) {
    return;
  }

  if (La == La->next) {
    La->next = Lb->next;
    if (Lb != Lb->next) {
      node *tail = Lb->next;
      while (tail != Lb) {
        tail = tail->next;
      }
      tail->next = La;
    }
    delete Lb;
    Lb = nullptr;
    return;
  }

  if (Lb == Lb->next) {
    delete Lb;
    Lb = nullptr;
    return;
  }

  node *tailA = La;
  while (tailA->next != La) {
    tailA = tailA->next;
  }
  tailA->next = nullptr;

  node *tailB = Lb;
  while (tailB->next != Lb) {
    tailB = tailB->next;
  }
  tailB->next = nullptr;

  node *p = La->next;
  node *q = Lb->next;
  node *tail = La;
  La->next = nullptr;
  while (p != nullptr && q != nullptr) {
    if (p->data < q->data) {
      tail->next = p;
      tail = p;
      p = p->next;
    } else if (p->data > q->data) {
      tail->next = q;
      tail = q;
      q = q->next;
    } else {
      tail->next = p;
      tail = p;
      p = p->next;
      node *tmp = q;
      q = q->next;
      delete tmp;
    }
  }

  if (p != nullptr) {
    tail->next = p;
    while (tail->next != nullptr) {
      tail = tail->next;
    }
  } else if (q != nullptr) {
    tail->next = q;
    while (tail->next != nullptr) {
      tail = tail->next;
    }
  } else {
    tail->next = nullptr;
  }

  tail->next = La;
  delete Lb;
  Lb = nullptr;
  return;
}

int main() {
  int a[] = {1, 3, 5, 7};
  int b[] = {2, 3, 6, 8};
  LinkList La = createList(a, 4);
  LinkList Lb = createList(b, 4);

  std::cout << "La: ";
  printList(La);
  std::cout << "Lb: ";
  printList(Lb);

  Union(La, Lb);

  std::cout << "After union, La: ";
  printList(La);
  std::cout << "Lb is " << (Lb == nullptr ? "released." : "not null.")
            << std::endl;

  destroyList(La);
  return 0;
}
