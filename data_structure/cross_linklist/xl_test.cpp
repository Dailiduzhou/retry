#include "xll.h"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

void CrossSearch(CrossList &M, ElemType x);

enum class MatrixCase {
  AllMatch,
  DistinctValues,
};

struct RunResult {
  bool timed_out = false;
  int exit_code = -1;
  int term_signal = 0;
  std::string output;
};

static void AddNode(CrossList &M, int i, int j, ElemType e) {
  OLink node = new OLNode{i, j, e, nullptr, nullptr};

  if (!M.rhead[i] || M.rhead[i]->j > j) {
    node->rnext = M.rhead[i];
    M.rhead[i] = node;
  } else {
    OLink p = M.rhead[i];
    while (p->rnext && p->rnext->j < j) {
      p = p->rnext;
    }
    node->rnext = p->rnext;
    p->rnext = node;
  }

  if (!M.chead[j] || M.chead[j]->i > i) {
    node->cnext = M.chead[j];
    M.chead[j] = node;
  } else {
    OLink p = M.chead[j];
    while (p->cnext && p->cnext->i < i) {
      p = p->cnext;
    }
    node->cnext = p->cnext;
    p->cnext = node;
  }

  M.t++;
}

static CrossList BuildMatrix(MatrixCase which) {
  CrossList M{};
  M.m = 2;
  M.n = 2;
  M.t = 0;
  M.rhead = new OLink[M.m]();
  M.chead = new OLink[M.n]();

  if (which == MatrixCase::AllMatch) {
    AddNode(M, 0, 0, 5);
    AddNode(M, 1, 1, 5);
  } else {
    AddNode(M, 0, 0, 1);
    AddNode(M, 1, 1, 2);
  }
  return M;
}

static void DestroyMatrix(CrossList &M) {
  for (int i = 0; i < M.m; ++i) {
    OLink p = M.rhead[i];
    while (p) {
      OLink next = p->rnext;
      delete p;
      p = next;
    }
  }
  delete[] M.rhead;
  delete[] M.chead;
  M = CrossList{};
}

static RunResult RunCrossSearchInChild(MatrixCase which, ElemType target,
                                       int timeout_ms) {
  RunResult result;

  std::cout.flush();
  std::cerr.flush();

  int pipe_fd[2];
  if (pipe(pipe_fd) != 0) {
    result.exit_code = -2;
    return result;
  }

  pid_t pid = fork();
  if (pid < 0) {
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    result.exit_code = -3;
    return result;
  }

  if (pid == 0) {
    close(pipe_fd[0]);
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[1]);

    CrossList M = BuildMatrix(which);
    CrossSearch(M, target);
    DestroyMatrix(M);
    _exit(0);
  }

  close(pipe_fd[1]);

  int status = 0;
  bool child_done = false;
  auto deadline =
      std::chrono::steady_clock::now() + std::chrono::milliseconds(timeout_ms);
  while (std::chrono::steady_clock::now() < deadline) {
    pid_t waited = waitpid(pid, &status, WNOHANG);
    if (waited == pid) {
      child_done = true;
      break;
    }
    if (waited < 0) {
      child_done = true;
      break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  if (!child_done) {
    result.timed_out = true;
    kill(pid, SIGKILL);
    waitpid(pid, &status, 0);
  }

  if (WIFEXITED(status)) {
    result.exit_code = WEXITSTATUS(status);
  } else if (WIFSIGNALED(status)) {
    result.term_signal = WTERMSIG(status);
  }

  char buf[256];
  ssize_t n = 0;
  while ((n = read(pipe_fd[0], buf, sizeof(buf))) > 0) {
    result.output.append(buf, static_cast<size_t>(n));
  }
  close(pipe_fd[0]);

  return result;
}

static bool TestFoundValueShouldReturnAndPrintPositions() {
  RunResult res = RunCrossSearchInChild(MatrixCase::AllMatch, 5, 500);

  bool ok = true;
  if (res.timed_out) {
    std::cerr << "  timeout: search for existing value did not return\n";
    ok = false;
  }
  if (res.term_signal != 0) {
    std::cerr << "  signaled: process terminated by signal " << res.term_signal
              << '\n';
    ok = false;
  }
  if (res.exit_code != 0) {
    std::cerr << "  exit_code: expected 0, got " << res.exit_code << '\n';
    ok = false;
  }
  if (res.output.find("(0,0)") == std::string::npos ||
      res.output.find("(1,1)") == std::string::npos) {
    std::cerr << "  output mismatch: expected to contain (0,0) and (1,1)\n";
    std::cerr << "  actual:   " << res.output << '\n';
    ok = false;
  }
  return ok;
}

static bool TestMissingValueShouldReturnWithoutOutput() {
  RunResult res = RunCrossSearchInChild(MatrixCase::DistinctValues, 42, 500);

  bool ok = true;
  if (res.timed_out) {
    std::cerr << "  timeout: search for missing value did not return\n";
    ok = false;
  }
  if (res.term_signal != 0) {
    std::cerr << "  signaled: process terminated by signal " << res.term_signal
              << '\n';
    ok = false;
  }
  if (res.exit_code != 0) {
    std::cerr << "  exit_code: expected 0, got " << res.exit_code << '\n';
    ok = false;
  }
  if (!res.output.empty()) {
    std::cerr << "  output mismatch: expected empty output, got\n"
              << res.output;
    ok = false;
  }
  return ok;
}

int main() {
  int failed = 0;

  std::cout << "[TEST] Search existing value\n";
  if (!TestFoundValueShouldReturnAndPrintPositions()) {
    ++failed;
    std::cout << "  -> FAILED\n";
  } else {
    std::cout << "  -> PASSED\n";
  }

  std::cout << "[TEST] Search missing value\n";
  if (!TestMissingValueShouldReturnWithoutOutput()) {
    ++failed;
    std::cout << "  -> FAILED\n";
  } else {
    std::cout << "  -> PASSED\n";
  }

  if (failed == 0) {
    std::cout << "\nAll tests passed.\n";
    return 0;
  }

  std::cout << "\n" << failed << " test(s) failed.\n";
  return 1;
}
