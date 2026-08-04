#include <bits/stdc++.h>
using namespace std;

int main() {
  for (int num = 100; num <= 999; ++num) {
    int a = num / 100;
    int b = (num / 10) % 10;
    int c = num % 10;
    if (a * a * a + b * b * b + c * c * c == num) {
      cout << num << endl;
    }
  }
  return 0;
}
