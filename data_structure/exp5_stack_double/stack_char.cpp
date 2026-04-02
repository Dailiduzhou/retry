#include "stack_char.h"
#include <iostream>

using namespace std;

void InitStack_Char(SqStackChar &S, int maxsize, int incresize) {
  S.elem = new SElemTypeChar[maxsize];
  S.top = -1;
  S.stacksize = maxsize;
  S.incrementsize = incresize;
}

bool GetTop_Char(SqStackChar S, SElemTypeChar &e) {
  if (S.top == -1)
    return false;
  e = S.elem[S.top];
  return true;
}

void Push_Char(SqStackChar &S, SElemTypeChar e) {
  if (S.top == S.stacksize - 1)
    incrementStacksize_Char(S);
  S.elem[++S.top] = e;
}

bool Pop_Char(SqStackChar &S, SElemTypeChar &e) {
  if (S.top == -1)
    return false;
  e = S.elem[S.top--];
  return true;
}

void DestroyStack_Char(SqStackChar &S) {
  delete[] S.elem;
  S.elem = nullptr;
  S.top = -1;
  S.stacksize = 0;
  S.incrementsize = 0;
}

void ClearStack_Char(SqStackChar &S) {
  S.top = -1;
}

bool StackEmpty_Char(SqStackChar S) {
  return S.top == -1;
}

int StackLength_Char(SqStackChar S) {
  return S.top + 1;
}

void incrementStacksize_Char(SqStackChar &S) {
  SElemTypeChar *new_elem = new SElemTypeChar[S.stacksize + S.incrementsize];
  S.stacksize += S.incrementsize;
  for (int i = 0; i <= S.top; ++i) {
    new_elem[i] = S.elem[i];
  }
  delete[] S.elem;
  S.elem = new_elem;
}

void StackTraverse_Char(SqStackChar S) {
  cout << "In the Stack (Char)\n";
  if (S.top == -1) {
    cout << "no element" << endl;
    return;
  }
  for (int i = 0; i <= S.top; ++i) {
    cout << S.elem[i] << endl;
  }
}
