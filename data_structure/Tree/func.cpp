#include "tree.h"
#include <algorithm>

int TreeDepth(CSTree T) {
  if (!T) {
    return 0;
  } else {
    int h1 = TreeDepth(T->firstchild);
    int h2 = TreeDepth(T->nextsibling);
    return (std::max(h1 + 1, h2));
  }
}
