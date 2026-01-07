#include <stdio.h>
#include <stdlib.h>

#define MAX 256

int main(int argc, char * argv[]){
    FILE *fp, *fp1;
    char str[MAX];
    int i = 1;

    if (argc != 2) exit(-1);

    // 修改1: 读取文本文件通常使用 "r" 模式
    if ((fp = fopen(argv[1], "r")) == NULL) exit(-1);

    // 修改2: 使用 fgets 替代 fread
    // fgets 会读取直到换行符或缓冲区满，并自动添加 \0
    while (fgets(str, MAX, fp) != NULL){
        // 修改3: 格式化输出，加个冒号或空格更清晰
        printf("%d: %s", i++, str); 
    }

    if ((fp1 = fopen(argv[1], "rb")) == NULL) exit(-1);
    int n; i =1;
    // 修改2: 交换参数位置。读取 MAX 个元素，每个 1 字节。
    // 这样即使末尾只有 50 字节，fread 也会返回 50。
    while ((n = fread(str, 1, MAX, fp1)) > 0){
        // 修改3: 手动添加字符串结束符，否则 printf 会越界
        str[n] = '\0'; 
        
        // 注意：这里的 i 代表“第i个数据块”，而不是“第i行”
        printf("[%d] %s\n", i++, str);
    }

    fclose(fp);fclose(fp1);
    return 0;
}