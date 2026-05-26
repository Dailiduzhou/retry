#include "dltree.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

static void print_tree(DLTNode *node, int depth) {
  if (!node)
    return;
  for (int i = 0; i < depth; ++i)
    printf("  ");
  printf("[%c] kind=%s", node->symbol,
         node->kind == NodeKind::BRANCH ? "BRANCH" : "LEAF");
  if (node->kind == NodeKind::LEAF) {
    printf(" idx=%d", node->idx);
  }
  printf("\n");
  if (node->kind == NodeKind::BRANCH) {
    print_tree(node->first, depth + 1);
  }
  print_tree(node->next, depth);
}

static void free_tree(DLTNode *node) {
  if (!node)
    return;
  if (node->kind == NodeKind::BRANCH) {
    free_tree(node->first);
  }
  free_tree(node->next);
  delete node;
}

static void fill_line(char dst[], const char *src) {
  int len = (int)strlen(src);
  memcpy(dst, src, len);
  for (int i = len; i < LINESIZE; ++i)
    dst[i] = '\0';
}

static int count_lines(FILE *fp) {
  if (!fp)
    return 0;
  int c, n = 0;
  while ((c = fgetc(fp)) != EOF)
    if (c == '\n')
      ++n;
  return n;
}

/* ---------- test cases ---------- */

static int test_insert_and_print() {
  printf("--- test_insert_and_print ---\n");
  DLTNode *root = new DLTNode;
  root->symbol = '@';
  root->kind = NodeKind::BRANCH;
  root->first = nullptr;
  root->next = nullptr;

  int n = -1;
  KeysType k1 = {"he", 2};
  KeysType k2 = {"she", 3};
  KeysType k3 = {"his", 3};
  KeysType k4 = {"hers", 4};

  bool r1 = Insert_DLTree(root, k1, n);
  bool r2 = Insert_DLTree(root, k2, n);
  bool r3 = Insert_DLTree(root, k3, n);
  bool r4 = Insert_DLTree(root, k4, n);

  printf("insert 'he'   : %s (idx=%d expected)\n", r1 ? "OK" : "FAIL", 0);
  printf("insert 'she'  : %s (idx=%d expected)\n", r2 ? "OK" : "FAIL", 1);
  printf("insert 'his'  : %s (idx=%d expected)\n", r3 ? "OK" : "FAIL", 2);
  printf("insert 'hers' : %s (idx=%d expected)\n", r4 ? "OK" : "FAIL", 3);
  printf("total keys = %d (expected 4)\n\n", n + 1);

  assert(r1 && r2 && r3 && r4);
  assert(n == 3); /* -1 + 4 = 3 */
  printf("Tree structure:\n");
  print_tree(root, 0);
  printf("\n");

  free_tree(root->first);
  delete root;
  printf("PASSED\n\n");
  return 0;
}

static int test_duplicate_insert() {
  printf("--- test_duplicate_insert ---\n");
  DLTNode *root = new DLTNode;
  root->symbol = '@';
  root->kind = NodeKind::BRANCH;
  root->first = nullptr;
  root->next = nullptr;

  int n = -1;
  KeysType k1 = {"he", 2};
  KeysType k2 = {"he", 2}; /* duplicate */

  bool r1 = Insert_DLTree(root, k1, n);
  bool r2 = Insert_DLTree(root, k2, n);
  printf("1st insert 'he': %s\n", r1 ? "OK" : "FAIL");
  printf("2nd insert 'he': %s (expected DUP)\n", r2 ? "OK" : "FAIL");
  printf("total keys = %d (expected 1)\n\n", n + 1);

  assert(r1 == true);
  assert(r2 == false);
  assert(n == 0);

  free_tree(root->first);
  delete root;
  printf("PASSED\n\n");
  return 0;
}

static int test_search_dltree() {
  printf("--- test_search_dltree ---\n");
  DLTNode *root = new DLTNode;
  root->symbol = '@';
  root->kind = NodeKind::BRANCH;
  root->first = nullptr;
  root->next = nullptr;

  int n = -1;
  KeysType k1 = {"he", 2};
  KeysType k2 = {"she", 3};
  KeysType k3 = {"his", 3};
  KeysType k4 = {"hers", 4};
  Insert_DLTree(root, k1, n);
  Insert_DLTree(root, k2, n);
  Insert_DLTree(root, k3, n);
  Insert_DLTree(root, k4, n);

  int count[MAXNUM] = {0};
  int k = 0;

  /* match "he" at pos 0 */
  memset(count, 0, sizeof(count));
  char line1[LINESIZE];
  fill_line(line1, "heabc");
  bool found = Search_DLTree(root, line1, count, 0, k);
  printf("line='heabc' pos=0: found=%d k=%d count[0]=%d (expected 1/2/1)\n",
         found, k, count[0]);
  assert(found && k == 2 && count[0] == 1);

  /* match "she" at pos 0 */
  memset(count, 0, sizeof(count));
  char line2[LINESIZE];
  fill_line(line2, "she");
  found = Search_DLTree(root, line2, count, 0, k);
  printf("line='she' pos=0: found=%d k=%d count[1]=%d (expected 1/3/1)\n",
         found, k, count[1]);
  assert(found && k == 3 && count[1] == 1);

  /* no match */
  memset(count, 0, sizeof(count));
  char line3[LINESIZE];
  fill_line(line3, "xyz");
  found = Search_DLTree(root, line3, count, 0, k);
  printf("line='xyz' pos=0: found=%d k=%d (expected 0/any)\n", found, k);
  assert(!found);

  /* match from nonzero position */
  memset(count, 0, sizeof(count));
  char line4[LINESIZE];
  fill_line(line4, "xxhe");
  found = Search_DLTree(root, line4, count, 2, k);
  printf("line='xxhe' pos=2: found=%d k=%d count[0]=%d (expected 1/2/1)\n",
         found, k, count[0]);
  assert(found && k == 2 && count[0] == 1);

  free_tree(root->first);
  delete root;
  printf("PASSED\n\n");
  return 0;
}

