#include <cctype>
#include <iostream>
#include <string>

int main() {
  std::string line;
  std::getline(std::cin, line);

  int upper = 0, lower = 0, digit = 0, other = 0;

  for (char ch : line) {
    unsigned char c = static_cast<unsigned char>(ch);

    if (std::isupper(c)) {
      ++upper;
    } else if (std::islower(c)) {
      ++lower;
    } else if (std::isdigit(c)) {
      ++digit;
    } else {
      ++other;
    }
  }

  std::cout << upper << std::endl;
  std::cout << lower << std::endl;
  std::cout << digit << std::endl;
  std::cout << other << std::endl;

  return 0;
}
