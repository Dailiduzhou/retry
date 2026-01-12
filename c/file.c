#include <stdio.h>
#include <stdlib.h>

#define MAX 256

int main(int argc, char *argv[]) {
    FILE *fp, *fp1;
    char str[MAX];
    int i = 1;

    if (argc != 2)
        exit(-1);

    if ((fp = fopen(argv[1], "r")) == NULL)
        exit(-1);

        while (fgets(str, MAX, fp) != NULL) {
        printf("%d: %s", i++, str);
    }

    if ((fp1 = fopen(argv[1], "rb")) == NULL)
        exit(-1);
    int n;
    i = 1;

    while ((n = fread(str, 1, MAX, fp1)) > 0) {

        str[n] = '\0';

        // 注意：这里的 i 代表“第i个数据块”，而不是“第i行”
        printf("[%d] %s\n", i++, str);
    }

    fclose(fp);
    fclose(fp1);
    return 0;
}