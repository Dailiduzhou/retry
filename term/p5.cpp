#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 8

int count = 0; // 解法计数器

// 打印棋盘
void printBoard(int board[N]) {
    count++;
    printf("解法 %d:\n", count);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i] == j)
                printf(" Q ");
            else
                printf(" . ");
        }
        printf("\n");
    }
    printf("\n");
}

// 检查当前位置是否安全
int isSafe(int board[N], int row, int col) {
    for (int i = 0; i < row; i++) {
        // 检查同一列或对角线
        if (board[i] == col || abs(board[i] - col) == abs(i - row)) {
            return 0;
        }
    }
    return 1;
}

// 递归放置皇后
void placeQueen(int board[N], int row) {
    if (row == N) {
        printBoard(board);
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col;           // 在第row行第col列放置皇后
            placeQueen(board, row + 1); // 放置下一行的皇后
        }
    }
}

int main() {
    int board[N]; // board[i]表示第i行皇后所在的列

    printf("八皇后问题解法（一维数组优化）:\n");
    printf("==============================\n\n");

    placeQueen(board, 0);

    printf("总共有 %d 种解法\n", count);

    return 0;
}