#include "btree.hpp"
#include <cassert>
#include <iostream>

int main() {
    {
        std::cout << "=== BTree<int, 3> (2-3-4 tree) ===\n";

        BTree<int, 3> tree;

        assert(tree.empty());
        assert(tree.height() == -1);
        assert(tree.size() == 0);

        int keys[] = {10, 20, 5, 6, 12, 30, 7, 17, 3, 25, 15, 1, 9, 22, 8};
        for (int k : keys)
            tree.insert(k);

        assert(!tree.empty());
        assert(tree.size() == 15);

        std::cout << "Inorder traversal: ";
        tree.traverse();

        std::cout << "Tree structure:\n";
        tree.print();

        std::cout << "Height: " << tree.height() << "\n";
        std::cout << "Size (keys): " << tree.size() << "\n";
        std::cout << "Nodes: " << tree.node_count() << "\n";
        std::cout << "Min: " << tree.min() << ", Max: " << tree.max() << "\n\n";

        for (int k : keys)
            assert(tree.contains(k));
        assert(!tree.contains(99));
        assert(tree.search(10));

        std::cout << "=== Delete tests ===\n";

        struct { int key; const char* desc; } dels[] = {
            {6, "leaf key"},
            {12, "another leaf key"},
            {30, "max key"},
            {1, "min key"},
            {17, "internal key"},
            {10, "root key after rotations"},
        };

        for (auto& d : dels) {
            std::cout << "Delete " << d.key << " (" << d.desc << "): ";
            assert(tree.contains(d.key));
            tree.remove(d.key);
            assert(!tree.contains(d.key));
            tree.traverse();
            tree.print();
            std::cout << "  size=" << tree.size() << "\n\n";
        }

        while (!tree.empty()) {
            int k = tree.min();
            tree.remove(k);
        }
        assert(tree.empty());
        assert(tree.size() == 0);
        assert(tree.height() == -1);
    }

    {
        std::cout << "\n=== BTree<char, 2> (2-3 tree) ===\n";
        BTree<char, 2> t;
        for (char c = 'a'; c <= 'z'; ++c)
            t.insert(c);
        std::cout << "Size: " << t.size() << "\n";
        std::cout << "Height: " << t.height() << "\n";
        std::cout << "Nodes: " << t.node_count() << "\n";
        assert(t.contains('m'));

        t.remove('p');
        t.remove('q');
        t.remove('z');
        assert(!t.contains('p'));
        assert(!t.contains('q'));
        assert(!t.contains('z'));
        std::cout << "Inorder after deletes: ";
        t.traverse();
    }

    {
        std::cout << "\n=== BTree<int, 10> (large degree) ===\n";
        BTree<int, 10> t;
        for (int i = 0; i < 1000; ++i)
            t.insert(i);
        assert(t.size() == 1000);
        std::cout << "Size: " << t.size() << "\n";
        std::cout << "Height: " << t.height() << "\n";
        std::cout << "Nodes: " << t.node_count() << "\n";
        for (int i = 0; i < 1000; ++i)
            assert(t.contains(i));

        for (int i = 0; i < 500; ++i)
            t.remove(i);
        assert(t.size() == 500);
        assert(t.min() == 500);
        std::cout << "After removing 0..499, size=" << t.size() << ", min=" << t.min() << "\n";
    }

    {
        std::cout << "\n=== Move semantics ===\n";
        BTree<int, 3> a;
        a.insert(1);
        a.insert(2);
        BTree<int, 3> b = std::move(a);
        assert(a.empty());
        assert(b.size() == 2);
        assert(b.contains(1));
        std::cout << "Move OK\n";
    }

    std::cout << "\nAll tests passed!\n";
    return 0;
}
