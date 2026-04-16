#ifndef BITREE_H_
#define BITREE_H_

typedef char TElemType;
typedef struct BiNode {
  TElemType data;
  struct BiNode *lchild, *rchild;
} BiNode, *BiTree;

void Preorder(BiTree T, void (*visit)(BiTree));

enum class TaskType : int { Visit = 0, Travel = 1 };

#endif // !BITREE_H_
