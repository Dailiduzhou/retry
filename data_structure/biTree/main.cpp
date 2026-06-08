#include "bitree.h"
#include <iostream>
using namespace std;

int main() {
  // 1. InitBiTree: initialize an empty tree
  BiTree T;
  InitBiTree(T);
  cout << " 1. InitBiTree" << endl;
  cout << "BiTreeEmpty: " << (BiTreeEmpty(T) ? "true" : "false") << endl;
  Traverse(T);

  // 2. Build a tree manually: A(B(D,E),C(,F))
  //          A
  //        /   \
  //       B     C
  //      / \     \
  //     D   E     F
  BiNode *nA = CreateBiNode('A');
  BiNode *nB = CreateBiNode('B');
  BiNode *nC = CreateBiNode('C');
  BiNode *nD = CreateBiNode('D');
  BiNode *nE = CreateBiNode('E');
  BiNode *nF = CreateBiNode('F');
  nA->lchild = nB;
  nA->rchild = nC;
  nB->lchild = nD;
  nB->rchild = nE;
  nC->rchild = nF;
  T = nA;

  cout << "\n\n" << "searchBiTree";
  searchBiTree(T, 'B');
  cout << "\n\n";

  cout << "\n 2. Manual build: A(B(D,E),C(,F)) " << endl;
  Traverse(T);
  cout << "BiTreeEmpty: " << (BiTreeEmpty(T) ? "true" : "false")
       << ", BiTreeDepth: " << BiTreeDepth(T) << endl;

  // 3. Parent: find parent node of a given node
  cout << "\n 3. Parent " << endl;
  BiNode *p = Parent(T, nB);
  cout << "Parent(B) = " << (p ? &p->data : NULL) << ": " << (p ? p->data : ' ')
       << endl;
  p = Parent(T, nD);
  cout << "Parent(D) = " << (p ? p->data : ' ') << endl;
  p = Parent(T, nA);
  cout << "Parent(A) = " << (p ? "non-null" : "NULL") << endl;

  // 4. LeftChild / RightChild
  cout << "\n 4. LeftChild / RightChild " << endl;
  BiNode *lc = LeftChild(T, nA);
  BiNode *rc = RightChild(T, nA);
  cout << "LeftChild(A)  = " << (lc ? lc->data : ' ') << endl;
  cout << "RightChild(A) = " << (rc ? rc->data : ' ') << endl;
  lc = LeftChild(T, nC);
  rc = RightChild(T, nC);
  cout << "LeftChild(C)  = " << (lc ? lc->data : ' ') << endl;
  cout << "RightChild(C) = " << (rc ? rc->data : ' ') << endl;

  // 5. LeftSibling / RightSibling
  cout << "\n 5. LeftSibling / RightSibling " << endl;
  BiNode *ls = LeftSibling(T, nC);
  BiNode *rs = RightSibling(T, nB);
  cout << "LeftSibling(C)  = " << (ls ? ls->data : ' ') << endl;
  cout << "RightSibling(B) = " << (rs ? rs->data : ' ') << endl;
  ls = LeftSibling(T, nE);
  rs = RightSibling(T, nD);
  cout << "LeftSibling(E)  = " << (ls ? ls->data : ' ') << endl;
  cout << "RightSibling(D) = " << (rs ? rs->data : ' ') << endl;

  // 6. InsertChild: insert G as left child of C (LR=0)
  //    Before: C(,F)  ->  After: C(G,F) where G's rchild = NULL
  cout << "\n 6. InsertChild: insert G as left child of C " << endl;
  BiNode *nG = CreateBiNode('G');
  InsertChild(T, nC, 0, nG);
  Traverse(T);

  // 7. InsertChild: insert H as right child of D (LR=1)
  //    Before: D  ->  After: D(,H)
  cout << "\n 7. InsertChild: insert H as right child of D " << endl;
  BiNode *nH = CreateBiNode('H');
  InsertChild(T, nD, 1, nH);
  Traverse(T);

  // 8. DeleteChild: delete left child of C (removes G subtree)
  cout << "\n 8. DeleteChild: delete left child of C " << endl;
  DeleteChild(T, nC, 0);
  Traverse(T);

  // 9. DeleteChild: delete right child of D (removes H subtree)
  cout << "\n 9. DeleteChild: delete right child of D " << endl;
  DeleteChild(T, nD, 1);
  Traverse(T);

  // 10. DestroyBiTree: destroy entire tree
  cout << "\n 10. DestroyBiTree " << endl;
  DestroyBiTree(T);
  cout << "BiTreeEmpty: " << (BiTreeEmpty(T) ? "true" : "false") << endl;
  Traverse(T);

  // 11. CreateBiTree: build tree from preorder input ('#' = null)
  //     Example input: ABD##E##C#F##
  //     This produces the same tree: A(B(D,E),C(,F))
  cout << "\n 11. CreateBiTree (input preorder, use '#' for null) " << endl;
  cout << "Example: ABD##E##C#F##" << endl;
  cout << "Enter: ";
  CreateBiTree(T);
  cout << "BiTreeDepth: " << BiTreeDepth(T) << endl;
  Traverse(T);

  DestroyBiTree(T);
  return 0;
}
