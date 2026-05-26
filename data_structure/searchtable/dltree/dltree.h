#ifndef DLTREE_H_
#define DLTREE_H_

const int LINESIZE = 80;
const int MAXKEYLEN = 16;
const int MAXNUM = 100;

typedef struct {
  char ch[MAXKEYLEN];
  int num;
} KeysType;
enum class NodeKind : int { LEAF = 0, BRANCH = 1 };
typedef struct DLTNode {
  char symbol;
  struct DLTNode *next;
  NodeKind kind;
  union {
    struct DLTNode *first;
    int idx;
  };
} DLTNode, *DLTree;

bool Search_DLTree(const DLTree &rt, const char line[], int count[], int j, int &k);
bool Insert_DLTree(DLTree &root, KeysType K, int &n);
void setmatch(const DLTree &root, char line[], int count[]);

#endif // !DLTREE_H_
