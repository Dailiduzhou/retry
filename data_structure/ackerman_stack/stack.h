#ifndef STACK_H
#define STACK_H

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

typedef struct {
  int nval;
  int xval;
  int yval;
} SElemType;

typedef struct {
  SElemType *elem;
  int top;
  int stacksize;
  int incrementsize;

} SqStack;

void InitStack_Sq(SqStack &S, int maxsize = STACK_INIT_SIZE,
                  int incresize = STACK_INCREMENT);
void DestroyStack(SqStack &S);
void ClearStack(SqStack &S);
bool StackEmpty(SqStack S);
int StackLength(SqStack S);
bool GetTop_Sq(SqStack S, SElemType &e);
void Push_Sq(SqStack &S, SElemType e);
bool Pop_Sq(SqStack &S, SElemType &e);
void StackTraverse(SqStack S);
void incrementStacksize(SqStack &S);

#endif // !STACK_H
