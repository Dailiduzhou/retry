#include <iostream>
#include <string>
#include <cmath>

typedef struct BiTree {
  char *data;
  int size;
  int capacity;
} BiTree;

int LeftChild(int i) { return 2 * i + 1; }

int RightChild(int i) { return 2 * i + 2; }

BiTree* createBiTree(const std::string& s) {
    BiTree* T = new BiTree;
    T->size = s.length();
    T->capacity = s.length();
    T->data = new char[T->capacity];
    for (int i = 0; i < T->size; i++) {
        T->data[i] = s[i];
    }
    return T;
}

void destroyBiTree(BiTree* T) {
    if (T) {
        delete[] T->data;
        delete T;
    }
}

int lastNonEmptyIndex(BiTree* T) {
    for (int i = T->size - 1; i >= 0; i--) {
        if (T->data[i] != '#') return i;
    }
    return -1;
}

int depth(BiTree* T) {
    if (!T || T->size == 0) return 0;
    int maxIdx = lastNonEmptyIndex(T);
    if (maxIdx < 0) return 0;
    return (int)(log2(maxIdx + 1)) + 1;
}

int countLeaves(BiTree* T) {
    if (!T || T->size == 0) return 0;
    int count = 0;
    int lastIdx = lastNonEmptyIndex(T);
    for (int i = 0; i <= lastIdx; i++) {
        if (T->data[i] == '#') continue;
        int left = LeftChild(i);
        int right = RightChild(i);
        bool leftChild = (left <= lastIdx && T->data[left] != '#');
        bool rightChild = (right <= lastIdx && T->data[right] != '#');
        if (!leftChild && !rightChild) count++;
    }
    return count;
}

bool isCompleteBinaryTree(BiTree* T) {
    if (!T || T->size == 0) return true;
    int lastIdx = lastNonEmptyIndex(T);
    if (lastIdx < 0) return true;
    bool sawEmpty = false;
    for (int i = 0; i <= lastIdx; i++) {
        if (T->data[i] != '#') {
            if (sawEmpty) return false;
        } else {
            sawEmpty = true;
        }
    }
    return true;
}

void test(BiTree* T, const char* label) {
    std::cout << "===== " << label << " =====" << std::endl;
    std::cout << "sequential: [";
    for (int i = 0; i < T->size && T->data[i]; i++) {
        if (i > 0) std::cout << " ";
        std::cout << T->data[i];
    }
    std::cout << "]" << std::endl;
    std::cout << "depth: " << depth(T) << std::endl;
    std::cout << "countLeaves: " << countLeaves(T) << std::endl;
    std::cout << "isCompleteBinaryTree: " << (isCompleteBinaryTree(T) ? "true" : "false") << std::endl;
    std::cout << std::endl;
}

int main(int argc, char **argv) {
    BiTree* t0 = createBiTree("");
    BiTree* t1 = createBiTree("A");
    BiTree* t2 = createBiTree("ABC");
    BiTree* t3 = createBiTree("ABC##D");
    BiTree* t4 = createBiTree("ABCDE");
    BiTree* t5 = createBiTree("AB#C###");

    test(t0, "empty tree");
    test(t1, "single node");
    test(t2, "full tree of depth 2");
    test(t3, "tree with gap (not complete)");
    test(t4, "complete tree with 5 nodes");
    test(t5, "left-skewed (not complete)");

    destroyBiTree(t0);
    destroyBiTree(t1);
    destroyBiTree(t2);
    destroyBiTree(t3);
    destroyBiTree(t4);
    destroyBiTree(t5);

    return 0;
}
