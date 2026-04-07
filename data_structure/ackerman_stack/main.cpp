#include "stack.h"
#include <iostream>

using namespace std;

int Ackerman(int n, int x, int y);
int value(int n, int x, int y);

int main() {
  int n = Ackerman(3, 2, 1);
  cout << "A(3,2,1) equals to " << n << endl;
}

int Ackerman(int n, int x, int y) {
  SqStack S;
  InitStack_Sq(S);
  SElemType e;
  e.nval = n;
  e.xval = x;
  e.yval = y;
  int u = -1;

  Push_Sq(S, e);

  do {
    GetTop_Sq(S, e);

    while (e.nval != 0 && e.yval != 0) {
      e.yval--;
      Push_Sq(S, e);
    }

    Pop_Sq(S, e);
    u = value(e.nval, e.xval, e.yval);

    if (!StackEmpty(S)) {
      Pop_Sq(S, e);
      e.nval--;
      e.yval = e.xval;
      e.xval = u;
      Push_Sq(S, e);
    }
  } while (!StackEmpty(S));
  return u;
}

int value(int n, int x, int y) {
  if (n == 0) {
    return (x + 1);
  }

  switch (n) {
  case 1:
    return x;
  case 2:
    return 0;
  case 3:
    return 1;
  default:
    return 2;
  }
}
