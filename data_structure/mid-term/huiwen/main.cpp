#include "queue.h"
#include "stack.h"
#include <cstring>

int huiwen(char *str) {
  int len = strlen(str);
  if (len == 0) {
    return 1;
  }

  SqStack S;
  LinkQueue Q;
  InitStack_Sq(S, len);
  InitQueue_L(Q);

  char *c = str;
  while ((*c) != '\0') {
    Push_Sq(S, *c);
    Enqueue_L(Q, *c);
    c++;
  }

  int a, b;
  bool is_palindrome = true;
  while (!StackEmpty(S) && !QueueEmpty_L(Q)) {
    Pop_Sq(S, a);
    Dequeue_L(Q, b);
    if (a != b) {
      is_palindrome = false;
      break;
    }
  }

  DestroyStack(S);
  DestroyQueue_L(Q);
  return is_palindrome ? 1 : 0;
}
