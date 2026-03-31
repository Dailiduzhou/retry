#include "stack.h"
#include <iostream>
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
    cout << e << ' ';
  }
  cout << endl;
  DestroyStack(S);
}

bool matching(char exp[]) {
  SqStack S;
  InitStack_Sq(S);
  int state = 1;
  char ch = *exp++;

  while (ch != '#' && state) {
    switch (ch) {
    case '(':
    case '[':
      Push_Sq(S, ch);
      break;
    case ')': {
      SElemType top;
      if (GetTop_Sq(S, top) && top == '(') {
        Pop_Sq(S, top);
      } else {
        state = 0;
      }
      break;
    }
    case ']': {
      SElemType top;
      if (GetTop_Sq(S, top) && top == '[') {
        Pop_Sq(S, top);
      } else {
        state = 0;
      }
      break;
    }
    }
    ch = *exp++;
  }

  DestroyStack(S);
  return state && StackEmpty(S);
}

void knapsack(int w[], int T, int n) {
  SqStack S;
  InitStack_Sq(S);
  int k = 0;
  do {
    while (T > 0 && k < n) {
      if (T - w[k] >= 0) {
        Push_Sq(S, k);
        T -= w[k];
      }
      k++;
    }
    if (T == 0) {
      StackTraverse(S);
    }
    if (!StackEmpty(S)) {
      SElemType top;
      Pop_Sq(S, top);
      T += w[top];
      k = top + 1;
    }
  } while (!StackEmpty(S) || k < n);
  DestroyStack(S);
}

void test_conversion() {
  cout << "=== Test Conversion ===" << endl;
  cout << "Test 1: 1348 -> ";
  SqStack S;
  InitStack_Sq(S);
  int N = 1348;
  while (N) {
    Push_Sq(S, N % 8);
    N = N / 8;
  }
  SElemType e;
  while (!StackEmpty(S)) {
    Pop_Sq(S, e);
    cout << e;
  }
  cout << " (Expected: 2504)" << endl;
  DestroyStack(S);

  cout << "Test 2: 10 -> ";
  InitStack_Sq(S);
  N = 10;
  while (N) {
    Push_Sq(S, N % 8);
    N = N / 8;
  }
  while (!StackEmpty(S)) {
    Pop_Sq(S, e);
    cout << e;
  }
  cout << " (Expected: 12)" << endl;
  DestroyStack(S);
}

void test_matching() {
  cout << "=== Test Matching ===" << endl;

  char test1[] = "([])#";
  cout << "Test 1: " << test1 << " -> "
       << (matching(test1) ? "Match" : "Not Match") << " (Expected: Match)"
       << endl;

  char test2[] = "([)]#";
  cout << "Test 2: " << test2 << " -> "
       << (matching(test2) ? "Match" : "Not Match") << " (Expected: Not Match)"
       << endl;

  char test3[] = "(([]))#";
  cout << "Test 3: " << test3 << " -> "
       << (matching(test3) ? "Match" : "Not Match") << " (Expected: Match)"
       << endl;

  char test4[] = "([)#";
  cout << "Test 4: " << test4 << " -> "
       << (matching(test4) ? "Match" : "Not Match") << " (Expected: Not Match)"
       << endl;

  char test5[] = "([][]())#";
  cout << "Test 5: " << test5 << " -> "
       << (matching(test5) ? "Match" : "Not Match") << " (Expected: Match)"
       << endl;
}

void test_knapsack() {
  cout << "=== Test Knapsack ===" << endl;

  cout << "Test 1: w={1,8,4,3,5,2}, T=10" << endl;
  int w1[] = {1, 8, 4, 3, 5, 2};
  knapsack(w1, 10, 6);

  cout << "\nTest 2: w={2,3,5,7}, T=10" << endl;
  int w2[] = {2, 3, 5, 7};
  knapsack(w2, 10, 4);

  cout << "\nTest 3: w={5,5,10}, T=20" << endl;
  int w3[] = {5, 5, 10};
  knapsack(w3, 20, 3);
}

int main() {
  test_conversion();
  cout << endl;
  test_matching();
  cout << endl;
  test_knapsack();
  return 0;
}
