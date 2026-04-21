#ifndef BITHRTREE_H_
#define BITHRTREE_H_

typedef int TElemType;

typedef struct BiThrNode {
  TElemType data;
  struct BiThrNode *lchild, *rchild;
  struct BiThrNode *pred, *succ;
} BiThrNode, *BiThrTree;

void InOrder(BiThrTree H, void (*visit)(BiThrTree));
void InOrderThreading(BiThrTree &H, BiThrTree T);
void InThreading(BiThrTree p, BiThrTree &pre);

#endif // !BITHRTREE_H_
