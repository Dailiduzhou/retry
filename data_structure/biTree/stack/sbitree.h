#ifndef SBITREE_H_
#define SBITREE_H_

typedef int TElemType;

typedef struct BiNode {
  TElemType data;
  struct BiNode *lchild, *rchild;
} BiNode, *BiTree;

void Preorder(BiTree T, void (*visit)(BiTree));

enum class TaskType : int { Visit = 0, Travel = 1 };

typedef struct {
  BiTree ptr;
  TaskType task;
} SElemType;

void InOrder_iter(BiTree BT, void (*visit)(BiTree));

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

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

#endif
