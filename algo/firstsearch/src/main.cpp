#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char **argv) {
  int n;
  cin >> n;
  vector<int> nums(n, 0);
  int num;
  for (int i = 0; i < n; ++i) {
    cin >> num;
    nums[i] = num;
  }

  int target;
  cin >> target;
  int pos = -1;
  for (int i = 0; i < n; ++i) {
    if (target == nums.at(i)) {
      pos = i + 1;
      break;
    }
  }
  cout << pos;
}