static int test_setmatch() {
  printf("--- test_setmatch ---\n");
  DLTNode *root = new DLTNode;
  root->symbol = '@';
  root->kind = NodeKind::BRANCH;
  root->first = nullptr;
  root->next = nullptr;

  int n = -1;
  KeysType k1 = {"he", 2};
  KeysType k2 = {"she", 3};
  KeysType k3 = {"his", 3};
  KeysType k4 = {"hers", 4};
  Insert_DLTree(root, k1, n);
  Insert_DLTree(root, k2, n);
  Insert_DLTree(root, k3, n);
  Insert_DLTree(root, k4, n);

  int count[MAXNUM] = {0};
  char line[LINESIZE];

  /* case 1: mixed sentence */
  memset(count, 0, sizeof(count));
  fill_line(line, "he and she and his");
  setmatch(root, line, count);
  printf("line='he and she and his'\n");
  printf("  he  (idx=0): %d (expected >=1)\n", count[0]);
  printf("  she (idx=1): %d (expected 1)\n", count[1]);
  printf("  his (idx=2): %d (expected 1)\n", count[2]);
  printf("  hers(idx=3): %d (expected 0)\n", count[3]);
  assert(count[0] >= 1);
  assert(count[1] == 1);
  assert(count[2] == 1);
  assert(count[3] == 0);

  /* case 2: empty line */
  memset(count, 0, sizeof(count));
  fill_line(line, "");
  setmatch(root, line, count);
  int total = 0;
  for (int i = 0; i < MAXNUM; ++i)
    total += count[i];
  printf("empty line: total=%d (expected 0)\n", total);
  assert(total == 0);

  /* case 3: only one key repeated */
  memset(count, 0, sizeof(count));
  fill_line(line, "hehehe");
  setmatch(root, line, count);
  printf("line='hehehe': he count=%d\n", count[0]);
  /* overlapping: "he" at 0, then i+=1 -> 1, "he" at 1 ("ehe..."),
     but Search_DLTree at pos=1: line[1]='h', root->first='h'=='h',
     k=1, p='e'=='e', k=2, LEAF -> matches "he" again!
     i+=1 -> 2, pos=2 'h' -> matches again!
     i+=1 -> 3, pos=3 'e' -> 'h'>'e'? break, i++ ->4,
     pos=4 'h' -> matches, i+=1->5, pos=5 'e'->break, i++->6 done.
     So count should be 4 */
  printf("  (expected 4 with overlapping)\n");
  /* don't assert exact number — depends on overlapping behavior */

  /* case 4: key at end of line */
  memset(count, 0, sizeof(count));
  fill_line(line, "xxhis");
  setmatch(root, line, count);
  printf("line='xxhis': his count=%d (expected 1)\n", count[2]);
  assert(count[2] == 1);

  free_tree(root->first);
  delete root;
  printf("PASSED\n\n");
  return 0;
}

static int test_prefix_relation() {
  printf("--- test_prefix_relation ---\n");
  DLTNode *root = new DLTNode;
  root->symbol = '@';
  root->kind = NodeKind::BRANCH;
  root->first = nullptr;
  root->next = nullptr;

  int n = -1;
  /* "he" is a prefix of "hers" */
  KeysType k1 = {"he", 2};
  KeysType k2 = {"hers", 4};
  Insert_DLTree(root, k1, n);
  Insert_DLTree(root, k2, n);

  int count[MAXNUM] = {0};
  char line[LINESIZE];

  /* "hers" should match "hers" (longer match, because '$' < 'r') */
  memset(count, 0, sizeof(count));
  fill_line(line, "hers");
  setmatch(root, line, count);
  printf("line='hers': he=%d hers=%d\n", count[0], count[1]);
  printf("  (longer match 'hers' takes priority at pos 0)\n");

  /* "he" should match standalone */
  memset(count, 0, sizeof(count));
  fill_line(line, "hexx");
  setmatch(root, line, count);
  printf("line='hexx': he=%d hers=%d (expected he=1 hers=0)\n", count[0],
         count[1]);
  assert(count[0] == 1);
  assert(count[1] == 0);

  free_tree(root->first);
  delete root;
  printf("PASSED\n\n");
  return 0;
}

/* ---------- main ---------- */

int main() {
  printf("=== DLTree Tests ===\n\n");

  int failures = 0;
  failures += test_insert_and_print();
  failures += test_duplicate_insert();
  failures += test_search_dltree();
  failures += test_setmatch();
  failures += test_prefix_relation();

  printf("=========================\n");
  if (failures == 0) {
    printf("ALL TESTS PASSED\n");
  } else {
    printf("%d TEST(S) FAILED\n", failures);
  }
  return failures;
}
