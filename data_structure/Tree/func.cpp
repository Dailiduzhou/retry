#include "stack.h"
#include "tree.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

int TreeDepth(CSTree T) {
  if (!T) {
    return 0;
  } else {
    int h1 = TreeDepth(T->firstchild);
    int h2 = TreeDepth(T->nextsibling);
    return (std::max(h1 + 1, h2));
  }
}

void OutPath(CSTree T, SqStack &S) {
  Elem e;
  while (T) {
    Push_Sq(S, T->data);
    if (!T->firstchild) {
      StackTraverse(S);
    } else {
      OutPath(T->firstchild, S);
    }
    Pop_Sq(S, e);
    T = T->nextsibling;
  }
}

void CreateTree(CSTree &T) {
  char fa, ch;
  T = NULL;
  queue<CSNode *> q;
  unordered_map<char, CSNode *> lastChild; // 记录每个父节点的最后一个孩子
  for (cin >> fa >> ch; ch != '#'; cin >> fa >> ch) {
    CSNode *p = new CSNode;
    p->data = ch;
    p->firstchild = p->nextsibling = NULL;
    q.emplace(p);
    if (fa == '#') {
      T = p;
    } else {
      // 在队列中查找父节点，不破坏队列结构
      int n = q.size();
      CSNode *s = NULL;
      for (int i = 0; i < n; i++) {
        CSNode *temp = q.front();
        q.pop();
        if (temp->data == fa) {
          s = temp;
        }
        q.emplace(temp);
      }
      if (!s) {
        continue; // 父节点未找到，跳过
      }
      if (!s->firstchild) {
        s->firstchild = p;
      } else {
        lastChild[fa]->nextsibling = p; // 链接到该父节点的最后一个孩子
      }
      lastChild[fa] = p; // 更新该父节点的最后一个孩子
    }
  }
}

void InitCSTree(CSTree &T) { T = nullptr; }

// 销毁树
void DestroyCSTree(CSTree &T) {
  if (T) {
    DestroyCSTree(T->firstchild);
    DestroyCSTree(T->nextsibling);
    delete T;
    T = nullptr;
  }
}

// 树是否为空
bool CSTreeEmpty(CSTree T) { return T == nullptr; }

// 返回父节点
Elem Parent(CSTree T, Elem e) {
  if (T == nullptr) {
    return -1;
  }
  if ((T->firstchild && T->firstchild->data == e) ||
      (T->nextsibling && T->nextsibling->data == e)) {
    return T->data;
  }

  Elem p = Parent(T->firstchild, e);
  if (p != -1) {
    return p;
  }

  return Parent(T->nextsibling, e);
}

// 返回第一个孩子节点（左子节点）
Elem LeftChild(CSTree T, Elem e) {
  if (T == nullptr) {
    return -1;
  }
  if (T->data == e) {
    return (T->firstchild) ? T->firstchild->data : -1;
  }

  Elem res = LeftChild(T->firstchild, e);
  if (res != -1) {
    return res;
  }

  return LeftChild(T->nextsibling, e);
}

// 返回下一个兄弟节点（右子节点）
Elem RightChild(CSTree T, Elem e) {
  if (T == nullptr) {
    return -1;
  }
  if (T->data == e) {
    return (T->nextsibling) ? T->nextsibling->data : -1;
  }

  Elem res = RightChild(T->firstchild, e);
  if (res != -1) {
    return res;
  }

  return RightChild(T->nextsibling, e);
}

// 返回左兄弟节点
Elem LeftSibling(CSTree T, Elem e) {
  if (T == nullptr || T->data == e) {
    return -1;
  }

  Elem res = Parent(T, e);
  if (res == -1) {
    return -1;
  }

  Elem ans = LeftChild(T, res);
  if (ans == -1) {
    return -1;
  }

  return ans;
}

// 返回右兄弟节点
Elem RightSibling(CSTree T, Elem e) {
  if (T == nullptr || T->data == e) {
    return -1;
  }

  Elem res = Parent(T, e);
  if (res == -1) {
    return -1;
  }

  Elem ans = RightChild(T, res);
  if (ans == -1) {
    return -1;
  }

  return ans;
}

// 插入子树
// LR为0插第一个孩子，为1插下一个兄弟
bool InsertChild(CSTree &T, Elem p, int LR, CSTree C) {
  if (T == nullptr) {
    return false;
  }

  if (T->data == p) {
    if (LR == 0) {
      if (T->firstchild) {
        return false;
      }
      T->firstchild = C;
    } else {
      if (T->nextsibling) {
        return false;
      }
      T->nextsibling = C;
    }
    return true;
  }

  bool res = InsertChild(T->firstchild, p, LR, C);
  if (res) {
    return true;
  }

  return InsertChild(T->nextsibling, p, LR, C);
}

// 删除子树
bool DeleteChild(CSTree &T, Elem p, int LR) {
  if (T == nullptr) {
    return false;
  }

  if (T->data == p) {
    if (LR == 0) {
      if (T->firstchild) {
        DestroyCSTree(T->firstchild);
        T->firstchild = nullptr;
      }
      return true;
    } else {
      if (T->nextsibling) {
        DestroyCSTree(T->nextsibling);
        T->nextsibling = nullptr;
      }
      return true;
    }
  }

  bool res = DeleteChild(T->firstchild, p, LR);
  if (res) {
    return true;
  }

  return DeleteChild(T->nextsibling, p, LR);
}

// 前序遍历
void PreorderTraverse(CSTree T) {
  if (T) {
    cout << T->data << " ";
    PreorderTraverse(T->firstchild);
    PreorderTraverse(T->nextsibling);
  }
}

// 中序遍历
void InorderTraverse(CSTree T) {
  if (T) {
    InorderTraverse(T->firstchild);
    cout << T->data << " ";
    InorderTraverse(T->nextsibling);
  }
}

// 后序遍历
void PostorderTraverse(CSTree T) {
  if (T) {
    PostorderTraverse(T->firstchild);
    PostorderTraverse(T->nextsibling);
    cout << T->data << " ";
  }
}

// 层级遍历
void LevelTraverse(CSTree T) {
  if (T == nullptr) {
    return;
  }
  queue<CSTree> q;
  q.push(T);

  while (!q.empty()) {
    CSTree node = q.front();
    q.pop();
    cout << node->data << " ";

    if (node->firstchild) {
      q.push(node->firstchild);
    }
    if (node->nextsibling) {
      q.push(node->nextsibling);
    }
  }
}

// 插入节点
CSNode *CreateCSNode(Elem value) {
  CSNode *newNode = new CSNode();
  newNode->data = value;
  newNode->firstchild = newNode->nextsibling = nullptr;
  return newNode;
}
