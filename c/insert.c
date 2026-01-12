#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 注意：如果想将结果写回 s1，调用时 s1 必须有足够的空间
void insert(char *s1, char *s2, char ch) {
    char *p;
    p = strchr(s1, ch);

    // 如果没找到字符 ch，直接返回
    if (!p)
        return;

    char *result = (char *)malloc(strlen(s1) + strlen(s2) + 1);

    char *remaining = (char *)malloc(strlen(p) * sizeof(char) + 1);
    strcpy(remaining, p);

    int prefix_len = p - s1;

    memcpy(result, s1, prefix_len);

    memcpy(result + prefix_len, s2, strlen(s2));

    strcpy(result + prefix_len + strlen(s2), remaining);

    strcpy(s1, result);

    free(result);
    free(remaining);
}

int main() {
    char text[100] = "HelloWorld";
    char insert_str[] = " My ";
    char target = 'W';

    printf("Original: %s\n", text);

    insert(text, insert_str, target);

    printf("Result:   %s\n", text);

    return 0;
}