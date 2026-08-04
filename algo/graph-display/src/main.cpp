#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
  int row, col;
  cin >> row >> col;
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      cout << (char)(std::abs(j - i) + 'A');
    }
    cout << endl;
  }
  return 0;
}
