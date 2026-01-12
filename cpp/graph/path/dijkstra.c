/**
 * Dijkstra最短路径算法 (C语言 - 邻接矩阵版)
 * 时间复杂度: O(V^2)
 * 空间复杂度: O(V^2)
 */

#include <limits.h>  // 用于使用 INT_MAX
#include <stdbool.h> // 用于使用 bool, true, false
#include <stdio.h>

// 定义图的顶点数量 (这里固定为9个，可根据需求修改)
#define V 9

/**
 * 辅助函数: 找到距离最小的节点
 * 在 dist[] 中查找尚未包含在最短路径树(sptSet)中的、距离起点最近的顶点
 */
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX;
    int min_index;

    for (int v = 0; v < V; v++) {
        // 1. sptSet[v] == false: 必须是未处理过的点
        // 2. dist[v] <= min: 找当前的最小值
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

/**
 * 辅助函数: 打印结果
 */
void printSolution(int dist[]) {
    printf("顶点 \t\t 距离起点的最短距离\n");
    printf("--------------------------------\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

/**
 * Dijkstra 算法主体
 * graph[V][V]: 邻接矩阵，graph[i][j] 表示 i 到 j 的权重，0 表示不相连
 * src: 起点 (Source)
 */
void dijkstra(int graph[V][V], int src) {

    // dist[i] 保存从 src 到 i 的最短距离
    int dist[V];

    // sptSet[i] (Shortest Path Tree Set)
    // 如果为 true，表示顶点 i 的最短路径已经确定，归入集合
    bool sptSet[V];

    // 1. 初始化
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX; // 初始距离都是无穷大
        sptSet[i] = false; // 所有点都未被处理
    }

    // 起点到自己的距离总是 0
    dist[src] = 0;

    // 2. 迭代寻找所有顶点的最短路径
    // 只需要循环 V-1 次，因为最后一个点会自动确定的
    for (int count = 0; count < V - 1; count++) {

        // 步骤 A: 贪心选择
        // 从未处理的顶点集合中，选出距离 src 最近的顶点 u
        int u = minDistance(dist, sptSet);

        // 将 u 标记为已处理 (加入最短路径树)
        sptSet[u] = true;

        // 步骤 B: 松弛操作 (Relaxation)
        // 更新 u 的所有邻接点 v 的距离
        for (int v = 0; v < V; v++) {
            // 更新条件需要同时满足 4 点:
            // 1. !sptSet[v]: v 还没有被处理过
            // 2. graph[u][v]: u 和 v 之间有边 (权重不为0)
            // 3. dist[u] != INT_MAX: u 本身是可达的 (防止溢出)
            // 4. dist[u] + graph[u][v] < dist[v]: 经过 u 到 v 比原来的路径更短
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {

                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // 打印计算出的最短距离数组
    printSolution(dist);
}

int main() {
    /* 创建一个示例图的邻接矩阵
       例如: graph[0][1] = 4 表示 0 到 1 的距离是 4
       0 表示两个节点不直接相连 (或者是自身)
    */
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},  {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},  {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0}, {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},  {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}};

    printf("Dijkstra算法计算结果 (起点为 0):\n");
    dijkstra(graph, 0);

    return 0;
}