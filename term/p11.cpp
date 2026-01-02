#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word {
    char word[80];
    unsigned count;
    struct Word* next; // C语言标准写法建议加上struct，C++可省略
} Word;

Word* create_node(const char* word, unsigned count){
    Word* new_node = (Word *)malloc(sizeof(Word));
    if (!new_node){
        perror("Memory allocation failed");
        exit(1);
    }
    // 保证字符串以 \0 结尾
    strncpy(new_node->word, word, sizeof(new_node->word) - 1);
    new_node->word[sizeof(new_node->word) - 1] = '\0';
    new_node->count = count;
    new_node->next = NULL;
    return new_node;
}

// 核心逻辑修改：查找单词，找到则计数+1，没找到则插入到头部
// 使用二级指针是因为可能会修改 head 的指向
void add_word(Word** head, const char* token) {
    Word* current = *head;
    
    // 1. 先查找是否存在
    while (current != NULL) {
        if (strcmp(current->word, token) == 0) {
            current->count++;
            return; // 找到了，处理完毕直接返回
        }
        current = current->next;
    }

    Word* new_node = create_node(token, 1);
    new_node->next = *head;
    *head = new_node;
}

void swap_data(Word* a, Word* b){
    char temp_word[80];
    strcpy(temp_word, a->word);
    strcpy(a->word, b->word);
    strcpy(b->word, temp_word);
    
    unsigned temp_count = a->count;
    a->count = b->count;
    b->count = temp_count;
}

void sort_list(Word* head){
    if (head == NULL || head->next == NULL) {
        return;
    }

    Word* current;
    Word* last = NULL;
    int swapped;

    do {
        swapped = 0;
        current = head;

        while (current->next != last) {
            if (current->count < current->next->count) {
                swap_data(current, current->next);
                swapped = 1;
            } else if (current->count == current->next->count && 
                       strcmp(current->word, current->next->word) > 0){
                swap_data(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

// 新增：释放链表内存
void free_list(Word* head) {
    Word* current = head;
    while (current != NULL) {
        Word* temp = current;
        current = current->next;
        free(temp);
    }
}

int main(){
    Word * head = NULL;
    char line[1001];

    // 建议增加非空检查
    if (fgets(line, 1000, stdin) == NULL) {
        return 0;
    }

    // 处理换行符的安全写法
    size_t len = strlen(line);
    if (len > 0 && line[len-1] == '\n') {
        line[len-1] = '\0';
    }

    // 直接使用 line 进行分割，不需要 malloc 额外的 copy，减少内存碎片
    // 分隔符增加了 \t (制表符) 和 \r (回车)，增强鲁棒性
    char* token = strtok(line, " \t\r");
    while (token != NULL) {
        add_word(&head, token); // 调用封装好的函数
        token = strtok(NULL, " \t\r");
    }
    
    sort_list(head);
    
    Word* current = head;
    while (current != NULL) {
        printf("%s %u\n", current->word, current->count);
        current = current->next;
    }
    
    // 释放链表
    free_list(head);

    return 0;
}