#include<bits/stdc++.h>
using namespace std;

const int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
const int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

bool a[21][21] = {false};
long long b[21][21] = {0};

long long dfs(int o, int p, int x, int y) {
    if (o == x && p == y) return 1;
    if (b[o][p]) return b[o][p]; // 使用缓存结果
    
    long long current = 0;
    
    // 向右移动
    if (o < x && !a[o+1][p]) {
        current += dfs(o+1, p, x, y);
    }
    
    // 向下移动
    if (p < y && !a[o][p+1]) {
        current += dfs(o, p+1, x, y);
    }
    
    b[o][p] = current; // 缓存当前节点结果
    return current;
}

int main() {
    int x, y, m, n;
    scanf("%d%d%d%d", &x, &y, &m, &n);
    
    // 标记马的控制点
    a[m][n] = true;
    for (int i = 0; i < 8; i++) {
        int nx = m + dx[i];
        int ny = n + dy[i];
        if (nx >= 0 && nx <= 20 && ny >= 0 && ny <= 20) {
            a[nx][ny] = true;
        }
    }
    
    // 检查起点是否被马阻挡
    if (a[0][0]) {
        cout << 0;
        return 0;
    }
    
    cout << dfs(0, 0, x, y);
    return 0;
}