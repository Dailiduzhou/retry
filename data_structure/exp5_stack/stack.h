#ifndef STACK_H
#define STACK_H

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

typedef int SElemType;

typedef struct {
  SElemType *elem;
  int top;
  int stacksize;
  int incrementsize;

} SqStack;

void InitStack_Sq(SqStack &S, int maxsize, int incresize);
void DestroyStack(SqStack &S);
void ClearStack(SqStack &S);
void StackEmpty(SqStack S);
int StackLength(SqStack S);
void GetTop_Sq(SqStack S, SElemType &e);
void Push_Sq(SqStack &S, SElemType e);
void Pop_Sq(SqStack &S, SElemType &e);
void StackTraverse(SqStack S);

#endif // !STACK_H
