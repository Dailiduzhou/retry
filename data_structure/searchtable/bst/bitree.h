#ifndef BITREE_H_
#define BITREE_H_

typedef int KeyType;
typedef struct BiNode {
  KeyType data;
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
void Insert_BST(BiTree &T, KeyType e);
bool Insert_BST_bool(BiTree &T, KeyType e);
bool Search_BST(const BiTree &T, KeyType kval, BiTree &p, BiTree &f);
void Delete_BST(BiTree &T, KeyType kval);

enum class TaskType : int { Visit = 0, Travel = 1 };

#endif // !BITREE_H_
