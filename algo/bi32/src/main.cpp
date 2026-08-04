#include <iostream>
using namespace std;

int main() {
  for (int i = 0; i < 32; ++i) {
    int bits[5];
    int temp = i;
    for (int j = 4; j >= 0; --j) {
      bits[j] = temp % 2;
      temp /= 2;
    }
    for (int j = 0; j < 5; ++j) {
      cout << bits[j];
    }
    cout << endl;
  }
  return 0;
}
