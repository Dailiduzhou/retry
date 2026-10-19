#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

namespace {

constexpr int kMinutesPerHour = 60; // 1 小时 = 60 分钟
constexpr int kHoursPerDay = 24;    // 一天 24 小时

// 一个作业的输入数据
struct Job {
  int number = 0;      // 作业号
  int arrive_time = 0; // 作业进入系统的时间, 形如 1010
  int need_time = 0;   // 估计执行时间, 单位: 分钟
};

// 一个作业的调度结果
struct JobStat {
  int number;
  int arrive_time;            // 形如 1010
  int need_time;              // 要求服务时间(分钟)
  int enter_time;             // 进入内存的时间(分钟)
  int finish_time;            // 完成时间(分钟)
  int wait_time;              // 等待时间 = 进入内存 - 到达
  int turnaround_time;        // 周转时间 = 完成 - 到达
  double weighted_turnaround; // 带权周转时间 = 周转时间 / 服务时间
};

// 调度结果: 调度时刻(分钟) + 按调度顺序排列的作业统计信息
struct ScheduleResult {
  int schedule_time;
  std::vector<JobStat> stats;
};

// 调度算法, 取值与菜单编号一致; enum class 不会隐式转换成 int
enum class Algorithm { FCFS = 1, SJF = 2, HRN = 3 };

// 判断 hhmm 是否为合法的 24 小时制时间(形如 HHMM: 800 表示 8:00, 30 表示 0:30)
constexpr bool isValidHHMM(int hhmm) {
  return hhmm >= 0 && hhmm / 100 < kHoursPerDay && hhmm % 100 < kMinutesPerHour;
}

// 把 800 这样的时间转换成 0 点起的分钟数; 非法输入返回 -1
constexpr int toMinutes(int hhmm) {
  return isValidHHMM(hhmm) ? hhmm / 100 * kMinutesPerHour + hhmm % 100 : -1;
}

// 把 0 点起的分钟数转换回 800 这样的时间; 超出 [0, 24:00) 返回 -1
// 与 toMinutes 互为逆运算, 因此凌晨时刻(如 30 表示 0:30)也能正确输出
constexpr int toHHMM(int minutes) {
  return minutes >= 0 && minutes < kHoursPerDay * kMinutesPerHour
             ? minutes / kMinutesPerHour * 100 + minutes % kMinutesPerHour
             : -1;
}

const char *nameOf(Algorithm algorithm) {
  switch (algorithm) {
  case Algorithm::FCFS:
    return "FCFS";
  case Algorithm::SJF:
    return "SJF";
  case Algorithm::HRN:
    return "HRN";
  }
  return "UNKNOWN";
}

// 计算响应比: (等待时间 + 要求服务时间) / 要求服务时间
// 调用前已保证 need_time > 0, 且 now >= 到达时间, 因此结果一定为有限值
double responseRatio(const Job &job, int now) {
  const int wait_time = now - toMinutes(job.arrive_time);
  return static_cast<double>(wait_time + job.need_time) / job.need_time;
}

// 模拟单道批处理系统的作业调度: 内存一次只放一个作业,
// 调度时刻 = 最后一个作业到达系统的时间, 每送走一个作业就重新调度一次
ScheduleResult schedule(const std::vector<Job> &jobs, Algorithm algorithm) {
  ScheduleResult result{0, {}};
  if (jobs.empty()) {
    return result;
  }

  // 调度时刻 = 最后一个作业到达系统的时间
  const auto latest = std::max_element(
      jobs.begin(), jobs.end(), [](const Job &lhs, const Job &rhs) {
        return toMinutes(lhs.arrive_time) < toMinutes(rhs.arrive_time);
      });
  result.schedule_time = toMinutes(latest->arrive_time);

  result.stats.reserve(jobs.size());
  std::vector<bool> scheduled(jobs.size(), false);
  int now = result.schedule_time;

  for (std::size_t count = 0; count < jobs.size(); ++count) {
    // 1) 收集当前已到达系统、且还没有进入内存的作业
    std::vector<std::size_t> ready;
    for (std::size_t i = 0; i < jobs.size(); ++i) {
      if (!scheduled[i] && toMinutes(jobs[i].arrive_time) <= now) {
        ready.push_back(i);
      }
    }
    if (ready.empty()) {
      break; // 还有作业没到达, 调度结束
    }

    // 2) 自定义用于比较的 lambda 函数:
    //    返回 true 表示 lhs 的优先级低于 rhs, 配合 max_element 取最高优先级
    const auto hasLowerPriority = [&](std::size_t lhs, std::size_t rhs) {
      const Job &a = jobs[lhs];
      const Job &b = jobs[rhs];
      // 并列时的统一规则: 先到达者优先, 再按作业号小的优先
      const auto arrival_key = [](const Job &job) {
        return std::make_tuple(toMinutes(job.arrive_time), job.number);
      };
      switch (algorithm) {
      case Algorithm::FCFS: // 先来先服务: 到达越晚优先级越低
        return arrival_key(a) > arrival_key(b);
      case Algorithm::SJF: // 短作业优先: 估计执行时间越长优先级越低
                           // 使用tuple简化比较逻辑
        return std::make_tuple(a.need_time, toMinutes(a.arrive_time),
                               a.number) >
               std::make_tuple(b.need_time, toMinutes(b.arrive_time), b.number);
      case Algorithm::HRN: { // 最高响应比优先: 每次调度都用当前时间重算
        const double ratio_a = responseRatio(a, now);
        const double ratio_b = responseRatio(b, now);
        // 先比较响应比(比值相等概率极低, 但相等时仍需给出确定的次序)
        return ratio_a != ratio_b ? ratio_a < ratio_b
                                  : arrival_key(a) > arrival_key(b);
      }
      }
      return false;
    };
    const std::size_t index =
        *std::max_element(ready.begin(), ready.end(), hasLowerPriority);

    // 3) 调度该作业: 进入内存 -> 执行 -> 让出内存
    const Job &job = jobs[index];
    const int arrive = toMinutes(job.arrive_time);
    const int enter_time = now;
    const int finish_time = enter_time + job.need_time;
    now = finish_time; // 作业执行完才让出内存
    scheduled[index] = true;

    result.stats.push_back(
        JobStat{job.number, job.arrive_time, job.need_time, enter_time,
                finish_time, enter_time - arrive, finish_time - arrive,
                static_cast<double>(finish_time - arrive) / job.need_time});
  }
  return result;
}

// 对某项统计量求平均, getter 决定统计哪一项
template <typename Getter>
double average(const std::vector<JobStat> &stats, Getter getter) {
  if (stats.empty()) {
    return 0.0;
  }
  const double sum =
      std::accumulate(stats.begin(), stats.end(), 0.0,
                      [&getter](double acc, const JobStat &stat) {
                        return acc + getter(stat);
                      });
  return sum / static_cast<double>(stats.size());
}

// 打印作业表, 列: number arrive_time need_time
void printJobs(const std::vector<Job> &jobs) {
  std::cout << "number\tarrive_time\tneed_time\n";
  for (const auto &job : jobs) {
    std::cout << job.number << "\t" << job.arrive_time << "\t\t"
              << job.need_time << "\n";
  }
}

// 输出某个算法的调度结果: 每行一个作业, 最后给出三项平均值
void printSchedule(const std::vector<Job> &jobs, Algorithm algorithm) {
  const ScheduleResult result = schedule(jobs, algorithm);

  std::cout << "\n---------- " << nameOf(algorithm) << " ----------\n";
  std::cout << "调度时刻: " << toHHMM(result.schedule_time) << "\n";

  std::size_t order = 0;
  for (const auto &stat : result.stats) {
    ++order;
    // n-th job: arrival time: xxx, service time: xxx
    // wait_time: xxx, turnaround time:xxx, weighted turnaround time:xxx
    std::cout << order << "-th job: number: " << stat.number
              << ", arrival time: " << stat.arrive_time
              << ", service time: " << stat.need_time
              << ", enter time: " << toHHMM(stat.enter_time)
              << ", finish time: " << toHHMM(stat.finish_time)
              << ", wait_time: " << stat.wait_time
              << ", turnaround time: " << stat.turnaround_time
              << ", weighted turnaround time: " << std::fixed
              << std::setprecision(2) << stat.weighted_turnaround << "\n";
  }

  // 只有全部作业都进入过内存, 才认为调度完成
  if (result.stats.size() != jobs.size()) {
    std::cout << "Warning: " << (jobs.size() - result.stats.size())
              << " job(s) never arrived and are not scheduled\n";
    return;
  }
  std::cout << "All jobs are scheduled\n";
  std::cout << "Average wait time: " << std::fixed << std::setprecision(2)
            << average(result.stats,
                       [](const JobStat &stat) {
                         return static_cast<double>(stat.wait_time);
                       })
            << ". Average turnaround time: "
            << average(result.stats,
                       [](const JobStat &stat) {
                         return static_cast<double>(stat.turnaround_time);
                       })
            << ". Average weighted turnaround time: "
            << average(
                   result.stats,
                   [](const JobStat &stat) { return stat.weighted_turnaround; })
            << "\n";
}

// 读取作业文件, 返回有效作业数; 非法行会被跳过并给出提示
std::size_t readJobs(const std::string &path, std::vector<Job> &jobs) {
  std::ifstream input(path);
  if (!input) {
    std::cout << "open file " << path << " failed!\n";
    return 0;
  }

  // 每行三个数据项: 作业号 作业进入系统的时间 估计执行时间
  int line_number = 0;
  for (std::string line; std::getline(input, line);) {
    ++line_number;
    if (line.find_first_not_of(" \t\r\n") == std::string::npos) {
      continue; // 跳过空行
    }
    std::istringstream iss(line);
    Job job;
    if (!(iss >> job.number >> job.arrive_time >> job.need_time)) {
      std::cout << "line " << line_number << " ignored (bad format): " << line
                << "\n";
      continue;
    }
    if (job.number <= 0 || !isValidHHMM(job.arrive_time) ||
        job.need_time <= 0) {
      std::cout << "line " << line_number
                << " ignored (expect: number>0, arrive HHMM, need>0): " << line
                << "\n";
      continue;
    }
    jobs.push_back(job);
  }
  return jobs.size();
}

} // namespace

int main(int argc, char *argv[]) {
  // 允许在命令行指定作业文件: ./main other_jobs.txt
  const std::string path = argc > 1 ? argv[1] : "jobs.txt";

  std::cout << "Start to read in jobs data\n";
  std::vector<Job> jobs;
  if (readJobs(path, jobs) == 0) {
    std::cout << "no valid job in file " << path << ", exit!\n";
    return 1;
  }
  std::cout << "read jobs' data successfully!\n";
  std::cout << "Total jobs number: " << jobs.size() << "\n";

  printJobs(jobs);

  while (true) {
    std::cout << "Please select one of the scheduling algorithms: \n"
              << "(1)FCFS\n"
              << "(2)SJF\n" // 三种算法共用一套代码, 只换比较规则
              << "(3)HRN\n"
              << "(0)EXIT\n";
    int choice = 0;
    if (!(std::cin >> choice)) {
      break;
    }
    switch (choice) {
    case 1:
    case 2:
    case 3: // 枚举取值与菜单编号一致, 可以直接转换
      printSchedule(jobs, static_cast<Algorithm>(choice));
      break;
    case 0:
      return 0;
    default:
      std::cout << "invalid choice, try again!\n";
      break;
    }
  }
  return 0;
}
