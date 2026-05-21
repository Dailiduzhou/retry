#include <bits/stdc++.h>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

typedef struct {
  int xpos;
  int ypos;
} PosType;

typedef struct DQNode {
  PosType seat;
  struct DQNode *next;
  struct DQNode *pre;
} DQNode, *DQueuePtr;

typedef struct {
  DQueuePtr front;
  DQueuePtr rear;
} DLinkQueue;

void InitQueue(DLinkQueue &Q) { Q.front = Q.rear = nullptr; }

void EnQueue(DLinkQueue &Q, PosType e) {
  DQNode *p = new DQNode;
  p->seat.xpos = e.xpos;
  p->seat.ypos = e.ypos;
  p->next = nullptr;
  if (!Q.rear) {
    p->pre = nullptr;
    Q.rear = p;
    Q.front = p;
  } else {
    p->pre = Q.rear;
    Q.rear->next = p;
    Q.rear = p;
  }
}

void GetHead(DLinkQueue Q, PosType &e) {
  e.xpos = Q.front->seat.xpos;
  e.ypos = Q.front->seat.ypos;
}

void DeQueue(DLinkQueue &Q) { Q.front = Q.front->next; }
bool QueueEmpty(const DLinkQueue &Q) { return Q.front == nullptr; }

int n;
int m;
vector<pair<int, int>> dire = {{-1, 1}, {0, 1},   {1, 1},  {-1, 0},
                               {1, 0},  {-1, -1}, {0, -1}, {1, -1}};

bool ShortestPathstd(const vector<vector<int>> &maze, stack<PosType> &pathStack) {
  int n = maze.size();
  int m = maze[0].size();
  if (maze[0][0] == 1) return false; // 起点是墙
  
  vector<vector<bool>> visited(n, vector<bool>(m, false));
  vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1}));
  queue<pair<int, int>> q;
  
  q.push({0, 0});
  visited[0][0] = true;
  parent[0][0] = {-1, -1}; // 起点无父节点
  
  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();
    
    if (x == n - 1 && y == m - 1) {
      // 找到终点，回溯路径
      stack<PosType> reversePath;
      int curX = x, curY = y;
      while (curX != -1 && curY != -1) {
        PosType pos;
        pos.xpos = curX;
        pos.ypos = curY;
        reversePath.push(pos);
        auto [px, py] = parent[curX][curY];
        curX = px;
        curY = py;
      }
      // 将路径按从起点到终点的顺序压入pathStack
      while (!reversePath.empty()) {
        pathStack.push(reversePath.top());
        reversePath.pop();
      }
      return true;
    }
    
    for (const auto &dir : dire) {
      int nx = x + dir.first;
      int ny = y + dir.second;
      if (nx >= 0 && nx < n && ny >= 0 && ny < m && maze[nx][ny] == 0 && !visited[nx][ny]) {
        visited[nx][ny] = true;
        parent[nx][ny] = {x, y};
        q.push({nx, ny});
      }
    }
  }
  return false; // 未找到路径
}
PosType NextPos(const PosType &curpos, int v) {
  PosType next;
  next.xpos = curpos.xpos + dire[v].first;
  next.ypos = curpos.ypos + dire[v].second;
  if (next.xpos < 0 || next.xpos >= n || next.ypos < 0 || next.ypos >= m) {
    return curpos;
  }
  return next;
}

bool ShortestPath(const vector<vector<int>> &maze, stack<PosType> &st) {
  DLinkQueue q;
  int n = maze.size();
  int m = maze[0].size();
  vector<vector<bool>> visited(n, vector<bool>(m, false));
  if (maze[0][0]) {
    return false;
  }
  PosType e;
  e.xpos = 0;
  e.ypos = 0;
  EnQueue(q, e);
  bool found = false;
  PosType curpos, npos;
  while (!found && !QueueEmpty(q)) {
    GetHead(q, curpos);
    for (int v = 0; v < 8 && !found; ++v) {
      npos = NextPos(curpos, v);
      if (!maze[npos.xpos][npos.ypos] && !visited[npos.xpos][npos.ypos]) {
        EnQueue(q, npos);
        visited[npos.xpos][npos.ypos] = true;
      }
      if (npos.xpos == n - 1 && npos.ypos == m - 1) {
        found = true;
      }
    }
  }

  if (found) {
    st = stack<PosType>();
    DQNode *p = q.rear;
    while (p) {
      st.push(p->seat);
      p = p->pre;
    }

    return true;
  } else {
    return false;
  }
}
