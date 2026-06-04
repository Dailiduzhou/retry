#ifndef BTREE_HPP
#define BTREE_HPP

#include <cstring>
#include <iostream>
#include <stdexcept>

template <typename K, int T = 3> class BTree {
  static_assert(T >= 2, "B-tree minimum degree must be at least 2");

private:
  struct Node {
    int n;
    K *keys;
    Node **children;
    bool leaf;

    Node(bool is_leaf) : n(0), leaf(is_leaf) {
      keys = new K[2 * T - 1];
      children = new Node *[2 * T];
    }

    ~Node() {
      delete[] keys;
      delete[] children;
    }

    int find_key(const K &key) const {
      int idx = 0;
      while (idx < n && keys[idx] < key)
        ++idx;
      return idx;
    }

    void insert_nonfull(const K &key) {
      int i = n - 1;
      if (leaf) {
        while (i >= 0 && keys[i] > key) {
          keys[i + 1] = keys[i];
          --i;
        }
        keys[i + 1] = key;
        ++n;
      } else {
        while (i >= 0 && keys[i] > key)
          --i;
        ++i;
        if (children[i]->n == 2 * T - 1) {
          split_child(i, children[i]);
          if (keys[i] < key)
            ++i;
        }
        children[i]->insert_nonfull(key);
      }
    }

    void split_child(int i, Node *y) {
      Node *z = new Node(y->leaf);
      z->n = T - 1;

      for (int j = 0; j < T - 1; ++j)
        z->keys[j] = y->keys[j + T];

      if (!y->leaf) {
        // 把非叶子的节点后T - 1个元素分给后一个孩子
        for (int j = 0; j < T; ++j)
          z->children[j] = y->children[j + T];
      }

      y->n = T - 1;

      // 让出位置
      for (int j = n; j >= i + 1; --j)
        children[j + 1] = children[j];
      // 把后一个孩子挂上去
      children[i + 1] = z;

      for (int j = n - 1; j >= i; --j)
        keys[j + 1] = keys[j];
      keys[i] = y->keys[T - 1];
      ++n;
    }

    bool search(const K &key) const {
      int i = 0;
      while (i < n && key > keys[i])
        ++i;
      if (i < n && key == keys[i])
        return true;
      if (leaf)
        return false;
      return children[i]->search(key);
    }

    void remove(const K &key) {
      int idx = find_key(key);

      if (idx < n && keys[idx] == key) {
        if (leaf)
          remove_from_leaf(idx);
        else
          remove_from_nonleaf(idx);
      } else {
        if (leaf)
          return;

        bool last_child = (idx == n);
        if (children[idx]->n < T)
          fill(idx);

        // 如果是最后一个孩子，并且跟前一个孩子合并了
        if (last_child && idx > n)
          children[idx - 1]->remove(key);
        else
          children[idx]->remove(key);
      }
    }

    void remove_from_leaf(int idx) {
      for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];
      --n;
    }

    void remove_from_nonleaf(int idx) {
      K k = keys[idx];

      if (children[idx]->n >= T) {
        K pred_key = get_pred(idx);
        keys[idx] = pred_key;
        children[idx]->remove(pred_key);
      } else if (children[idx + 1]->n >= T) {
        K succ_key = get_succ(idx);
        keys[idx] = succ_key;
        children[idx + 1]->remove(succ_key);
      } else {
        merge(idx);
        children[idx]->remove(k);
      }
    }

    K get_pred(int idx) {
      Node *cur = children[idx];
      while (!cur->leaf)
        cur = cur->children[cur->n];
      return cur->keys[cur->n - 1];
    }

    K get_succ(int idx) {
      Node *cur = children[idx + 1];
      while (!cur->leaf)
        cur = cur->children[0];
      return cur->keys[0];
    }

    void fill(int idx) {
      if (idx != 0 && children[idx - 1]->n >= T)
        borrow_from_prev(idx);
      else if (idx != n && children[idx + 1]->n >= T)
        borrow_from_next(idx);
      else {
        if (idx != n)
          merge(idx);
        else
          merge(idx - 1);
      }
    }

    void borrow_from_prev(int idx) {
      Node *child = children[idx];
      Node *sibling = children[idx - 1];

      // 空出位置
      for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

      if (!child->leaf) {
        for (int i = child->n; i >= 0; --i)
          child->children[i + 1] = child->children[i];
      }

      // 把父节点的关键字降下来
      child->keys[0] = keys[idx - 1];

      // 非叶子节点继承sibling的最后一个节点的孩子
      if (!child->leaf)
        child->children[0] = sibling->children[sibling->n];

      // 把sibling的节点提升上去
      keys[idx - 1] = sibling->keys[sibling->n - 1];

      child->n += 1;
      sibling->n -= 1;
    }

    void borrow_from_next(int idx) {
      Node *child = children[idx];
      Node *sibling = children[idx + 1];

      child->keys[child->n] = keys[idx];

      if (!child->leaf)
        child->children[child->n + 1] = sibling->children[0];

      keys[idx] = sibling->keys[0];

      for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

      if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
          sibling->children[i - 1] = sibling->children[i];
      }

      child->n += 1;
      sibling->n -= 1;
    }

    void merge(int idx) {
      Node *child = children[idx];
      Node *sibling = children[idx + 1];

      // 父节点降下来
      child->keys[T - 1] = keys[idx];

      // 获取兄弟的节点
      for (int i = 0; i < sibling->n; ++i)
        child->keys[i + T] = sibling->keys[i];

      if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i)
          child->children[i + T] = sibling->children[i];
      }

      // 补全消失的父节点位置
      for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];

      // 跳过合并的节点
      for (int i = idx + 2; i <= n; ++i)
        children[i - 1] = children[i];

      child->n += sibling->n + 1;
      --n;

      delete sibling;
    }

    void traverse() const {
      if (leaf) {
        for (int i = 0; i < n; ++i)
          std::cout << keys[i] << " ";
      } else {
        for (int i = 0; i < n; ++i) {
          children[i]->traverse();
          std::cout << keys[i] << " ";
        }
        children[n]->traverse();
      }
    }

    K min_key() const {
      const Node *cur = this;
      while (!cur->leaf)
        cur = cur->children[0];
      return cur->keys[0];
    }

    K max_key() const {
      const Node *cur = this;
      while (!cur->leaf)
        cur = cur->children[cur->n];
      return cur->keys[cur->n - 1];
    }

    int height() const {
      if (leaf)
        return 0;
      return 1 + children[0]->height();
    }

    int count_nodes() const {
      int c = 1;
      if (!leaf) {
        for (int i = 0; i <= n; ++i)
          c += children[i]->count_nodes();
      }
      return c;
    }

    int count_keys() const {
      int c = n;
      if (!leaf) {
        for (int i = 0; i <= n; ++i)
          c += children[i]->count_keys();
      }
      return c;
    }
  };

  Node *root;

