#include <algorithm>
#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

namespace {

// 模拟的内存按字节编址, 地址从 0 开始; 一个分区用 (起始地址, 分区大小) 表示,
// 即占用地址区间 [start, start + size)
constexpr int kMaxAddress = 1 << 30; // 地址上限, 避免输入过大导致溢出

// 一个空闲分区的输入数据
struct FreeBlock {
  int start = 0; // 起始地址
  int size = 0;  // 分区大小
};

// 一个进程的分区请求
struct Request {
  std::string name;  // 进程名, 形如 P1
  int need_size = 0; // 请求的分区大小
};

// 一条请求的分配结果
struct Allocation {
  std::string name;
  int need_size = 0; // 请求的分区大小
  int start = -1;    // 分配到的起始地址, -1 表示分配失败
  int size = 0;      // 实际占用的分区大小(等于请求大小)
  bool success = false;
};

// 一条请求处理完之后的状态, 用于逐步输出空闲分区队列
struct Step {
  Allocation allocation;
  std::vector<FreeBlock> free_blocks; // 处理完该请求后的空闲分区队列
};

// 一次模拟的结果: 最终空闲分区队列 + 按请求顺序排列的各步状态
struct SimulationResult {
  std::vector<FreeBlock> free_blocks; // 最终空闲分区队列(按起始地址排序)
  std::vector<Step> steps;            // 与请求序列一一对应
};

// 分配算法, 取值与菜单编号一致; enum class 不会隐式转换成 int
enum class Algorithm { FIRST_FIT = 1, BEST_FIT = 2, WORST_FIT = 3 };

const char *nameOf(Algorithm algorithm) {
  switch (algorithm) {
  case Algorithm::FIRST_FIT:
    return "首次适应算法 (FIRST FIT)";
  case Algorithm::BEST_FIT:
    return "最佳适应算法 (BEST FIT)";
  case Algorithm::WORST_FIT:
    return "最坏适应算法 (WORST FIT)";
  }
  return "未知算法";
}

// 空闲分区队列按起始地址递增排列: 首次适应算法即从低地址端开始扫描
void sortByAddress(std::vector<FreeBlock> &blocks) {
  std::sort(blocks.begin(), blocks.end(),
            [](const FreeBlock &lhs, const FreeBlock &rhs) {
              return lhs.start < rhs.start;
            });
}

// 按算法从空闲分区队列中挑出一个能容纳 need 的分区, 返回其下标
// 三种算法共用同一套扫描代码, 只是"挑哪个"的规则不同
bool selectBlock(const std::vector<FreeBlock> &blocks, int need,
                 Algorithm algorithm, std::size_t &index) {
  index = blocks.size(); // 用队列长度表示"还没有选中任何分区"
  for (std::size_t i = 0; i < blocks.size(); ++i) {
    if (blocks[i].size < need) {
      continue; // 装不下, 直接跳过
    }
    switch (algorithm) {
    case Algorithm::FIRST_FIT: // 首次适应: 第一个够大的分区, 立即返回
      index = i;
      return true;
    case Algorithm::BEST_FIT: // 最佳适应: 保留够用且最小的分区
      if (index == blocks.size() || blocks[i].size < blocks[index].size) {
        index = i;
      }
      break;
    case Algorithm::WORST_FIT: // 最坏适应: 保留够用且最大的分区
      if (index == blocks.size() || blocks[i].size > blocks[index].size) {
        index = i;
      }
      break;
    }
  }
  return index != blocks.size();
}

// 判断 [start, start + size) 是否与已有的空闲分区重叠
bool overlaps(const std::vector<FreeBlock> &blocks, int start, int size) {
  for (const auto &block : blocks) {
    if (start < block.start + block.size && block.start < start + size) {
      return true;
    }
  }
  return false;
}

// 模拟分区式存储管理: 按请求序列依次分配, 每条请求都从低地址端切分空闲分区
SimulationResult simulate(const std::vector<FreeBlock> &initial_blocks,
                          const std::vector<Request> &requests,
                          Algorithm algorithm) {
  SimulationResult result;
  result.free_blocks = initial_blocks;
  sortByAddress(result.free_blocks);
  result.steps.reserve(requests.size());

  for (const auto &request : requests) {
    // 1) 按算法挑选一个能容纳请求的空闲分区
    std::size_t index = result.free_blocks.size();
    const bool found =
        selectBlock(result.free_blocks, request.need_size, algorithm, index);

    // 2) 分配: 从选中分区的低地址端切出请求大小, 剩余部分继续留在空闲队列中
    Allocation allocation;
    allocation.name = request.name;
    allocation.need_size = request.need_size;
    if (found) {
      FreeBlock &block = result.free_blocks[index];
      allocation.start = block.start;
      allocation.size = request.need_size;
      allocation.success = true;
      if (block.size == request.need_size) {
        // 恰好用完, 整个分区从空闲队列中删除
        result.free_blocks.erase(result.free_blocks.begin() + index);
      } else {
        block.start += request.need_size;
        block.size -= request.need_size;
      }
    }

    // 3) 记录本步结果; 分配失败时该进程不占内存, 空闲队列保持不变
    result.steps.emplace_back(Step{allocation, result.free_blocks});
  }
  return result;
}

// 打印空闲分区队列, 形如 (0, 100) -> (200, 150), 括号内依次为起始地址和分区大小
void printFreeBlocks(const std::vector<FreeBlock> &blocks) {
  if (blocks.empty()) {
    std::cout << "(无空闲分区)";
    return;
  }
  for (std::size_t i = 0; i < blocks.size(); ++i) {
    std::cout << "(" << blocks[i].start << ", " << blocks[i].size << ")";
    if (i + 1 < blocks.size()) {
      std::cout << " -> ";
    }
  }
}

// 打印读入的输入数据: 空闲分区表 + 请求序列
void printInput(const std::vector<FreeBlock> &free_blocks,
                const std::vector<Request> &requests) {
  std::cout << "起始地址\t分区大小\n";
  for (const auto &block : free_blocks) {
    std::cout << block.start << "\t" << block.size << "\n";
  }
  std::cout << "进程请求序列: ";
  for (std::size_t i = 0; i < requests.size(); ++i) {
    std::cout << requests[i].name << "(" << requests[i].need_size << ")";
    if (i + 1 < requests.size()) {
      std::cout << " ";
    }
  }
  std::cout << "\n";
}

// 输出某个算法的模拟过程: 逐步的空闲分区队列 + 分配结果表 + 最终空闲队列
void printSimulation(const std::vector<FreeBlock> &initial_blocks,
                     const std::vector<Request> &requests,
                     Algorithm algorithm) {
  const SimulationResult result = simulate(initial_blocks, requests, algorithm);

  std::cout << "\n---------- " << nameOf(algorithm) << " ----------\n";
  std::cout << "初始空闲分区队列: ";
  printFreeBlocks(initial_blocks);
  std::cout << "\n\n";

  // 逐条请求输出: 请求信息 + 分配位置 + 分配后的空闲分区队列
  std::size_t order = 0;
  for (const auto &step : result.steps) {
    ++order;
    const Allocation &allocation = step.allocation;
    // 第 n 个请求: 进程: xxx, 请求大小: xxx, 起始地址: xxx, 空闲分区队列: ...
    std::cout << "第 " << order << " 个请求: 进程: " << allocation.name
              << ", 请求大小: " << allocation.need_size;
    if (allocation.success) {
      std::cout << ", 起始地址: " << allocation.start
                << ", 占用大小: " << allocation.size << ", 状态: 已分配";
    } else {
      std::cout << ", 状态: 分配失败 (没有足够大的空闲分区)";
    }
    std::cout << "\n    分配后空闲分区队列: ";
    printFreeBlocks(step.free_blocks);
    std::cout << "\n";
  }

  // 分配结果表: 每行一条请求, 失败的请求用 '-' 占位
  std::cout << "\n分配结果:\n";
  std::cout << "进程\t请求大小\t起始地址\t占用大小\t状态\n";
  for (const auto &step : result.steps) {
    const Allocation &allocation = step.allocation;
    std::cout << allocation.name << "\t" << allocation.need_size << "\t";
    if (allocation.success) {
      std::cout << allocation.start << "\t" << allocation.size << "\t已分配\n";
    } else {
      std::cout << "-\t-\t分配失败\n";
    }
  }

  // 统计: 成功条数、总占用空间、剩余空闲空间及最大空闲分区
  const int requested = static_cast<int>(result.steps.size());
  const int success_count = static_cast<int>(
      std::count_if(result.steps.begin(), result.steps.end(),
                    [](const Step &step) { return step.allocation.success; }));
  const int allocated_size = std::accumulate(
      result.steps.begin(), result.steps.end(), 0,
      [](int sum, const Step &step) {
        return sum + (step.allocation.success ? step.allocation.size : 0);
      });
  const int free_size = std::accumulate(
      result.free_blocks.begin(), result.free_blocks.end(), 0,
      [](int sum, const FreeBlock &block) { return sum + block.size; });
  int largest_free = 0;
  if (!result.free_blocks.empty()) {
    largest_free =
        std::max_element(result.free_blocks.begin(), result.free_blocks.end(),
                         [](const FreeBlock &lhs, const FreeBlock &rhs) {
                           return lhs.size < rhs.size;
                         })
            ->size;
  }

  std::cout << "\n最终空闲分区队列: ";
  printFreeBlocks(result.free_blocks);
  std::cout << "\n";
  if (success_count != requested) {
    std::cout << "警告: 有 " << (requested - success_count)
              << " 个请求未能分配\n";
  } else {
    std::cout << "全部请求均已分配\n";
  }
  std::cout << "汇总: 成功分配 " << success_count << "/" << requested
            << " 个请求, 已占用 " << allocated_size << " 字节, 剩余空闲 "
            << free_size << " 字节 (共 " << result.free_blocks.size()
            << " 个分区), 最大空闲分区: " << largest_free << " 字节\n";
}

// 读取实验数据文件, 返回 false 表示文件打不开或没有有效数据;
// 非法行会被跳过并给出提示
bool readWorkload(const std::string &path, std::vector<FreeBlock> &free_blocks,
                  std::vector<Request> &requests) {
  std::ifstream input(path);
  if (!input) {
    std::cout << "打开文件 " << path << " 失败!\n";
    return false;
  }

  // 数据文件用段标记区分两部分: [FREE] 之后是空闲分区, [REQUEST] 之后是进程请求
  enum class Section { NONE, FREE, REQUEST };
  Section section = Section::NONE;

  int line_number = 0;
  for (std::string line; std::getline(input, line);) {
    ++line_number;
    // 去掉 '#' 之后的注释
    const std::size_t comment = line.find('#');
    if (comment != std::string::npos) {
      line.erase(comment);
    }
    const std::size_t first = line.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
      continue; // 跳过空行
    }

    // 段标记行, 形如 [FREE] 或 [REQUEST], 大小写不敏感
    if (line[first] == '[') {
      std::string header = line.substr(first);
      std::transform(
          header.begin(), header.end(), header.begin(),
          [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
      if (header.rfind("[FREE", 0) == 0) {
        section = Section::FREE;
      } else if (header.rfind("[REQUEST", 0) == 0) {
        section = Section::REQUEST;
      } else {
        section = Section::NONE; // 未知段之后的数均不再属于任何一段
        std::cout << "第 " << line_number
                  << " 行已忽略 (未知的段标记): " << line << "\n";
      }
      continue;
    }

    std::istringstream iss(line);
    if (section == Section::FREE) {
      // 每行两个数据项: 起始地址 空闲分区大小
      FreeBlock block;
      if (!(iss >> block.start >> block.size)) {
        std::cout << "第 " << line_number
                  << " 行已忽略 (格式应为: 起始地址 分区大小): " << line
                  << "\n";
        continue;
      }
      if (block.start < 0 || block.size <= 0 ||
          block.start > kMaxAddress - block.size) {
        std::cout << "第 " << line_number
                  << " 行已忽略 (要求 起始地址>=0、分区大小>0、起始地址+大小<="
                  << kMaxAddress << "): " << line << "\n";
        continue;
      }
      if (overlaps(free_blocks, block.start, block.size)) {
        std::cout << "第 " << line_number
                  << " 行已忽略 (与已读入的空闲分区重叠): " << line << "\n";
        continue;
      }
      free_blocks.push_back(block);
    } else if (section == Section::REQUEST) {
      // 每行两个数据项: 进程名 请求的分区大小
      Request request;
      if (!(iss >> request.name >> request.need_size)) {
        std::cout << "第 " << line_number
                  << " 行已忽略 (格式应为: 进程名 请求大小): " << line << "\n";
        continue;
      }
      if (request.need_size <= 0 || request.need_size > kMaxAddress) {
        std::cout << "第 " << line_number
                  << " 行已忽略 (要求 0<请求大小<=" << kMaxAddress
                  << "): " << line << "\n";
        continue;
      }
      requests.push_back(request);
    } else {
      std::cout << "第 " << line_number
                << " 行已忽略 (还没有 [FREE] 或 [REQUEST] 段标记): " << line
                << "\n";
    }
  }

  if (free_blocks.empty() || requests.empty()) {
    return false;
  }
  sortByAddress(free_blocks);
  return true;
}

} // namespace

int main(int argc, char *argv[]) {
  // 允许在命令行指定数据文件: ./main other_memory.txt
  const std::string path = argc > 1 ? argv[1] : "memory.txt";

  std::cout << "开始读入内存数据\n";
  std::vector<FreeBlock> free_blocks;
  std::vector<Request> requests;
  if (!readWorkload(path, free_blocks, requests)) {
    std::cout << "文件 " << path << " 中没有有效数据, 程序退出!\n";
    return 1;
  }
  std::cout << "内存数据读入成功!\n";
  std::cout << "空闲分区总数: " << free_blocks.size() << "\n";
  std::cout << "进程请求总数: " << requests.size() << "\n\n";

  printInput(free_blocks, requests);

  while (true) {
    std::cout
        << "请选择一种分区分配算法: \n"
        << "(1)首次适应算法 (FIRST FIT)\n"
        << "(2)最佳适应算法 (BEST FIT)\n" // 三种算法共用一套代码, 只换选择规则
        << "(3)最坏适应算法 (WORST FIT)\n"
        << "(4)三种算法全部输出\n"
        << "(0)退出\n";
    int choice = 0;
    if (!(std::cin >> choice)) {
      break;
    }
    switch (choice) {
    case 1:
    case 2:
    case 3: // 枚举取值与菜单编号一致, 可以直接转换
      printSimulation(free_blocks, requests, static_cast<Algorithm>(choice));
      break;
    case 4: // 依次输出三种算法的空闲分区队列与分配结果
      printSimulation(free_blocks, requests, Algorithm::FIRST_FIT);
      printSimulation(free_blocks, requests, Algorithm::BEST_FIT);
      printSimulation(free_blocks, requests, Algorithm::WORST_FIT);
      break;
    case 0:
      return 0;
    default:
      std::cout << "输入无效, 请重新选择!\n";
      break;
    }
  }
  return 0;
}
