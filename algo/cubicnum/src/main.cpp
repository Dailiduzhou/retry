#include <iostream>
using namespace std;

int main(int argc, char **argv) {

  for (int i = 100; i < 1000; ++i) {
    int tmp = i;
    int cubic = 0;
    while (tmp) {
      int th = tmp % 10;
      tmp /= 10;
      cubic += th * th * th;
    }
    if (cubic == i) {
      cout << i << '\n';
    }
  }
  return 0;
}
