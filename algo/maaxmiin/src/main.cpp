#include <climits>
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
  int n = 10;
  int num;
  int ma = INT_MIN;
  int mi = INT_MAX;
  for (int i = 0; i < n; ++i) {
    cin >> num;
    if (num > ma) {
      ma = num;
    }
    if (num < mi) {
      mi = num;
    }
  }
  cout << ma << ' ' << mi;
  return 0;
}
