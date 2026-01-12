#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // 新增: 用于物理文件比较

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "用法: %s <目的文件> <源文件>\n", argv[0]);
        return 1;
    }

    const char *destPath = argv[1];
    const char *srcPath = argv[2];

    struct stat srcStat, dstStat;
    if (stat(srcPath, &srcStat) == 0 && stat(destPath, &dstStat) == 0) {
        if (srcStat.st_dev == dstStat.st_dev &&
            srcStat.st_ino == dstStat.st_ino) {
            fprintf(
                stderr,
                "错误: "
                "源文件与目的文件指向同一个物理文件，拒绝操作以防止死循环。\n");
            return 1;
        }
    }

    FILE *src = fopen(srcPath, "rb");
    if (!src) {
        fprintf(stderr, "无法打开源文件: %s: %s\n", srcPath, strerror(errno));
        return 1;
    }

    FILE *dst = fopen(destPath, "ab");
    if (!dst) {
        int e = errno;
        fclose(src);
        fprintf(stderr, "无法打开目的文件: %s: %s\n", destPath, strerror(e));
        return 1;
    }

    char buffer[8192];
    size_t nread;
    while ((nread = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        size_t nwritten = fwrite(buffer, 1, nread, dst);
        if (nwritten != nread) {
            fprintf(stderr, "写入错误: %s (可能磁盘已满)\n", strerror(errno));
            fclose(src);
            fclose(dst);
            return 1;
        }
    }

    if (ferror(src)) {
        fprintf(stderr, "读取源文件时发生错误: %s\n", strerror(errno));
        fclose(src);
        fclose(dst);
        return 1;
    }

    fclose(src);

    if (fclose(dst) != 0) {
        fprintf(stderr, "关闭目的文件时发生错误 (数据可能未保存): %s\n",
                strerror(errno));
        return 1;
    }

    return 0;
}