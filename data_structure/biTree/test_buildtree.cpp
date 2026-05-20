#include "bitree.h"
#include <cstring>
#include <execution>
#include <iostream>
#include <sstream>
using namespace std;

BiTree buildTree(char *pre, char *in, int n);
void SwapChildren(BiTree &T);
bool is_balanced(BiTree &T);
bool buildAndCheck(char *in);
void TraverseCount(const BiTree &T, int &nodes);

void testSwapChildren() {
  cout << "=== Test SwapChildren ===" << endl;

  BiTree T1 = NULL;
  cout << "Test 1: Empty tree" << endl;
  cout << "Before swap:" << endl;
  Traverse(T1);
  SwapChildren(T1);
  cout << "After swap:" << endl;
  Traverse(T1);
  DestroyBiTree(T1);
  cout << endl;

  cout << "Test 2: Single node tree" << endl;
  BiTree T2 = CreateBiNode('A');
  cout << "Before swap:" << endl;
  Traverse(T2);
  SwapChildren(T2);
  cout << "After swap:" << endl;
  Traverse(T2);
  DestroyBiTree(T2);
  cout << endl;

  cout << "Test 3: Three node tree" << endl;
  BiTree T3 = NULL;
  BiNode *nA = CreateBiNode('A');
  BiNode *nB = CreateBiNode('B');
  BiNode *nC = CreateBiNode('C');
  nA->lchild = nB;
  nA->rchild = nC;
  T3 = nA;
  cout << "Before swap:" << endl;
  Traverse(T3);
  SwapChildren(T3);
  cout << "After swap:" << endl;
  Traverse(T3);
  DestroyBiTree(T3);
  cout << endl;

  cout << "Test 4: Five node tree" << endl;
  BiTree T4 = NULL;
  BiNode *nD = CreateBiNode('D');
  BiNode *nE = CreateBiNode('E');
  BiNode *nF = CreateBiNode('F');
  BiNode *nG = CreateBiNode('G');
  BiNode *nH = CreateBiNode('H');
  BiNode *nI = CreateBiNode('I');
  nD->lchild = nE;
  nD->rchild = nF;
  nE->lchild = nG;
  nE->rchild = nH;
  nG->lchild = nI;
  T4 = nD;
  cout << "Before swap:" << endl;
  Traverse(T4);

  //            D
  //          /   \
  //         E     F
  //        / \
  //       G   H
  //       /
  //      I
  cout << "\n\n\n";
  cout << "Lowest Parent: " << endl;
  BiNode *parent = LowestCommonAncestor(T4, nD, nG);
  cout << "Parent: " << parent->data << endl;
  parent = LowestCommonAncestor(T4, nH, nG);
  cout << "Parent: " << parent->data << endl;
  parent = LowestCommonAncestor(T4, nI, nH);
  cout << "Parent: " << parent->data << endl;
  parent = LowestCommonAncestor(T4, nI, nG);
  cout << "Parent: " << parent->data << endl;

  SwapChildren(T4);
  cout << "After swap:" << endl;
  Traverse(T4);
  DestroyBiTree(T4);
  cout << endl;
}

void testIsBalanced() {
  cout << "=== Test is_balanced ===" << endl;

  cout << "Test 1: Empty tree" << endl;
  BiTree T1 = NULL;
  cout << "is_balanced: " << (is_balanced(T1) ? "true" : "false") << endl;
  DestroyBiTree(T1);
  cout << endl;

  cout << "Test 2: Single node tree" << endl;
  BiTree T2 = CreateBiNode('A');
  Traverse(T2);
  cout << "is_balanced: " << (is_balanced(T2) ? "true" : "false") << endl;
  DestroyBiTree(T2);
  cout << endl;

  cout << "Test 3: Balanced tree" << endl;
  BiTree T3 = NULL;
  BiNode *nA = CreateBiNode('A');
  BiNode *nB = CreateBiNode('B');
  BiNode *nC = CreateBiNode('C');
  nA->lchild = nB;
  nA->rchild = nC;
  T3 = nA;
  Traverse(T3);
  cout << "is_balanced: " << (is_balanced(T3) ? "true" : "false") << endl;
  DestroyBiTree(T3);
  cout << endl;

  cout << "Test 4: Unbalanced tree (left heavy)" << endl;
  BiTree T4 = NULL;
  BiNode *nD = CreateBiNode('D');
  BiNode *nE = CreateBiNode('E');
  BiNode *nF = CreateBiNode('F');
  BiNode *nG = CreateBiNode('G');
  nD->lchild = nE;
  nE->lchild = nF;
  nF->lchild = nG;
  T4 = nD;
  Traverse(T4);
  cout << "is_balanced: " << (is_balanced(T4) ? "true" : "false") << endl;
  DestroyBiTree(T4);
  cout << endl;
}

void testBuildAndCheck() {
  cout << "=== Test buildAndCheck ===" << endl;

  cout << "Test 1: AB##C## (balanced)" << endl;
  char input1[] = "AB##C##";
  cout << "buildAndCheck: " << (buildAndCheck(input1) ? "true" : "false")
       << endl;
  cout << endl;

  cout << "Test 2: A#B#C## (unbalanced)" << endl;
  char input2[] = "A#B#C##";
  cout << "buildAndCheck: " << (buildAndCheck(input2) ? "true" : "false")
       << endl;
  cout << endl;

  cout << "Test 3: A#B## (unbalanced)" << endl;
  char input3[] = "A#B##";
  cout << "buildAndCheck: " << (buildAndCheck(input3) ? "true" : "false")
       << endl;
  cout << endl;
}

void testTraverseCount() {
  cout << "=== Test TraverseCount ===" << endl;

  cout << "Test 1: Empty tree" << endl;
  BiTree T1 = NULL;
  int nodes1 = 0;
  TraverseCount(T1, nodes1);
  cout << "TraverseCount: " << nodes1 << endl;
  DestroyBiTree(T1);
  cout << endl;

  cout << "Test 2: Single node tree" << endl;
  BiTree T2 = CreateBiNode('A');
  Traverse(T2);
  int nodes2 = 0;
  TraverseCount(T2, nodes2);
  cout << "TraverseCount: " << nodes2 << endl;
  DestroyBiTree(T2);
  cout << endl;

  cout << "Test 3: Three node tree" << endl;
  BiTree T3 = NULL;
  BiNode *nA = CreateBiNode('A');
  BiNode *nB = CreateBiNode('B');
  BiNode *nC = CreateBiNode('C');
  nA->lchild = nB;
  nA->rchild = nC;
  T3 = nA;
  Traverse(T3);
  int nodes3 = 0;
  TraverseCount(T3, nodes3);
  cout << "TraverseCount: " << nodes3 << endl;
  DestroyBiTree(T3);
  cout << endl;

  cout << "Test 4: Five node tree" << endl;
  BiTree T4 = NULL;
  BiNode *nD = CreateBiNode('D');
  BiNode *nE = CreateBiNode('E');
  BiNode *nF = CreateBiNode('F');
  BiNode *nG = CreateBiNode('G');
  BiNode *nH = CreateBiNode('H');
  nD->lchild = nE;
  nD->rchild = nF;
  nE->lchild = nG;
  nF->rchild = nH;
  T4 = nD;
  Traverse(T4);
  int nodes4 = 0;
  TraverseCount(T4, nodes4);
  cout << "TraverseCount: " << nodes4 << endl;
  DestroyBiTree(T4);
  cout << endl;
}

int main() {
  testSwapChildren();
  testIsBalanced();
  testBuildAndCheck();
  testTraverseCount();

  return 0;
}
