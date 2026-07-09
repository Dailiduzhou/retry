#include <iostream>
using namespace std;

int main(int argc, char **argv) {
  int n;
  cin >> n;
  if (n == 1 || n == 2) {
    cout << 1;
    return 0;
  }

  int prev = 1;
  int cur = 1;
  for (int i = 2; i < n; ++i) {
    int tmp = cur;
    cur = cur + prev;
    prev = tmp;
  }
  cout << cur;
  return 0;
}
