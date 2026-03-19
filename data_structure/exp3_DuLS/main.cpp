#include "head.h"
#include <cstddef>
#include <iostream>

int main(int argc, char *argv[]) {
  DuLinkedList L;
  L->data = 0;
  L->prior = NULL;
  L->next = NULL;
  return 0;
}
