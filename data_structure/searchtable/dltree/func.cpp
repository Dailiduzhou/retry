#include "dltree.h"

bool Search_DLTree(const DLTree &rt, const char line[], int count[], int j,
                   int &k) {
  k = 0;
  bool found = false;
  DLTNode *p = rt->first;
  while (p && !found) {
    while (p && p->symbol < line[j + k]) {
      p = p->next;
    }
    if (!p || p->symbol > line[j + k]) {
      break;
    } else {
      p = p->first;
      ++k;
      if (p && p->kind == NodeKind::LEAF) {
        count[p->idx]++;
        found = true;
      }
    }
  }
  return found;
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
      break;
    }
  }

  if (p && j == K.num) {
    if (p->first && p->first->kind == NodeKind::LEAF) {
      return false;
    } else {
      while (j <= K.num) {
        DLTNode *s = new DLTNode;
        s->next = p->first;
        p->first = s;
        p = s;
        if (j < K.num) {
          s->kind = NodeKind::BRANCH;
          s->symbol = K.ch[j++];
          s->first = nullptr;
        } else {
          s->kind = NodeKind::LEAF;
          s->symbol = '$';
          ++n;
          s->idx = n;
        }
      }
      return true;
    }
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
