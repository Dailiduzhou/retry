/**
 * Kruskal算法实现最小生成树
 * 时间复杂度: O(E log E) 或 O(E log V)，主要取决于排序
 * 空间复杂度: O(V + E)
 */

#include <algorithm> // 用于 std::sort
#include <iostream>
#include <vector>

using namespace std;

// 定义边的结构体
struct Edge {
    int u, v;   // 连接的两个顶点
    int weight; // 边的权重

    // 重载小于运算符，用于排序
    // const Edge& other 保证不会修改比较对象，const 保证不会修改自身
    bool operator<(const Edge &other) const {
        return weight < other.weight; // 按权重升序排列
    }
};

// 并查集 (DSU - Disjoint Set Union) 结构
struct DSU {
    vector<int> parent;
    vector<int> rank; // 用于按秩合并，优化树的高度

    // 初始化并查集，每个节点的父节点指向自己
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    // 查找节点 x 的根节点 (包含路径压缩优化)
    int find(int x) {
        // 1. 基准情况 (Base Case)：找到根节点了
        if (x == parent[x])
            return x;

        // 2. 递归查找 + 路径压缩 (Recursive Step + Path Compression)
        // 这一行做了两件事：
        // A. find(parent[x]): 继续找我父亲的父亲（递归向上）
        // B. parent[x] = ...: 将递归返回的结果（根节点），直接赋值给我的父节点
        return parent[x] = find(parent[x]);
    }

    // 合并 x 和 y 所在的集合
    // 返回 true 表示合并成功（之前不在同一集合），false 表示已在同一集合
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            // 按秩合并：将高度较小的树挂在高度较大的树下
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
            return true;
        }
        return false;
    }
};

void kruskalMST(int V, vector<Edge> &edges) {
    // 1. 将所有边按权重从小到大排序
    sort(edges.begin(), edges.end());

    DSU dsu(V);            // 初始化并查集，假设顶点编号为 0 到 V-1
    int mstWeight = 0;     // 最小生成树的总权重
    vector<Edge> mstEdges; // 存储被选中的边

    cout << "Kruskal算法构建MST过程:" << endl;

    // 2. 遍历每一条边
    for (const auto &edge : edges) {
        // 3. 判断加入该边是否会形成环 (即两个顶点是否已经连通)
        if (dsu.unite(edge.u, edge.v)) {
            mstWeight += edge.weight;
            mstEdges.push_back(edge);
            cout << "选边: " << edge.u << " - " << edge.v
                 << " (权重: " << edge.weight << ")" << endl;
        }
    }

    // 输出结果
    if (mstEdges.size() != V - 1) {
        cout << "图不连通，无法生成完整的MST。" << endl;
    } else {
        cout << "最小生成树总权重: " << mstWeight << endl;
    }
}

int main() {
    // 示例数据
    // 顶点数 4, 边列表
    int V = 4;
    vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}};

    kruskalMST(V, edges);

    return 0;
}