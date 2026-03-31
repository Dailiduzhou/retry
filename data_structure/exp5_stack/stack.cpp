#include "stack.h"
#include <iostream>

using namespace std;

void InitStack_Sq(SqStack &S, int maxsize = STACK_INIT_SIZE,
                  int incresize = STACK_INCREMENT) {
  S.elem = new SElemType[maxsize];

  S.top = -1;
  S.stacksize = maxsize;
  S.incrementsize = incresize;
}

bool GetTop_Sq(SqStack S, SElemType &e) {
  if (S.top == -1)
    return false;
  e = S.elem[S.top];
  return true;
}

void Push_Sq(SqStack &S, SElemType e) {
  if (S.top == S.stacksize - 1)
    incrementStacksize(S);
  S.elem[++S.top] = e;
}

bool Pop_Sq(SqStack &S, SElemType &e) {
  if (S.top == -1)
    return false;
  e = S.elem[S.top--];
  return true;
}

void DestroyStack(SqStack &S) {
  delete[] S.elem;
  S.elem = nullptr;
  S.top = -1;
  S.stacksize = 0;
  S.incrementsize = 0;
}

void ClearStack(SqStack &S) {
  S.top = -1;
}

bool StackEmpty(SqStack S) {
  return S.top == -1;
}

int StackLength(SqStack S) {
  return S.top + 1;
}

void incrementStacksize(SqStack &S) {
  SElemType *new_elem = new SElemType[S.stacksize + S.incrementsize];
  S.stacksize += S.incrementsize;
  for (int i = 0; i <= S.top; ++i) {
    new_elem[i] = S.elem[i];
  }
  delete[] S.elem;
  S.elem = new_elem;
}

void StackTraverse(SqStack S) {
  cout << "In the Stack\n";
  if (S.top == -1) {
    cout << "no element" << endl;
    return;
  }
  for (int i = 0; i <= S.top; ++i) {
    cout << S.elem[i] << endl;
  }
}
