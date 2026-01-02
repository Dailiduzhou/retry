#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* sort_line(const char* line) { // 使用 const 保护原字符串不被修改
    // 1. 修复内存分配大小
    // sizeof(line) 是指针大小(8字节)，必须用 strlen 获取实际长度
    // +1 是为了存放结尾的 '\0'
    char* res = (char*)malloc(strlen(line) + 1);
    if (res == NULL) {
        perror("malloc failed");
        exit(1);
    }

    // 2. 过滤空格
    int index = 0;
    int i = 0;
    while (line[i] != '\0') {
        if (line[i] != ' ' && line[i] != '\n') { // 同时过滤掉可能残留的换行符
            res[index++] = line[i];
        }
        i++;
    }
    res[index] = '\0'; // 必须手动封口

    // 3. 排序 (冒泡排序)
    // 注意边界是 index-1，避免 j 越界
    for (i = 0; i < index - 1; ++i) {
        for (int j = i + 1; j < index; ++j) {
            if (res[i] > res[j]) {
                char temp = res[i];
                res[i] = res[j];
                res[j] = temp;
            }
        }
    }

    // 4. 直接返回 res，删除了原代码中多余的第二次 malloc 和 strcpy
    // 原代码中的 strcpy(result, result) 是严重的逻辑错误
    return res;
}

int main() {
    char line[81];
    
    // 循环读取每一行
    while (fgets(line, sizeof(line), stdin) != NULL) {
        // strcspn 去除换行符是个好习惯，保留
        line[strcspn(line, "\n")] = '\0';
        
        // 5. 修复内存泄露
        // 必须用指针接住返回值，打印完后 free
        char* sorted = sort_line(line);
        if (sorted != NULL) {
            printf("%s\n", sorted);
            free(sorted); // 释放内存
        }
    }
    return 0;
}