// 需求：目的文件名在前，源文件名在后，将源文件内容追加到目的文件末尾。
// 用法示例：./p10 dest.txt src.txt

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    // 检查参数：程序名 + 目的文件 + 源文件
    if (argc != 3) {
        std::cerr << "用法: " << argv[0] << " <目的文件> <源文件>\n";
        return 1;
    }

    const std::string destPath = argv[1];
    const std::string srcPath = argv[2];

    if (destPath == srcPath) {
        std::cerr << "错误: 目的文件与源文件相同，拒绝操作。\n";
        return 1;
    }

    // 只读方式打开源文件（二进制，跨平台不改变内容）
    std::ifstream src(srcPath, std::ios::in | std::ios::binary);
    if (!src) {
        std::cerr << "无法打开源文件(只读): " << srcPath << "\n";
        return 1;
    }

    // 追加方式打开目的文件（若不存在则创建）
    std::ofstream dst(destPath,
                      std::ios::out | std::ios::app | std::ios::binary);
    if (!dst) {
        std::cerr << "无法以追加方式打开目的文件: " << destPath << "\n";
        return 1;
    }

    // 高效复制：将源文件缓冲区直接插入到目的文件
    dst << src.rdbuf();

    if (!dst) {
        std::cerr << "写入目的文件失败: " << destPath << "\n";
        return 1;
    }

    return 0;
}
