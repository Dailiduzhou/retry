#include "dltree.h"

bool Search_DLTree(const DLTree &rt, const char line[], int count[], int j,
                   int &k) {
  k = 0;
  DLTNode *p = rt->first;
  int best_k = 0;
  int best_idx = -1;

  while (p) {
    while (p && p->symbol < line[j + k]) {
      p = p->next;
    }
    if (!p || p->symbol > line[j + k]) {
      break;
    }
    p = p->first;
    ++k;
    if (p && p->kind == NodeKind::LEAF) {
      best_k = k;
      best_idx = p->idx;
    }
  }

  if (best_idx >= 0) {
    count[best_idx]++;
    k = best_k;
    return true;
  }
  return false;
}

void setmatch(const DLTree &root, char line[], int count[]) {
  int i = 0;
  int k = 0;
  while (i < LINESIZE) {
    if (!Search_DLTree(root, line, count, i, k)) {
      ++i;
    } else {
      i += k - 1;
    }
  }
}

bool Insert_DLTree(DLTree &root, KeysType K, int &n) {
  DLTNode *p = root->first;
  DLTNode *f = root;
  int j = 0;
  while (p && j < K.num) {
    DLTNode *pre = nullptr;
    while (p && p->symbol < K.ch[j]) {
      pre = p;
      p = p->next;
    }

    if (p && p->symbol == K.ch[j]) {
      f = p;
      p = p->first;
      ++j;
    } else {
      DLTNode *s = new DLTNode;
      s->kind = NodeKind::BRANCH;
      s->symbol = K.ch[j++];
      s->first = nullptr;
      if (pre) {
        pre->next = s;
      } else {
        f->first = s;
      }
      s->next = p;
      p = s;
      f = s;
      break;
    }
  }

  if (j == K.num) {
    if (f->first && f->first->kind == NodeKind::LEAF) {
      return false;
    }
    DLTNode *s = new DLTNode;
    s->kind = NodeKind::LEAF;
    s->symbol = '$';
    s->next = f->first;
    f->first = s;
    ++n;
    s->idx = n;
    return true;
  }

  if (j < K.num) {
    while (j <= K.num) {
      DLTNode *s = new DLTNode;
      s->kind = (j < K.num) ? NodeKind::BRANCH : NodeKind::LEAF;
      s->symbol = (j < K.num) ? K.ch[j] : '$';
      s->first = nullptr;
      s->next = nullptr;
      f->first = s;
      f = s;
      if (j == K.num) {
        ++n;
        s->idx = n;
      }
      ++j;
    }
    return true;
  }

  return false;
}
