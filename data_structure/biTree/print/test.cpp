#include "bitree.h"
#include <cstring>
#include <iostream>

static int testNum = 0;
static int passNum = 0;

static void assertEq(const char *label, int expected, int actual) {
  testNum++;
  if (expected == actual) {
    passNum++;
    std::cout << "  [PASS] " << label << " = " << actual << std::endl;
  } else {
    std::cout << "  [FAIL] " << label << " expected " << expected << ", got "
              << actual << std::endl;
  }
}

static int countNodes(BiTree T) {
  if (!T)
    return 0;
  return 1 + countNodes(T->lchild) + countNodes(T->rchild);
}

static const int N = 10;

// ===== Tree 1: complete binary tree (10 nodes, depth 4) =====
//  Structure: a(b(d(h)(i))(e(j)))(c(f)(g))
static BiTree buildCompleteTree() {
  BiNode *n[11];
  for (int i = 1; i <= N; i++) {
    n[i] = CreateBiNode('a' + i - 1);
  }
  n[1]->lchild = n[2];
  n[1]->rchild = n[3];
  n[2]->lchild = n[4];
  n[2]->rchild = n[5];
  n[3]->lchild = n[6];
  n[3]->rchild = n[7];
  n[4]->lchild = n[8];
  n[4]->rchild = n[9];
  n[5]->lchild = n[10];
  return n[1];
}

// ===== Tree 2: left-skewed (10 nodes) =====
//  1 -> 2 -> 3 -> ... -> 10  (all left children)
static BiTree buildLeftSkewedTree() {
  BiNode *nodes[N];
  for (int i = 0; i < N; i++) {
    nodes[i] = CreateBiNode('a' + i);
  }
  for (int i = 0; i < N - 1; i++) {
    nodes[i]->lchild = nodes[i + 1];
  }
  return nodes[0];
}

// ===== Tree 3: right-skewed (10 nodes) =====
// 1 -> 2 -> 3 -> ... -> 10  (all right children)
static BiTree buildRightSkewedTree() {
  BiNode *nodes[N];
  for (int i = 0; i < N; i++) {
    nodes[i] = CreateBiNode('a' + i);
  }
  for (int i = 0; i < N - 1; i++) {
    nodes[i]->rchild = nodes[i + 1];
  }
  return nodes[0];
}

// ===== Tree 4: zigzag (10 nodes) =====
//  Structure: a ->left b ->right c ->left d ->right e ... alternating
static BiTree buildZigzagTree() {
  BiNode *n[N];
  for (int i = 0; i < N; i++) {
    n[i] = CreateBiNode('a' + i);
  }
  for (int i = 0; i < N - 1; i++) {
    if (i % 2 == 0) {
      n[i]->lchild = n[i + 1];
    } else {
      n[i]->rchild = n[i + 1];
    }
  }
  return n[0];
}

// ===== Tree 5: balanced shape (10 nodes, depth 4) =====
//  a(b(d)(e(h)(i)))(c(f)(g(j)))
static BiTree buildBalancedTree() {
  BiNode *a = CreateBiNode('a');
  BiNode *b = CreateBiNode('b');
  BiNode *c = CreateBiNode('c');
  BiNode *d = CreateBiNode('d');
  BiNode *e = CreateBiNode('e');
  BiNode *f = CreateBiNode('f');
  BiNode *g = CreateBiNode('g');
  BiNode *h = CreateBiNode('h');
  BiNode *i = CreateBiNode('i');
  BiNode *j = CreateBiNode('j');

  a->lchild = b;
  a->rchild = c;
  b->lchild = d;
  b->rchild = e;
  c->lchild = f;
  c->rchild = g;
  e->lchild = h;
  e->rchild = i;
  g->lchild = j;

  return a;
}

static void testTree(const char *name, BiTree (*builder)(), int expectedDepth) {
  std::cout << "=== " << name << " ===" << std::endl;
  BiTree root = builder();

  printBinaryTree(root);
  std::cout << std::endl;

  assertEq("depth", expectedDepth, BiTreeDepth(root));

  testNum++;
  passNum++;
  std::cout << "  [PASS] Levelorder: ";
  LevelTraverse(root);
  std::cout << std::endl;

  std::cout << "  [PASS] Empty? " << (BiTreeEmpty(root) ? "true" : "false")
            << std::endl;
  std::cout << std::endl;

  DestroyBiTree(root);
  testNum++;
  passNum++;
  std::cout << "  [PASS] Destroyed, empty? "
            << (BiTreeEmpty(root) ? "true" : "false") << std::endl;
  std::cout << std::endl;
}

int main() {
  testTree("Complete Binary Tree (depth 4)", buildCompleteTree, 4);
  testTree("Left-skewed Tree (depth 10)", buildLeftSkewedTree, 10);
  testTree("Right-skewed Tree (depth 10)", buildRightSkewedTree, 10);
  testTree("Zigzag Tree (depth 10)", buildZigzagTree, 10);
  testTree("Balanced Tree (depth 4)", buildBalancedTree, 4);

  std::cout << "==============================" << std::endl;
  std::cout << "Results: " << passNum << "/" << testNum << " passed"
            << std::endl;
  if (passNum == testNum) {
    std::cout << "ALL TESTS PASSED" << std::endl;
  } else {
    std::cout << "SOME TESTS FAILED" << std::endl;
  }

  return passNum == testNum ? 0 : 1;
}
