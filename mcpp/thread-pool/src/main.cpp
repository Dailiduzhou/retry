#include <condition_variable>
#include <deque>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <numeric>
#include <stdexcept>
#include <string>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

void expect(bool condition, const char *message) {
  if (!condition) {
    throw std::logic_error(message);
  }
}

class ThreadPool {
  std::vector<std::thread> workers;
  std::deque<std::packaged_task<void()>> tasks;
  std::mutex mtx;
  std::condition_variable cv;
  bool stop = false;

public:
  ThreadPool(size_t N) {
    for (size_t i = 0; i < N; ++i) {
      workers.emplace_back([this] {
        while (true) {
          std::packaged_task<void()> task;
          {
            std::unique_lock lock(mtx);
            cv.wait(lock, [this] { return stop || !tasks.empty(); });
            if (stop && tasks.empty())
              return;
            task = std::move(tasks.front());
            tasks.pop_front();
          }
          task(); // 执行任务
        }
      });
    }
  }

  template <typename F, typename... Args>
  auto enqueue(F &&f, Args &&...args)
      -> std::future<std::invoke_result_t<F, Args...>> {
    using RetType = std::invoke_result_t<F, Args...>;
    auto task = std::make_shared<std::packaged_task<RetType()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<RetType> fut = task->get_future();
    {
      std::lock_guard lock(mtx);
      tasks.emplace_back([task]() { (*task)(); });
    }
    cv.notify_one();
    return fut;
  }

  ~ThreadPool() {
    {
      std::lock_guard lock(mtx);
      stop = true;
    }
    cv.notify_all();
    for (auto &t : workers)
      t.join();
  }
};

int main() {
  ThreadPool pool(4);

  auto answer = pool.enqueue([] { return 42; });
  expect(answer.get() == 42, "task without arguments should return its result");

  auto product = pool.enqueue([](int lhs, int rhs) { return lhs * rhs; }, 6, 7);
  expect(product.get() == 42, "task with arguments should receive arguments");

  std::vector<std::future<int>> futures;
  for (int i = 1; i <= 10; ++i) {
    futures.emplace_back(pool.enqueue([](int value) { return value * value; }, i));
  }

  std::vector<int> squares;
  squares.reserve(futures.size());
  for (auto &future : futures) {
    squares.emplace_back(future.get());
  }

  const int total = std::accumulate(squares.begin(), squares.end(), 0);
  expect(total == 385, "parallel tasks should all finish");

  bool finished = false;
  auto voidTask = pool.enqueue([&finished] { finished = true; });
  voidTask.get();
  expect(finished, "void task should run");

  auto failed = pool.enqueue([]() -> int {
    throw std::runtime_error("sample task failed");
  });

  try {
    failed.get();
    expect(false, "failed task should rethrow from future::get");
  } catch (const std::runtime_error &err) {
    expect(std::string(err.what()) == "sample task failed",
           "exception message should be preserved");
  }

  std::cout << "all thread pool samples passed\n";
  return 0;
}
