#include <algorithm>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  std::string s;
  std::cin >> s;
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::toupper(c); });
  std::cout << s;
  return 0;
}
