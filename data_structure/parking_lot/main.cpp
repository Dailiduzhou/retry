#include "queue.h"
#include "stack.h"
#include <cassert>
#include <iostream>

using namespace std;

static SqStack S;
static LinkQueue Q;

void Init() {
  InitStack_Sq(S, 3, 0);
  InitQueue_L(Q);
}

void Enter(int car) {
  if (Push_Sq(S, car)) {
    cout << "Car " << car << " entered the lot\n";
  } else {
    Enqueue_L(Q, car);
    cout << "Car " << car << " is waiting in queue\n";
  }
}

void Exit(int car) {
  SqStack tmp;
  InitStack_Sq(tmp, S.stacksize, 0);

  int e;
  while (!StackEmpty(S)) {
    Pop_Sq(S, e);
    if (e == car) break;
    cout << "Car " << e << " moves out temporarily\n";
    Push_Sq(tmp, e);
  }
  while (!StackEmpty(tmp)) {
    Pop_Sq(tmp, e);
    Push_Sq(S, e);
    cout << "Car " << e << " moves back in\n";
  }
  DestroyStack(tmp);

  cout << "Car " << car << " exited the lot\n";

  if (!QueueEmpty_L(Q)) {
    int next;
    Dequeue_L(Q, next);
    Push_Sq(S, next);
    cout << "Car " << next << " moved from queue into lot\n";
  }
}

// --- unit tests ---

void test_push_fails_when_full() {
  SqStack s;
  InitStack_Sq(s, 2, 0);
  assert(Push_Sq(s, 1));
  assert(Push_Sq(s, 2));
  assert(!Push_Sq(s, 3));
  assert(StackLength(s) == 2);
  DestroyStack(s);
  cout << "[PASS] push fails when full\n";
}

void test_pop_empty() {
  SqStack s;
  InitStack_Sq(s, 2, 0);
  int e;
  assert(!Pop_Sq(s, e));
  DestroyStack(s);
  cout << "[PASS] pop on empty stack returns false\n";
}

void test_get_top() {
  SqStack s;
  InitStack_Sq(s, 3, 0);
  int e;
  assert(!GetTop_Sq(s, e)); // empty
  Push_Sq(s, 10);
  Push_Sq(s, 20);
  assert(GetTop_Sq(s, e) && e == 20);
  assert(StackLength(s) == 2); // top doesn't pop
  DestroyStack(s);
  cout << "[PASS] get top\n";
}

void test_clear() {
  SqStack s;
  InitStack_Sq(s, 3, 0);
  Push_Sq(s, 1);
  Push_Sq(s, 2);
  ClearStack(s);
  assert(StackEmpty(s));
  assert(StackLength(s) == 0);
  // can push again after clear
  assert(Push_Sq(s, 5));
  DestroyStack(s);
  cout << "[PASS] clear stack\n";
}

void test_exit_bottom_car() {
  // car at bottom exits — all others move out and back
  Init();
  Enter(1); Enter(2); Enter(3);
  Exit(1); // bottom car
  assert(StackLength(S) == 2);
  int e;
  Pop_Sq(S, e); assert(e == 3);
  Pop_Sq(S, e); assert(e == 2);
  DestroyStack(S); DestroyQueue_L(Q);
  cout << "[PASS] exit bottom car\n";
}

void test_multiple_queue_drain() {
  // lot size 3, queue 3 cars; each exit pulls one from queue
  Init();
  Enter(1); Enter(2); Enter(3); // lot full
  Enter(4); Enter(5); Enter(6); // all queued
  Exit(1); assert(StackLength(S) == 3); // 4 enters
  Exit(2); assert(StackLength(S) == 3); // 5 enters
  Exit(3); assert(StackLength(S) == 3); // 6 enters
  Exit(4); assert(StackLength(S) == 2);
  Exit(5); assert(StackLength(S) == 1);
  Exit(6); assert(StackEmpty(S));
  assert(QueueEmpty_L(Q));
  DestroyStack(S); DestroyQueue_L(Q);
  cout << "[PASS] multiple queue drain\n";
}

void test_exit_nonexistent_car() {
  // exiting a car not in lot — all cars are restored, stack unchanged
  Init();
  Enter(1); Enter(2);
  Exit(99); // not in lot — cars 1 and 2 are restored
  assert(StackLength(S) == 2);
  DestroyStack(S); DestroyQueue_L(Q);
  cout << "[PASS] exit non-existent car\n";
}

void run_tests() {
  test_push_fails_when_full();
  test_pop_empty();
  test_get_top();
  test_clear();
  test_exit_bottom_car();
  test_multiple_queue_drain();
  test_exit_nonexistent_car();
  cout << "All tests passed.\n\n";
}

// --- interactive loop ---

void run_interactive() {
  Init();
  cout << "Commands: A <car> to enter, D <car> to exit, Q to quit\n";
  char cmd;
  int car;
  while (cin >> cmd) {
    if (cmd == 'Q' || cmd == 'q') break;
    if (!(cin >> car)) break;
    if (cmd == 'A' || cmd == 'a')
      Enter(car);
    else if (cmd == 'D' || cmd == 'd')
      Exit(car);
    else
      cout << "Unknown command. Use A <car> or D <car>.\n";
  }
  DestroyStack(S);
  DestroyQueue_L(Q);
}

int main() {
  run_tests();
  run_interactive();
  return 0;
}
