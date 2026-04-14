#include "stack.h"
#include "validate_stack_seq.h"
#include <iostream>

using namespace std;

void testValidateStackSequence() {
  cout << "Test 1: Valid sequence" << endl;

  vector<int> in1 = {1, 2, 3};
  vector<int> out1 = {2, 1, 3};

  bool result1 = isValid(in1, out1);

  cout << "In: [1, 2, 3], Out: [2, 1, 3]" << endl;
  cout << "Result: " << (result1 ? "Valid" : "Invalid") << endl;

  cout << "\nTest 2: Push all then pop all" << endl;

  vector<int> in2 = {1, 2, 3};
  vector<int> out2 = {3, 2, 1};

  bool result2 = isValid(in2, out2);

  cout << "In: [1, 2, 3], Out: [3, 2, 1]" << endl;
  cout << "Result: " << (result2 ? "Valid" : "Invalid") << endl;

  cout << "\nTest 3: Push and pop alternately" << endl;

  vector<int> in3 = {1, 2, 3, 4, 5};
  vector<int> out3 = {1, 2, 3, 4, 5};

  bool result3 = isValid(in3, out3);

  cout << "In: [1, 2, 3, 4, 5], Out: [1, 2, 3, 4, 5]" << endl;
  cout << "Result: " << (result3 ? "Valid" : "Invalid") << endl;

  cout << "\nTest 4: Invalid sequence" << endl;

  vector<int> in4 = {1, 2, 3};
  vector<int> out4 = {3, 1, 2};

  bool result4 = isValid(in4, out4);
  cout << "In: [1, 2, 3], Out: [3, 1, 2]" << endl;
  cout << "Result: " << (result4 ? "Valid" : "Invalid") << endl;

  cout << "\nTest 5: Different lengths" << endl;

  vector<int> in5 = {1, 2, 3};
  vector<int> out5 = {1, 2};

  bool result5 = isValid(in5, out5);
  cout << "In: [1, 2, 3], Out: [1, 2]" << endl;
  cout << "Result: " << (result5 ? "Valid" : "Invalid") << endl;
}

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

  testValidateStackSequence();

  return 0;
}
