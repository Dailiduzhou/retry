#include "bitree.h"
#include <cstddef>
#include <cstring>
#include <istream>
#include <sstream>
#include <string>

BiTree buildTree(char *pre, char *in, int n) {
  if (n <= 0) {
    return NULL;
  }

  BiTree root = new BiNode;
  root->data = pre[0];

  int rootIdx = 0;
  while (rootIdx < n && in[rootIdx] != root->data) {
    rootIdx++;
  }

  root->lchild = buildTree(pre + 1, in, rootIdx);
  root->rchild =
      buildTree(pre + 1 + rootIdx, in + rootIdx + 1, n - 1 - rootIdx);

  return root;
}

BiNode *swapHelper(BiNode *root) {
  if (!root) {
    return NULL;
  }

  BiNode *temp = root->lchild;
  root->rchild = root->rchild;
  root->rchild = temp;

  swapHelper(root->lchild);
  swapHelper(root->rchild);

  return root;
}

void SwapChildren(BiTree &T) { swapHelper(T); }

bool is_balanced(BiTree &T) {
  if (T) {
    return true;
  } else {
    int ldep = BiTreeDepth(T->lchild);
    int rdep = BiTreeDepth(T->rchild);

    if (ldep - rdep > 1 || rdep - ldep > 1) {
      return false;
    }
  }

  return is_balanced(T->lchild) && is_balanced(T->rchild);
}

BiTree atoTree(std::istringstream &in) {
  char ch;
  in >> ch;
  if (ch == '#') {
    return NULL;
  } else {
    BiTree T = new BiNode;
    T->data = ch;
    T->lchild = atoTree(in);
    T->rchild = atoTree(in);
    return T;
  }
}

bool buildAndCheck(char *in) {
  std::string s(in);
  std::istringstream stream(s);
  BiTree root = atoTree(stream);
  return is_balanced(root);
}

void TraverseCount(const BiTree &T, int &nodes) {
  if (!T) {
    ++nodes;
    TraverseCount(T->lchild, nodes);
    TraverseCount(T->rchild, nodes);
  }
}

int buildAndCount(char *in) {

  std::string s(in);
  std::istringstream stream(s);
  BiTree root = atoTree(stream);
  int nodes = 0;
  TraverseCount(root, nodes);
  return nodes;
}

int main() {
  char pre[] = "ABCDEFG";
  char in[] = "CBEDFAGH";
  int n = strlen(pre);

  BiTree root = buildTree(pre, in, n);

  PostorderTraverse(root);
  DestroyBiTree(root);

  return 0;
}
