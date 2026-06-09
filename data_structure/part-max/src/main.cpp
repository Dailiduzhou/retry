#include <climits>
#include <iostream>
void calMulMax(int A[], int res[], int n) {
  int suffix_max = INT_MIN, suffix_min = INT_MAX;
  for (int i = n - 1; i >= 0; --i) {
    if (A[i] > suffix_max)
      suffix_max = A[i];
    if (A[i] < suffix_min)
      suffix_min = A[i];
    if (A[i] >= 0)
      res[i] = A[i] * suffix_max;
    else
      res[i] = A[i] * suffix_min;
  }
}
int main(int argc, char **argv) {
  int n = 6;
  int nums[] = {-1, 7, -9, 2, 6, 3};
  int *res = new int[6]();
  calMulMax(nums, res, n);
  for (int i = 0; i < n; ++i) {
    std::cout << res[i] << ' ';
  }
  delete[] res;
  return 0;
}
