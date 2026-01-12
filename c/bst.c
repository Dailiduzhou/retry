#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[20];
    struct Node *left;
    struct Node *right;
} Node;

/* 创建新节点 */
static Node *new_node(const char *name) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strncpy(n->name, name, sizeof(n->name) - 1);
    n->name[sizeof(n->name) - 1] = '\0';
    n->left = n->right = NULL;
    return n;
}

/* 按字典序插入；若已存在相同 key，则忽略 */
Node *bst_insert(Node *root, const char *name) {
    if (root == NULL) {
        return new_node(name);
    }
    int cmp = strcmp(name, root->name);
    if (cmp < 0) {
        root->left = bst_insert(root->left, name);
    } else if (cmp > 0) {
        root->right = bst_insert(root->right, name);
    } else {
        /* 已存在，保持不变 */
    }
    return root;
}

/* 查找 */
Node *bst_find(Node *root, const char *name) {
    if (!root)
        return NULL;
    int cmp = strcmp(name, root->name);
    if (cmp == 0)
        return root;
    if (cmp < 0)
        return bst_find(root->left, name);
    return bst_find(root->right, name);
}

/* 找到最小值节点（用于删除） */
static Node *bst_min_node(Node *root) {
    Node *cur = root;
    while (cur && cur->left)
        cur = cur->left;
    return cur;
}

/* 删除节点 */
Node *bst_delete(Node *root, const char *name) {
    if (!root)
        return NULL;
    int cmp = strcmp(name, root->name);
    if (cmp < 0) {
        root->left = bst_delete(root->left, name);
    } else if (cmp > 0) {
        root->right = bst_delete(root->right, name);
    } else {
        /* 找到目标节点 */
        if (!root->left) {
            Node *r = root->right;
            free(root);
            return r;
        } else if (!root->right) {
            Node *l = root->left;
            free(root);
            return l;
        } else {
            /* 两个孩子：用右子树最小节点替换 */
            Node *succ = bst_min_node(root->right);
            strncpy(root->name, succ->name, sizeof(root->name) - 1);
            root->name[sizeof(root->name) - 1] = '\0';
            root->right = bst_delete(root->right, succ->name);
        }
    }
    return root;
}

/* 中序遍历（按字典序输出） */
void bst_inorder(Node *root) {
    if (!root)
        return;
    bst_inorder(root->left);
    printf("%s\n", root->name);
    bst_inorder(root->right);
}

/* 先序遍历 */
void bst_preorder(Node *root) {
    if (!root)
        return;
    printf("%s\n", root->name);
    bst_preorder(root->left);
    bst_preorder(root->right);
}

/* 后序遍历 */
void bst_postorder(Node *root) {
    if (!root)
        return;
    bst_postorder(root->left);
    bst_postorder(root->right);
    printf("%s\n", root->name);
}

/* 释放整棵树 */
void bst_free(Node *root) {
    if (!root)
        return;
    bst_free(root->left);
    bst_free(root->right);
    free(root);
}

int main(void) {
    const char *names[] = {"Lily", "Bob",   "Zoe",  "Alice",
                           "Mike", "Cindy", "David"};
    size_t n = sizeof(names) / sizeof(names[0]);

    Node *root = NULL;
    for (size_t i = 0; i < n; ++i) {
        root = bst_insert(root, names[i]);
    }

    printf("中序遍历(字典序):\n");
    bst_inorder(root);

    const char *q = "Mike";
    printf("\n查找 %s: %s\n", q, bst_find(root, q) ? "FOUND" : "NOT FOUND");

    root = bst_delete(root, "Bob");
    printf("\n删除 Bob 后的前序遍历:\n");
    bst_preorder(root);
    printf("\n删除 Bob 后的中序遍历:\n");
    bst_inorder(root);
    printf("\n删除 Bob 后的后序遍历:\n");
    bst_postorder(root);

    bst_free(root);
    return 0;
}