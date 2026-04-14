# 十字链表（Cross Linked List）数据结构详解

## 目录
- [一、数据结构概述](#一数据结构概述)
- [二、核心结构详解](#二核心结构详解)
- [三、搜索算法实现](#三搜索算法实现)
- [四、测试框架详解](#四测试框架详解)
- [五、Timeout机制原理](#五timeout机制原理)

---

## 一、数据结构概述

### 1.1 什么是十字链表？

**十字链表（Orthogonal List）** 是一种用于存储**稀疏矩阵（Sparse Matrix）**的高效数据结构。

**稀疏矩阵的特点**：
- 矩阵中绝大多数元素为 0
- 非零元素数量远小于总元素数量
- 直接存储整个矩阵会浪费大量空间

**十字链表的优势**：
- 只存储非零元素，节省空间
- 支持快速的行遍历和列遍历
- 插入和删除操作灵活

### 1.2 直观理解

想象一个 3×3 的稀疏矩阵：

```
[ 0  5  0 ]
[ 0  0  7 ]
[ 3  0  0 ]
```

十字链表只存储三个非零元素：`(0,1)=5`, `(1,2)=7`, `(2,0)=3`

每个节点同时属于：
- **行链表**：同一行中的所有非零元素
- **列链表**：同一列中的所有非零元素

---

## 二、核心结构详解

### 2.1 节点结构 `OLNode`

```cpp
typedef struct OLNode {
  int i, j;              // 行号和列号（位置信息）
  ElemType e;            // 元素值
  struct OLNode *rnext;  // 行指针：指向同一行中的下一个非零元素
  struct OLNode *cnext;  // 列指针：指向同一列中的下一个非零元素
} OLNode, *OLink;
```

**关键特性**：
- 每个节点同时处于两条链表中
- `rnext` 连接同一行的元素（按列号有序）
- `cnext` 连接同一列的元素（按行号有序）

### 2.2 矩阵结构 `CrossList`

```cpp
typedef struct {
  OLink *rhead;  // 行头指针数组：rhead[i] 指向第 i 行的第一个节点
  OLink *chead;  // 列头指针数组：chead[j] 指向第 j 列的第一个节点
  int m, n, t;   // m: 行数, n: 列数, t: 非零元素个数
} CrossList;
```

**内存布局示意**：

```
        列头指针数组
        chead[0]  chead[1]  chead[2]
            │         │         │
            ▼         ▼         ▼
           [3]──cnext──►[5]──cnext──►[7]
            │         │         │
           rnext     rnext     rnext
            │         │         │
            ▼         ▼         ▼
           NULL      NULL      NULL

行头指针数组
rhead[0] ──► [5]──rnext──► NULL
rhead[1] ──► [7]──rnext──► NULL  
rhead[2] ──► [3]──rnext──► NULL
```

### 2.3 节点插入操作 `AddNode`

```cpp
static void AddNode(CrossList &M, int i, int j, ElemType e) {
  OLink node = new OLNode{i, j, e, nullptr, nullptr};

  // 1. 插入行链表（按列号升序）
  if (!M.rhead[i] || M.rhead[i]->j > j) {
    // 插入到行头
    node->rnext = M.rhead[i];
    M.rhead[i] = node;
  } else {
    // 查找插入位置
    OLink p = M.rhead[i];
    while (p->rnext && p->rnext->j < j) {
      p = p->rnext;
    }
    node->rnext = p->rnext;
    p->rnext = node;
  }

  // 2. 插入列链表（按行号升序）
  if (!M.chead[j] || M.chead[j]->i > i) {
    // 插入到列头
    node->cnext = M.chead[j];
    M.chead[j] = node;
  } else {
    // 查找插入位置
    OLink p = M.chead[j];
    while (p->cnext && p->cnext->i < i) {
      p = p->cnext;
    }
    node->cnext = p->cnext;
    p->cnext = node;
  }

  M.t++;  // 非零元素计数+1
}
```

**插入过程图解**：

假设要在位置 `(1, 1)` 插入元素 `5`：

```
插入前：
  第1行: [0,0]=1 ──rnext──► NULL
  第1列: [0,1]=2 ──cnext──► NULL

插入 [1,1]=5 后：
  第1行: [0,0]=1 ──rnext──► [1,1]=5 ──rnext──► NULL
  第1列: [0,1]=2 ──cnext──► [1,1]=5 ──cnext──► NULL
```

---

## 三、搜索算法实现

### 3.1 正确实现

```cpp
void CrossSearch(CrossList &M, ElemType x) {
  // 遍历每一行
  for (int i = 0; i < M.m; i++) {
    OLNode *p = *(M.rhead + i);  // 获取第 i 行的头节点
    
    // 遍历当前行的所有非零元素
    while (p) {
      if (p->e == x) {
        // 找到匹配元素，输出位置
        std::cout << '(' << p->i << ',' << p->j << ')' << std::endl;
      }
      p = p->rnext;  // 移动到行中的下一个元素
    }
  }
}
```

### 3.2 原代码的 Bug 分析

**错误的原始代码**：

```cpp
void CrossSearch(CrossList &M, ElemType x) {
  int i = 0;
  OLNode *p = *(M.rhead + i);
  while (i < M.m) {
    if (!p) {
      i++;
      p = *(M.rhead + i);  // 当前行遍历完毕，进入下一行
    } else {
      if (p->e == x) {
        std::cout << '(' << p->i << ',' << p->j << ')' << std::endl;
        p = p->rnext;      // 仅当找到匹配时才移动指针
      }
      // BUG: 当 p->e != x 时，指针没有移动，陷入死循环！
    }
  }
}
```

**问题分析**：

| 场景 | 行为 | 结果 |
|------|------|------|
| `p == nullptr` | 进入下一行 | ✅ 正确 |
| `p->e == x` | 输出并移动指针 | ✅ 正确 |
| `p->e != x` | 无任何操作 | ❌ 死循环！|

**修正方案**：
- 使用 `for` 循环明确遍历每一行
- 无论是否找到匹配，都要移动指针 `p = p->rnext`
- 简化逻辑，提高可读性

### 3.3 搜索过程示例

在以下矩阵中搜索值为 `5` 的元素：

```
[ 0  5  0 ]
[ 0  0  0 ]
[ 0  5  0 ]
```

搜索步骤：
1. 第 0 行：`[0,1]=5` ✓ 匹配，输出 `(0,1)`，指针移向 `NULL`
2. 第 1 行：空行，跳过
3. 第 2 行：`[2,1]=5` ✓ 匹配，输出 `(2,1)`，指针移向 `NULL`
4. 结束

**输出**：
```
(0,1)
(2,1)
```

---

## 四、测试框架详解

### 4.1 测试框架设计目标

1. **隔离性**：被测代码崩溃不影响测试框架
2. **超时检测**：检测无限循环等性能问题
3. **输出验证**：验证函数输出的正确性
4. **资源清理**：确保内存和进程资源被正确释放

### 4.2 核心结构

```cpp
enum class MatrixCase {
  AllMatch,       // 所有元素都匹配目标值
  DistinctValues, // 元素值各不相同
};

struct RunResult {
  bool timed_out = false;    // 是否超时
  int exit_code = -1;        // 子进程退出码
  int term_signal = 0;       // 终止信号
  std::string output;        // 子进程输出
};
```

### 4.3 测试用例构建

```cpp
static CrossList BuildMatrix(MatrixCase which) {
  CrossList M{};
  M.m = 2;  M.n = 2;  M.t = 0;
  M.rhead = new OLink[M.m]();  // 初始化为 nullptr
  M.chead = new OLink[M.n]();  // 初始化为 nullptr

  if (which == MatrixCase::AllMatch) {
    AddNode(M, 0, 0, 5);  // 元素值为 5
    AddNode(M, 1, 1, 5);  // 元素值为 5
  } else {
    AddNode(M, 0, 0, 1);  // 元素值为 1
    AddNode(M, 1, 1, 2);  // 元素值为 2
  }
  return M;
}
```

**生成的矩阵**：

- `AllMatch`:
  ```
  [ 5  0 ]
  [ 0  5 ]
  ```
  搜索 `5` 应该输出 `(0,0)` 和 `(1,1)`

- `DistinctValues`:
  ```
  [ 1  0 ]
  [ 0  2 ]
  ```
  搜索 `42` 应该没有输出

### 4.4 多进程测试机制

```cpp
static RunResult RunCrossSearchInChild(MatrixCase which, ElemType target, int timeout_ms) {
  RunResult result;
  
  // 1. 创建管道用于父子进程通信
  int pipe_fd[2];
  pipe(pipe_fd);  // pipe_fd[0] 读端, pipe_fd[1] 写端
  
  // 2. 创建子进程
  pid_t pid = fork();
  
  if (pid == 0) {
    // ========== 子进程 ==========
    close(pipe_fd[0]);                    // 关闭读端
    dup2(pipe_fd[1], STDOUT_FILENO);      // 重定向 stdout 到管道
    close(pipe_fd[1]);                    // 关闭原写端
    
    CrossList M = BuildMatrix(which);     // 构建测试矩阵
    CrossSearch(M, target);               // 执行被测函数
    DestroyMatrix(M);                     // 清理内存
    _exit(0);                             // 子进程退出
    // ==========================
  }
  
  // 3. 父进程监控子进程
  close(pipe_fd[1]);  // 关闭写端
  
  // ... Timeout 检测逻辑 ...
  
  // 4. 读取子进程输出
  char buf[256];
  while (read(pipe_fd[0], buf, sizeof(buf)) > 0) {
    result.output.append(buf, n);
  }
  close(pipe_fd[0]);
  
  return result;
}
```

---

## 五、Timeout机制原理

### 5.1 为什么需要 Timeout？

考虑以下场景：
- 被测函数存在**死循环** Bug
- 被测函数**运行时间过长**（算法复杂度高）
- 被测函数**死锁**或等待不可用的资源

没有 Timeout 机制时：
- 测试框架会**永远挂起**
- 无法得到任何反馈
- CI/CD 流程会被阻塞

### 5.2 实现原理

```cpp
static RunResult RunCrossSearchInChild(...) {
  // ... fork 创建子进程 ...
  
  int status = 0;
  bool child_done = false;
  
  // 计算截止时间
  auto deadline = std::chrono::steady_clock::now() 
                + std::chrono::milliseconds(timeout_ms);
  
  // 轮询检查子进程状态
  while (std::chrono::steady_clock::now() < deadline) {
    pid_t waited = waitpid(pid, &status, WNOHANG);  // 非阻塞等待
    
    if (waited == pid) {
      child_done = true;    // 子进程已完成
      break;
    }
    if (waited < 0) {
      child_done = true;    // 发生错误
      break;
    }
    
    // 等待 10ms 后再次检查
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  
  // 超时处理
  if (!child_done) {
    result.timed_out = true;      // 标记超时
    kill(pid, SIGKILL);           // 发送强制终止信号
    waitpid(pid, &status, 0);     // 等待子进程结束
  }
  
  // ... 收集结果 ...
}
```

### 5.3 关键函数解释

| 函数 | 作用 |
|------|------|
| `fork()` | 创建子进程，返回 0 表示子进程，>0 表示父进程得到子进程 PID |
| `waitpid(pid, &status, WNOHANG)` | 非阻塞等待子进程，立即返回状态 |
| `kill(pid, SIGKILL)` | 向进程发送 SIGKILL 信号（强制终止） |
| `WIFEXITED(status)` | 检查进程是否正常退出 |
| `WIFSIGNALED(status)` | 检查进程是否被信号终止 |
| `WEXITSTATUS(status)` | 获取进程退出码 |
| `WTERMSIG(status)` | 获取导致终止的信号编号 |

### 5.4 执行流程图

```
父进程                              子进程
  │                                   │
  ├────────── fork() ───────────────►│
  │                                   │
  │                                   ├── BuildMatrix()
  │                                   │
  │                                   ├── CrossSearch()
  │                                   │   (可能死循环!)
  │                                   │
  │◄───────────────┬─────────────────┤
  │                │                 │
  │    轮询检查    │                 │
  │   waitpid()    │                 │
  │                │                 │
  │  超时? ──是──► kill(SIGKILL) ───►│  强制终止
  │                │                 │
  │  完成? ──是──► 收集结果          │
  │                │                 │
  │◄───────────────┘                 │
  │                                   │
  ▼                                   ▼
```

### 5.5 测试验证

```cpp
static bool TestFoundValueShouldReturnAndPrintPositions() {
  // 搜索存在的值，超时时间 500ms
  RunResult res = RunCrossSearchInChild(MatrixCase::AllMatch, 5, 500);
  
  // 验证：不超时
  if (res.timed_out) {
    std::cerr << "timeout: search for existing value did not return\n";
    return false;
  }
  
  // 验证：正常退出
  if (res.exit_code != 0) {
    std::cerr << "exit_code: expected 0, got " << res.exit_code << '\n';
    return false;
  }
  
  // 验证：输出正确
  if (res.output.find("(0,0)") == std::string::npos ||
      res.output.find("(1,1)") == std::string::npos) {
    std::cerr << "output mismatch: expected to contain (0,0) and (1,1)\n";
    return false;
  }
  
  return true;
}
```

---

## 六、总结

### 6.1 知识点回顾

| 知识点 | 说明 |
|--------|------|
| 十字链表 | 稀疏矩阵的高效存储结构，每个节点同时在行链表和列链表中 |
| 多进程测试 | 使用 `fork()` 隔离被测代码，保护测试框架 |
| Timeout 机制 | 防止死循环导致测试挂起，确保测试可控 |
| 管道通信 | `pipe()` + `dup2()` 实现父子进程间的输出捕获 |

### 6.2 代码结构

```
xll.h           # 数据结构定义
xl.cpp          # 十字链表搜索算法实现
xl_test.cpp     # 多进程测试框架
```

### 6.3 编译运行

```bash
# 编译
g++ -o xl_test xl_test.cpp xl.cpp -std=c++11 -pthread

# 运行测试
./xl_test
```

**预期输出**：
```
[TEST] Search existing value
  -> PASSED
[TEST] Search missing value
  -> PASSED

All tests passed.
```

---

*文档生成时间：2026年4月14日*
