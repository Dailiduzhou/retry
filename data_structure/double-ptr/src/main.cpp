#include <iostream>

void rearrange(int A[], int n) {
  if (n <= 1) {
    return;
  }
  int left = 0;
  int right = n - 1;
  while (left < right) {
    while (left < right && A[left] < 0) {
      left++;
    }
    while (left < right && A[right] >= 0) {
      right--;
    }
    if (left < right) {
      int tmp = A[left];
      A[left] = A[right];
      A[right] = tmp;
    }
  }
}
int main() {
  int arr[] = {3, -1, 2, -5, 0, -2, 4};
  int n = sizeof(arr) / sizeof(arr[0]);
  rearrange(arr, n);
  for (int x : arr)
    std::cout << x << " ";
  // 输出示例：-1 -5 -2 3 0 2 4  (顺序可能不同，但负数都在前面)
  return 0;
}
