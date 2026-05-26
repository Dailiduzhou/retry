#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;

void printMatrix(const vector<vector<int>> &matrix) {
  int V = matrix.size();
  for (int i = 0; i < V; ++i) {
    for (int j = 0; j < V; ++j) {
      if (matrix[i][j] == INF) {
        cout << setw(5) << "INF";
      } else {
        cout << setw(5) << matrix[i][j];
      }
    }
    cout << endl;
  }
}

// Floyd-Warshall 算法核心函数
void floydWarshall(vector<vector<int>> &graph) {
  int V = graph.size();

  // 初始化距离矩阵 dist，初始状态与邻接矩阵相同
  vector<vector<int>> dist = graph;

  // 核心的三重循环
  // k 必须在最外层，表示依次将每个节点作为中转站
  for (int k = 0; k < V; ++k) {
    for (int i = 0; i < V; ++i) {
      for (int j = 0; j < V; ++j) {
        // 如果经过中转站 k 的路径是连通的，并且能使距离变得更短，则更新距离
        if (dist[i][k] != INF && dist[k][j] != INF &&
            dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }

  // 检查是否存在负权环
  // 如果一个顶点到它自身的距离变成了负数，说明图中存在负权环
  for (int i = 0; i < V; ++i) {
    if (dist[i][i] < 0) {
      cout << "警告: 图中存在负权环！最短路径无意义。" << endl;
      return;
    }
  }

  cout << "最终的任意两点间的最短距离矩阵:" << endl;
  printMatrix(dist);
}

int main() {
  /*
      构建一个简单的测试图 (包含4个顶点)
      (0)---3--->(1)
       ^          |
       |          | 2
       5          V
      (3)<---1---(2)
  */
  int V = 4;
  vector<vector<int>> graph = {
      {0, 3, INF, 5}, {2, 0, INF, 4}, {INF, 1, 0, INF}, {INF, INF, 2, 0}};

  // 执行算法
  floydWarshall(graph);

  return 0;
}
