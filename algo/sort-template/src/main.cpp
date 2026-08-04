#include <algorithm>
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

  sort(nums.begin(), nums.end());

  for (const auto num : nums) {
    cout << num << ' ';
  }
  return 0;
}
