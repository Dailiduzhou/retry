#ifndef TREE_H_
#define TREE_H_

typedef int Elem;

const int MAX_TREE_SIZE = 100;

typedef struct PTNode {
  Elem data;
  int parent;
} PTNode;
typedef struct {
  PTNode nodes[MAX_TREE_SIZE];
  int r; // root pos
  int n; // root nums
} PTree;

typedef struct CTNode {
  int child;
  struct CTNode *next;
} *ChildPtr;

typedef struct {
  Elem data;
  ChildPtr firstchild;
} CTBox;

typedef struct {
  CTBox nodes[MAX_TREE_SIZE];
  int r; // root pos
  int n; // root nums
} Ctree;

typedef struct CSNode {
  Elem data;
  struct CSNode *firstchild, *nextsibling;
} CSNode, *CSTree;

int TreeDepth(CSTree T);

#endif // !TREE_H_
