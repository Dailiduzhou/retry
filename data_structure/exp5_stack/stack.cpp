#include "stack.h"
#include <iostream>

using namespace std;

void InitStack_Sq(SqStack &S, int maxsize = STACK_INIT_SIZE,
                  int incresize = STACK_INCREMENT) {
  S.elem = new SElemType[maxsize];
}
