#include "stack_double.h"
#include <iostream>

using namespace std;

void InitStack_Double(SqStackDouble &S, int maxsize, int incresize) {
  S.elem = new SElemTypeDouble[maxsize];
  S.top = -1;
  S.stacksize = maxsize;
  S.incrementsize = incresize;
}

bool GetTop_Double(SqStackDouble S, SElemTypeDouble &e) {
  if (S.top == -1)
    return false;
  e = S.elem[S.top];
  return true;
}

void Push_Double(SqStackDouble &S, SElemTypeDouble e) {
  if (S.top == S.stacksize - 1)
    incrementStacksize_Double(S);
  S.elem[++S.top] = e;
}

bool Pop_Double(SqStackDouble &S, SElemTypeDouble &e) {
  if (S.top == -1)
    return false;
  e = S.elem[S.top--];
  return true;
}

void DestroyStack_Double(SqStackDouble &S) {
  delete[] S.elem;
  S.elem = nullptr;
  S.top = -1;
  S.stacksize = 0;
  S.incrementsize = 0;
}

void ClearStack_Double(SqStackDouble &S) {
  S.top = -1;
}

bool StackEmpty_Double(SqStackDouble S) {
  return S.top == -1;
}

int StackLength_Double(SqStackDouble S) {
  return S.top + 1;
}

void incrementStacksize_Double(SqStackDouble &S) {
  SElemTypeDouble *new_elem = new SElemTypeDouble[S.stacksize + S.incrementsize];
  S.stacksize += S.incrementsize;
  for (int i = 0; i <= S.top; ++i) {
    new_elem[i] = S.elem[i];
  }
  delete[] S.elem;
  S.elem = new_elem;
}

void StackTraverse_Double(SqStackDouble S) {
  cout << "In the Stack (Double)\n";
  if (S.top == -1) {
    cout << "no element" << endl;
    return;
  }
  for (int i = 0; i <= S.top; ++i) {
    cout << S.elem[i] << endl;
  }
}
