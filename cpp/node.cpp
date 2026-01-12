#include <cstdlib> // 推荐使用 cstdlib 而不是 stdlib.h
#include <iostream>

struct Node {
    int data;
    struct Node *next;
};

// 反转函数逻辑是正确的，保留即可
void invert(Node *&head) {
    if (head == NULL || head->next == NULL)
        return;
    Node *p, *q;
    p = head;
    q = head->next;
    p->next = NULL; // 原头变新尾
    while (q != NULL) {
        Node *next = q->next;
        q->next = p;
        p = q;
        q = next;
    }
    head = p; // 更新头指针
}

// 释放链表内存的辅助函数（好习惯）
void freeList(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node *head = NULL; // 初始化为空，而不是指向栈变量
    Node *tail = NULL; // 维护尾指针，优化插入效率

    int a;
    std::cout << "Input integers. Enter '0' to quit:" << std::endl;

    // 使用 cin >> a 读取整数，如果输入非数字或输入0则停止
    while (std::cin >> a && a != 0) {
        Node *p = new Node;
        if (!p)
            exit(-1);

        p->data = a;
        p->next = NULL;

        // 尾插法建立链表
        if (head == NULL) {
            head = p;
            tail = p;
        } else {
            tail->next = p; // 直接接到尾部
            tail = p;       // 更新尾指针
        }
    }

    // std::cout << "Original list created." << std::endl;
    // // (可选) 可以在这里打印原链表查看

    std::cout << "Let's see the inverse list.\n";
    invert(head);

    // 打印反转后的链表
    Node *current = head;
    while (current != NULL) {
        std::cout << current->data << std::endl << "|" << std::endl;
        current = current->next;
    }
    std::cout << "NULL" << std::endl;

    // 释放内存
    freeList(head);

    return 0;
}