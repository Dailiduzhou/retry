#include "sset.h"
#include <iostream>

void SetInit(Sset &s, int capacity) {
  s.data = new ElemType[capacity]();
  s.capacity = capacity;
  s.size = 0;
}

int LocateElem(const Sset &s, ElemType val) {
  for (int i = 0; i < s.size; ++i) {
    if (s.data[i] == val) {
      return i;
    }
  }
  return -1;
}

bool SetInsert(Sset &s, ElemType val) {
  if (s.size == s.capacity) {
    return false;
  }
  if (LocateElem(s, val) != -1) {
    return false;
  }

  s.data[s.size++] = val;
  return true;
}

void SetInit(Sset &s, const std::vector<ElemType> &nums) {
  int cap = nums.size() > DEFAULT_CAPACITY ? nums.size() : DEFAULT_CAPACITY;
  SetInit(s, cap);
  for (const auto &num : nums) {
    SetInsert(s, num);
  }
}

void SetTraverse(const Sset &s) {
  for (int i = 0; i < s.size; ++i) {
    std::cout << s.data[i] << ' ';
  }
}

int main() {
  Sset s1;
  SetInit(s1, 10);
  SetInsert(s1, 3);
  SetInsert(s1, 1);
  SetInsert(s1, 4);
  SetInsert(s1, 1);
  SetInsert(s1, 5);
  std::cout << "s1: ";
  SetTraverse(s1);
  std::cout << '\n';
  std::cout << "LocateElem(s1, 4) = " << LocateElem(s1, 4) << '\n';
  std::cout << "LocateElem(s1, 9) = " << LocateElem(s1, 9) << '\n';

  Sset s2;
  SetInit(s2, std::vector<ElemType>{9, 2, 6, 9, 5});
  std::cout << "s2: ";
  SetTraverse(s2);
  std::cout << '\n';

  return 0;
}
