#ifndef STACK_DOUBLE_H
#define STACK_DOUBLE_H

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

typedef double SElemTypeDouble;

typedef struct {
  SElemTypeDouble *elem;
  int top;
  int stacksize;
  int incrementsize;
} SqStackDouble;

void InitStack_Double(SqStackDouble &S, int maxsize = STACK_INIT_SIZE, int incresize = STACK_INCREMENT);
void DestroyStack_Double(SqStackDouble &S);
void ClearStack_Double(SqStackDouble &S);
bool StackEmpty_Double(SqStackDouble S);
int StackLength_Double(SqStackDouble S);
bool GetTop_Double(SqStackDouble S, SElemTypeDouble &e);
void Push_Double(SqStackDouble &S, SElemTypeDouble e);
bool Pop_Double(SqStackDouble &S, SElemTypeDouble &e);
void StackTraverse_Double(SqStackDouble S);
void incrementStacksize_Double(SqStackDouble &S);

#endif
