#include "Query.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

static void run_demo(TextQuery &tq) {
  std::vector<Query> demos = {
      Query("fiery") & Query("bird"),
      Query("wind") | Query("storm"),
      ~Query("the"),
      (Query("wind") & Query("storm")) | Query("rain"),
  };

  for (const auto &q : demos) {
    std::cout << "Query: " << q << "\n";
    print(std::cout, q.eval(tq)) << "\n";
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <text-file>\n";
    return 1;
  }

  std::ifstream infile(argv[1]);
  if (!infile) {
    std::cerr << "Failed to open file: " << argv[1] << "\n";
    return 1;
  }

  TextQuery tq(infile);

  std::cout << "Demo queries:\n";
  run_demo(tq);

  std::cout << "Single-word query mode. Enter 'q' to quit.\n";
  std::string s;
  while (true) {
    std::cout << "query> ";
    if (!(std::cin >> s) || s == "q") {
      break;
    }
    Query q(s);
    print(std::cout, q.eval(tq)) << "\n";
  }

  return 0;
}
