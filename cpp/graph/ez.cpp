#include <iostream>
#include <vector>
#include <list>
#include <utility> // for std::pair

using namespace std;

// 定义边的结构：{目标顶点, 权重}
// 也可以用 struct Edge { int to; int weight; }; 来代替 pair
typedef pair<int, int> Edge; 

class GraphAdjList {
private:
    // 核心数据结构：Vector of Lists
    // adj[u] 存储着从 u 出发的所有边
    vector<list<Edge>> adj;
    int numVertices;

public:
    GraphAdjList() {
        numVertices = 0;
    }

    // 1. 动态添加顶点
    // 相比矩阵的 O(V)，邻接表添加顶点非常快，仅需 O(1)
    void addVertex() {
        numVertices++;
        // 在 vector 末尾增加一个空的链表
        adj.push_back(list<Edge>());
        
        cout << "Node " << numVertices - 1 << " added." << endl;
    }

    // 2. 添加有向边
    // u: 起点, v: 终点, w: 权重
    void addEdge(int u, int v, int w = 1) {
        if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
            // 在 u 的链表中添加一个指向 v 的节点
            adj[u].push_back(make_pair(v, w)); 
        } else {
            cerr << "Error: Vertex index out of bounds!" << endl;
        }
    }

    // 3. 删除有向边 (u -> v)
    // 需要遍历链表找到 v，复杂度 O(deg(u))，即 u 的出度
    void removeEdge(int u, int v) {
        if (u < 0 || u >= numVertices) return;

        // 遍历 u 的链表寻找 v
        // 使用迭代器进行遍历和删除
        for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
            if (it->first == v) {
                adj[u].erase(it); // 删除该边
                return; // 有向图通常两点间只有一条边，删完即止
            }
        }
    }

    // 4. 打印邻接表
    void printGraph() {
        cout << "\nAdjacency List Visualization:" << endl;
        for (int i = 0; i < numVertices; ++i) {
            cout << "Vertex " << i << ":";
            
            if (adj[i].empty()) {
                cout << " (isolated)";
            } else {
                for (const auto& edge : adj[i]) {
                    int dest = edge.first;
                    int weight = edge.second;
                    cout << " -> [" << dest << "|w:" << weight << "]";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    // 获取某个点的出度 (Out-degree)
    int getOutDegree(int u) {
        if (u >= 0 && u < numVertices) {
            return adj[u].size();
        }
        return 0;
    }
};

int main() {
    GraphAdjList g;

    // 1. 动态添加顶点
    g.addVertex(); // 0
    g.addVertex(); // 1
    g.addVertex(); // 2

    // 2. 添加边
    // 0 -> 1 (权重 10)
    // 0 -> 2 (权重 5)
    // 2 -> 1 (权重 2)
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 5);
    g.addEdge(2, 1, 2);

    g.printGraph();

    // 3. 动态扩容
    cout << "--- Adding Vertex 3 ---" << endl;
    g.addVertex(); // 3
    g.addEdge(3, 0, 7); // 3 -> 0

    g.printGraph();

    // 4. 删除边测试
    cout << "--- Removing Edge 0->2 ---" << endl;
    g.removeEdge(0, 2);
    g.printGraph();

    return 0;
}