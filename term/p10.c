// 需求：目的文件名在前，源文件名在后，将源文件内容追加到目的文件末尾。
// 用法示例：./p10 dest.txt src.txt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "用法: %s <目的文件> <源文件>\n", argv[0]);
        return 1;
    }

    const char *destPath = argv[1];
    const char *srcPath  = argv[2];

    if (strcmp(destPath, srcPath) == 0) {
        fprintf(stderr, "错误: 目的文件与源文件相同，拒绝操作。\n");
        return 1;
    }

    FILE *src = fopen(srcPath, "rb");
    if (!src) {
        fprintf(stderr, "无法打开源文件(只读): %s: %s\n", srcPath, strerror(errno));
        return 1;
    }

    FILE *dst = fopen(destPath, "ab");
    if (!dst) {
        int e = errno;
        fclose(src);
        fprintf(stderr, "无法以追加方式打开目的文件: %s: %s\n", destPath, strerror(e));
        return 1;
    }

    char buffer[8192];
    size_t nread;
    while ((nread = fread(buffer, 1, sizeof buffer, src)) > 0) {
        size_t nwritten = fwrite(buffer, 1, nread, dst);
        if (nwritten != nread) {
            int e = ferror(dst) ? errno : 0;
            fprintf(stderr, "写入目的文件失败: %s%s%s\n", destPath, e ? ": " : "", e ? strerror(e) : "");
            fclose(src);
            fclose(dst);
            return 1;
        }
    }

    if (ferror(src)) {
        int e = errno;
        fprintf(stderr, "读取源文件失败: %s: %s\n", srcPath, strerror(e));
        fclose(src);
        fclose(dst);
        return 1;
    }

    if (fclose(src) != 0) {
        fprintf(stderr, "关闭源文件失败: %s: %s\n", srcPath, strerror(errno));
        // 继续尝试关闭目的文件
    }

    if (fclose(dst) != 0) {
        fprintf(stderr, "关闭目的文件失败: %s: %s\n", destPath, strerror(errno));
        return 1;
    }

    return 0;
}
