#ifndef BITREE_H_
#define BITREE_H_

typedef char TElemType;
typedef struct BiNode {
  TElemType data;
  struct BiNode *lchild, *rchild;
} BiNode, *BiTree;

void Preorder(BiTree T, void (*visit)(BiTree));

void InitBiTree(BiTree &T);
void DestroyBiTree(BiTree &T);
bool BiTreeEmpty(const BiTree &T);
int BiTreeDepth(const BiTree &T);
BiNode *Parent(BiTree T, BiNode *e);
BiNode *LeftChild(BiTree T, BiNode *e);
BiNode *RightChild(BiTree T, BiNode *e);
BiNode *LeftSibling(BiTree T, BiNode *e);
BiNode *RightSibling(BiTree T, BiNode *e);
bool InsertChild(BiTree &T, BiNode *p, int LR, BiNode *child);
bool DeleteChild(BiTree &T, BiNode *p, int LR);
void Traverse(const BiTree &T);
void CreateBiTree(BiTree &T);

void PreorderTraverse(BiTree T);
void PostorderTraverse(BiTree T);
void LevelTraverse(BiTree T);
BiNode *CreateBiNode(TElemType value);

void SwapChildren(BiTree &T);

BiNode *LowestCommonAncestor(BiTree root, BiNode *a, BiNode *b);

void searchBiTree(const BiTree &t, TElemType val);
enum class TaskType : int { Visit = 0, Travel = 1 };

#endif // !BITREE_H_
