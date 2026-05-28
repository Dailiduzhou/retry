#include "bitree.h"
#include <cassert>
#include <iostream>
using namespace std;

static BiNode *makeLeaf(TElemType v) { return CreateBiNode(v); }

static BiNode *makeNode(TElemType v, BiNode *l, BiNode *r) {
  BiNode *n = CreateBiNode(v);
  n->lchild = l;
  n->rchild = r;
  return n;
}

static void freeTree(BiTree &T) { DestroyBiTree(T); }

void test_cal_wpl() {
  /*
   * Test 1: empty tree
   * WPL = 0
   */
  {
    BiTree t = NULL;
    assert(CalWPLBiTree(t) == 0);
    cout << "PASS: empty tree" << endl;
  }

  /*
   * Test 2: single leaf
   *       (5)
   * depth=0, leaf weight=5, WPL = 0*5 = 0
   */
  {
    BiTree t = makeLeaf(5);
    assert(CalWPLBiTree(t) == 0);
    freeTree(t);
    cout << "PASS: single leaf" << endl;
  }

  /*
   * Test 3: root internal, two leaf children
   *         (99)
   *        /    \
   *      (2)    (3)
   * Leaves: (2) depth=1, (3) depth=1
   * WPL = 1*2 + 1*3 = 5
   */
  {
    BiNode *l = makeLeaf(2);
    BiNode *r = makeLeaf(3);
    BiTree t = makeNode(99, l, r);
    assert(CalWPLBiTree(t) == 5);
    freeTree(t);
    cout << "PASS: two leaf children" << endl;
  }

  /*
   * Test 4: depth-2 tree with 3 leaves
   *               (0)
   *             /     \
   *          (1)      (2)
   *         /   \
   *       (3)   (4)
   * Leaves: (2) depth=1, (3) depth=2, (4) depth=2
   * WPL = 1*2 + 2*3 + 2*4 = 2 + 6 + 8 = 16
   */
  {
    BiNode *l3 = makeLeaf(3);
    BiNode *l4 = makeLeaf(4);
    BiNode *n1 = makeNode(1, l3, l4);
    BiNode *n2 = makeLeaf(2);
    BiTree t = makeNode(0, n1, n2);
    assert(CalWPLBiTree(t) == 16);
    freeTree(t);
    cout << "PASS: depth-2 tree, 3 leaves" << endl;
  }

  /*
   * Test 5: right-skewed tree (chain)
   *   (0)
   *     \
   *     (1)
   *       \
   *       (7)   <-- only leaf
   * Leaf (7) at depth=2, WPL = 2*7 = 14
   */
  {
    BiNode *l7 = makeLeaf(7);
    BiNode *n1 = makeNode(1, NULL, l7);
    BiTree t = makeNode(0, NULL, n1);
    assert(CalWPLBiTree(t) == 14);
    freeTree(t);
    cout << "PASS: right-skewed chain" << endl;
  }

  /*
   * Test 6: left-skewed tree (chain)
   *            (0)
   *           /
   *         (1)
   *        /
   *      (3)
   *     /
   *   (9)   <-- only leaf
   * Leaf (9) at depth=3, WPL = 3*9 = 27
   */
  {
    BiNode *l9 = makeLeaf(9);
    BiNode *n3 = makeNode(3, l9, NULL);
    BiNode *n1 = makeNode(1, n3, NULL);
    BiTree t = makeNode(0, n1, NULL);
    assert(CalWPLBiTree(t) == 27);
    freeTree(t);
    cout << "PASS: left-skewed chain" << endl;
  }

  /*
   * Test 7: full binary tree (depth 2, 4 leaves)
   *               (0)
   *             /     \
   *          (1)      (2)
   *         /   \    /   \
   *       (1)  (2) (3)  (4)
   * Leaves: all 4 at depth=2
   * WPL = 2*1 + 2*2 + 2*3 + 2*4 = 2 + 4 + 6 + 8 = 20
   */
  {
    BiNode *a = makeLeaf(1);
    BiNode *b = makeLeaf(2);
    BiNode *c = makeLeaf(3);
    BiNode *d = makeLeaf(4);
    BiNode *n1 = makeNode(1, a, b);
    BiNode *n2 = makeNode(2, c, d);
    BiTree t = makeNode(0, n1, n2);
    assert(CalWPLBiTree(t) == 20);
    freeTree(t);
    cout << "PASS: full tree depth-2, 4 leaves" << endl;
  }

  /*
   * Test 8: unbalanced tree
   *                 (0)
   *               /     \
   *            (1)      (2)
   *           /   \       \
   *         (3)   (4)     (5)
   *        /               \
   *      (6)               (7)
   * Leaves: (4) depth=2, (6) depth=3, (7) depth=3
   * Note: (5) is NOT a leaf (has right child)
   * WPL = 2*4 + 3*6 + 3*7 = 8 + 18 + 21 = 47
   */
  {
    BiNode *l6 = makeLeaf(6);
    BiNode *l4 = makeLeaf(4);
    BiNode *l7 = makeLeaf(7);
    BiNode *l5 = makeNode(5, NULL, l7);
    BiNode *n3 = makeNode(3, l6, NULL);
    BiNode *n1 = makeNode(1, n3, l4);
    BiNode *n2 = makeNode(2, NULL, l5);
    BiTree t = makeNode(0, n1, n2);
    assert(CalWPLBiTree(t) == 47);
    freeTree(t);
    cout << "PASS: unbalanced tree" << endl;
  }

  /*
   * Test 9: all-zero leaves
   *          (0)
   *         /   \
   *       (0)   (0)
   *      /   \
   *    (0)   (0)
   * All leaf data=0 -> WPL = 0 regardless of depth
   */
  {
    BiNode *a = makeLeaf(0);
    BiNode *b = makeLeaf(0);
    BiNode *c = makeLeaf(0);
    BiNode *n1 = makeNode(0, a, b);
    BiTree t = makeNode(0, n1, c);
    assert(CalWPLBiTree(t) == 0);
    freeTree(t);
    cout << "PASS: all-zero leaves" << endl;
  }

  cout << "\n--- All CalWPLBiTree tests passed ---\n" << endl;
}

int main() {
  test_cal_wpl();
  return 0;
}