public:
  BTree() : root(nullptr) {}

  ~BTree() { destroy(root); }

  BTree(const BTree &) = delete;
  BTree &operator=(const BTree &) = delete;

  BTree(BTree &&other) noexcept : root(other.root) { other.root = nullptr; }

  BTree &operator=(BTree &&other) noexcept {
    if (this != &other) {
      destroy(root);
      root = other.root;
      other.root = nullptr;
    }
    return *this;
  }

  bool search(const K &key) const {
    if (!root)
      return false;
    return root->search(key);
  }

  bool contains(const K &key) const { return search(key); }

  void insert(const K &key) {
    if (!root) {
      root = new Node(true);
      root->keys[0] = key;
      root->n = 1;
      return;
    }

    if (root->n == 2 * T - 1) {
      // 给根节点虚造了一个父节点
      Node *s = new Node(false);
      s->children[0] = root;
      s->split_child(0, root);

      int i = 0;
      if (s->keys[0] < key)
        ++i;
      s->children[i]->insert_nonfull(key);
      root = s;
    } else {
      root->insert_nonfull(key);
    }
  }

  void remove(const K &key) {
    if (!root)
      return;

    root->remove(key);

    if (root->n == 0) {
      Node *tmp = root;
      if (root->leaf)
        root = nullptr;
      else
        root = root->children[0];
      delete tmp;
    }
  }

  void traverse() const {
    if (root) {
      root->traverse();
      std::cout << "\n";
    }
  }

  void print() const { print_node(root, 0); }

  K min() const {
    if (!root)
      throw std::runtime_error("B-tree is empty");
    return root->min_key();
  }

  K max() const {
    if (!root)
      throw std::runtime_error("B-tree is empty");
    return root->max_key();
  }

  int height() const {
    if (!root)
      return -1;
    return root->height();
  }

  int size() const {
    if (!root)
      return 0;
    return root->count_keys();
  }

  int node_count() const {
    if (!root)
      return 0;
    return root->count_nodes();
  }

  bool empty() const { return root == nullptr; }

private:
  void destroy(Node *node) {
    if (node) {
      if (!node->leaf) {
        for (int i = 0; i <= node->n; ++i)
          destroy(node->children[i]);
      }
      delete node;
    }
  }

  void print_node(const Node *node, int depth) const {
    if (!node)
      return;
    for (int i = 0; i < depth; ++i)
      std::cout << "  ";
    std::cout << "[";
    for (int i = 0; i < node->n; ++i) {
      std::cout << node->keys[i];
      if (i < node->n - 1)
        std::cout << " ";
    }
    std::cout << "]\n";
    if (!node->leaf) {
      for (int i = 0; i <= node->n; ++i)
        print_node(node->children[i], depth + 1);
    }
  }
};

#endif
