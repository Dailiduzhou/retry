#ifndef STACK_CHAR_H
#define STACK_CHAR_H

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

typedef char SElemTypeChar;

typedef struct {
  SElemTypeChar *elem;
  int top;
  int stacksize;
  int incrementsize;
} SqStackChar;

void InitStack_Char(SqStackChar &S, int maxsize = STACK_INIT_SIZE, int incresize = STACK_INCREMENT);
void DestroyStack_Char(SqStackChar &S);
void ClearStack_Char(SqStackChar &S);
bool StackEmpty_Char(SqStackChar S);
int StackLength_Char(SqStackChar S);
bool GetTop_Char(SqStackChar S, SElemTypeChar &e);
void Push_Char(SqStackChar &S, SElemTypeChar e);
bool Pop_Char(SqStackChar &S, SElemTypeChar &e);
void StackTraverse_Char(SqStackChar S);
void incrementStacksize_Char(SqStackChar &S);

#endif
