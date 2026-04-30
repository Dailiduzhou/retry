#include <cstddef>
#include <cstdlib>
#include <queue>
#include <vector>
const int N = 100;
struct HNode {
  int weight;
  HNode *lchild, *rchild;
};

using Htree = HNode *;
using namespace std;

struct Compare {
  bool operator()(Htree a, Htree b) {
    return a->weight > b->weight; // 最小堆
  }
};

Htree createHuffmanTree(int arr[], int n) {
  Htree forest[N];
  Htree root = NULL;
  for (int i = 0; i < n; i++) { // 将所有点存入森林
    Htree temp;
    temp = (Htree)malloc(sizeof(HNode));
    temp->weight = arr[i];
    temp->lchild = temp->rchild = NULL;
    forest[i] = temp;
  }

  for (int i = 1; i < n; i++) { // n-1 次循环建霍夫曼树
    int minn = -1, minnSub; // minn 为最小值树根下标，minnsub 为次小值树根下标
    for (int j = 0; j < n; j++) {
      if (forest[j] != NULL && minn == -1) {
        minn = j;
        continue;
      }
      if (forest[j] != NULL) {
        minnSub = j;
        break;
      }
    }

    for (int j = minnSub; j < n; j++) { // 根据 minn 与 minnSub 赋值
      if (forest[j] != NULL) {
        if (forest[j]->weight < forest[minn]->weight) {
          minnSub = minn;
          minn = j;
        } else if (forest[j]->weight < forest[minnSub]->weight) {
          minnSub = j;
        }
      }
    }

    // 建新树
    root = (Htree)malloc(sizeof(HNode));
    root->weight = forest[minn]->weight + forest[minnSub]->weight;
    root->lchild = forest[minn];
    root->rchild = forest[minnSub];

    forest[minn] = root;    // 指向新树的指针赋给 minn 位置
    forest[minnSub] = NULL; // minnSub 位置为空
  }
  return root;
}

Htree createHuffmanTreeOptimized(int arr[], int n) {
  priority_queue<Htree, vector<Htree>, Compare> pq;

  // 初始化：所有节点入堆
  for (int i = 0; i < n; i++) {
    Htree node = (Htree)malloc(sizeof(HNode));
    node->weight = arr[i];
    node->lchild = node->rchild = NULL;
    pq.push(node);
  }

  // 合并：每次取2个最小
  while (pq.size() > 1) {
    Htree left = pq.top();
    pq.pop();
    Htree right = pq.top();
    pq.pop();

    Htree parent = (Htree)malloc(sizeof(HNode));
    parent->weight = left->weight + right->weight;
    parent->lchild = left;
    parent->rchild = right;
    pq.push(parent);
  }

  return pq.empty() ? NULL : pq.top();
}
