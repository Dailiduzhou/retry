#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/**
 * 使用 std::vector 和 std::queue 实现的冲突图分组算法
 * @param R 冲突关系矩阵，R[i][j] = 1 表示 i 和 j 有冲突
 * @param n 元素个数
 * @return 返回每个元素所属的分组编号（从1开始）
 */
vector<int> divisionVector(const vector<vector<int>> &R, int n) {
  int pre = n;
  int group = 0;

  // 使用 std::queue 替代 SqQueue
  queue<int> Q;

  // 初始化队列，将所有元素入队
  for (int e = 0; e < n; ++e) {
    Q.push(e);
  }

  // 使用 std::vector 替代数组
  vector<int> clash(n, 0);
  vector<int> result(n, 0);

  int i = -1;

  while (!Q.empty()) {
    i = Q.front();
    Q.pop();

    // 如果当前元素比之前的小，说明开始新的一组
    if (i < pre) {
      group++;
      // 重置冲突标记
      fill(clash.begin(), clash.end(), 0);
    }

    // 如果当前元素没有冲突，可以加入当前组
    if (clash[i] == 0) {
      result[i] = group;
      // 将当前元素的所有冲突标记
      for (int j = 0; j < n; ++j) {
        clash[j] += R[i][j];
      }
    } else {
      // 有冲突，重新入队等待下一组
      Q.push(i);
    }
    pre = i;
  }

  return result;
}

/**
 * 打印分组结果
 */
void printGroupsVector(const vector<int> &result, int n, int groupCount) {
  for (int g = 1; g <= groupCount; ++g) {
    cout << "Group " << g << ": ";

    vector<int> groupMembers;
    for (int i = 0; i < n; ++i) {
      if (result[i] == g) {
        groupMembers.push_back(i);
      }
    }

    // 打印组成员
    for (size_t i = 0; i < groupMembers.size(); ++i) {
      if (i > 0)
        cout << " -> ";
      cout << groupMembers[i];
    }
    cout << endl;
  }
}

int main() {
  const int n = 6;

  // 使用 std::vector 替代数组
  vector<vector<int>> R(n, vector<int>(n, 0));

  // 冲突关系: 0-1, 0-3, 1-2, 1-4, 2-5, 3-4, 4-5
  R[0][1] = 1;
  R[1][0] = 1;
  R[0][3] = 1;
  R[3][0] = 1;
  R[1][2] = 1;
  R[2][1] = 1;
  R[1][4] = 1;
  R[4][1] = 1;
  R[2][5] = 1;
  R[5][2] = 1;
  R[3][4] = 1;
  R[4][3] = 1;
  R[4][5] = 1;
  R[5][4] = 1;

  cout << "Conflict Matrix (using vector):" << endl;
  cout << "  0 1 2 3 4 5" << endl;
  for (int i = 0; i < n; ++i) {
    cout << i << " ";
    for (int j = 0; j < n; ++j) {
      cout << R[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;

  // 调用 vector 版本的 division 函数
  vector<int> result = divisionVector(R, n);

  // 计算最大组数
  int maxGroup = 0;
  for (int i = 0; i < n; ++i) {
    if (result[i] > maxGroup) {
      maxGroup = result[i];
    }
  }

  cout << "Division Result (using vector): ";
  for (int i = 0; i < n; ++i) {
    cout << "[" << i << "]=" << result[i] << " ";
  }
  cout << endl << endl;

  cout << "Groups:" << endl;
  printGroupsVector(result, n, maxGroup);

  return 0;
}
