#include "stack.h"
#include <iostream>

using namespace std;

int main() {
  SqStack S;
  SElemType e;

  InitStack_Sq(S, 5, 2);

  cout << "After init, StackEmpty: " << StackEmpty(S) << endl;
  cout << "StackLength: " << StackLength(S) << endl;

  Push_Sq(S, 10);
  Push_Sq(S, 20);
  Push_Sq(S, 30);
  Push_Sq(S, 40);
  Push_Sq(S, 50);

  cout << "\nAfter push 5 elements:" << endl;
  StackTraverse(S);
  cout << "StackLength: " << StackLength(S) << endl;

  Push_Sq(S, 60);
  Push_Sq(S, 70);

  cout << "\nAfter push 2 more (test increment):" << endl;
  StackTraverse(S);
  cout << "StackLength: " << StackLength(S) << endl;

  if (GetTop_Sq(S, e))
    cout << "\nTop element: " << e << endl;

  if (Pop_Sq(S, e)) {
    cout << "Popped: " << e << endl;
  }
  if (Pop_Sq(S, e)) {
    cout << "Popped: " << e << endl;
  }

  cout << "\nAfter pop 2 elements:" << endl;
  StackTraverse(S);
  cout << "StackEmpty: " << StackEmpty(S) << endl;
  cout << "StackLength: " << StackLength(S) << endl;

  ClearStack(S);
  cout << "\nAfter ClearStack:" << endl;
  StackTraverse(S);
  cout << "StackEmpty: " << StackEmpty(S) << endl;
  cout << "StackLength: " << StackLength(S) << endl;

  DestroyStack(S);

  return 0;
}
