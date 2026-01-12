#include <stdio.h>

int pos[10];
int path[10];
void find(int u) {
    if (u > 3) { // 终止条件
        for (int i = 1; i <= 3; ++i) {
            printf("%d", path[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 7; i <= 9; i++) { // 轮流填入数字
        if (!pos[i]) {             // 判断数字是否已使用
            path[u] = i;
            pos[i] = 1;
            find(u + 1);
            pos[i] = 0; // 回溯，保证排列完整性
        }
    }
}

int main() {
    find(1); // <---从第一个数字开始
    return 0;
}
