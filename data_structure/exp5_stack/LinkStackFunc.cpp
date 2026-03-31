#include "stack.cpp"
#include "stack.h"
using namespace std;

void conversion() {
  SqStack S;
  InitStack_Sq(S);
  int N = 0;
  cin >> N;
  while (N) {
    Push_Sq(S, N % 8);
    N = N / 8;
  }

  SElemType e;
  while (!StackEmpty(S)) {
    Pop_Sq(S, e);
    cout << e << endl;
  }
}
