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
  unordered_map<char, CSNode *> lastChild;  // 记录每个父节点的最后一个孩子
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
        continue;  // 父节点未找到，跳过
      }
      if (!s->firstchild) {
        s->firstchild = p;
      } else {
        lastChild[fa]->nextsibling = p;  // 链接到该父节点的最后一个孩子
      }
      lastChild[fa] = p;  // 更新该父节点的最后一个孩子
    }
  }
}
