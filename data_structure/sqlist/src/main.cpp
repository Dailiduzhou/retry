#include <iostream>
typedef int ElemType;
typedef struct SqList {
  ElemType *data;
  int size;
  int capacity;
} SqList;

void SqListInit(SqList &s, int capacity = 10) {
  s.data = new ElemType[capacity];
  s.size = 0;
  s.capacity = capacity;
}

int LocateElem(const SqList &s, ElemType val) {
  for (int i = 0; i < s.size; ++i) {
    if (val == s.data[i]) {
      return i;
    }
  }
  return -1;
}

bool SqListInsert(SqList &s, ElemType val) {
  if (s.size == s.capacity) {
    return false;
  }
  int i = s.size - 1;
  while (i >= 0 && s.data[i] > val) {
    s.data[i + 1] = s.data[i];
    --i;
  }

  s.data[i + 1] = val;
  s.size++;
  return true;
}

bool SqListDelete(SqList &s, ElemType val) {
  if (s.size == 0) {
    return false;
  }
  int pos = LocateElem(s, val);
  if (pos == -1) {
    return false;
  }

  for (int i = pos; i < s.size - 1; ++i) {
    s.data[i] = s.data[i + 1];
  }
  s.size--;
  return true;
}

bool SqListEqual(const SqList &s1, const SqList &s2) {
  if (s1.size != s2.size) {
    return false;
  }
  int size = s1.size;
  for (int i = 0; i < size; ++i) {
    if (s1.data[i] != s2.data[i]) {
      return false;
    }
  }
  return true;
}

void SqListPrint(const SqList &s) {
  std::cout << "[";
  for (int i = 0; i < s.size; ++i) {
    if (i > 0) std::cout << ", ";
    std::cout << s.data[i];
  }
  std::cout << "] (size=" << s.size << ", cap=" << s.capacity << ")" << std::endl;
}

void SqListDestroy(SqList &s) {
  delete[] s.data;
  s.data = nullptr;
  s.size = 0;
  s.capacity = 0;
}

int main() {
  std::cout << "=== Test 1: Init ===" << std::endl;
  SqList s;
  SqListInit(s);
  SqListPrint(s);

  std::cout << "\n=== Test 2: Insert (empty -> sorted) ===" << std::endl;
  SqListInsert(s, 3);
  SqListInsert(s, 1);
  SqListInsert(s, 2);
  SqListPrint(s); // expect [1, 2, 3]

  std::cout << "\n=== Test 3: LocateElem ===" << std::endl;
  std::cout << "LocateElem(s, 1) = " << LocateElem(s, 1) << " (expect 0)" << std::endl;
  std::cout << "LocateElem(s, 3) = " << LocateElem(s, 3) << " (expect 2)" << std::endl;
  std::cout << "LocateElem(s, 5) = " << LocateElem(s, 5) << " (expect -1)" << std::endl;

  std::cout << "\n=== Test 4: Delete ===" << std::endl;
  SqListDelete(s, 1);
  SqListPrint(s); // expect [2, 3]
  std::cout << "Delete 99 (not exist) => " << (SqListDelete(s, 99) ? "deleted" : "not found") << std::endl;
  SqListDelete(s, 2);
  SqListDelete(s, 3);
  SqListPrint(s); // expect []
  std::cout << "Delete from empty => " << (SqListDelete(s, 1) ? "deleted" : "failed") << std::endl;

  std::cout << "\n=== Test 5: SqListEqual ===" << std::endl;
  SqList a, b, c;
  SqListInit(a);
  SqListInit(b);
  SqListInit(c);
  SqListInsert(a, 1); SqListInsert(a, 2);
  SqListInsert(b, 1); SqListInsert(b, 2);
  SqListInsert(c, 1); SqListInsert(c, 3);
  std::cout << "a == b: " << (SqListEqual(a, b) ? "true" : "false") << " (expect true)" << std::endl;
  std::cout << "a == c: " << (SqListEqual(a, c) ? "true" : "false") << " (expect false)" << std::endl;
  std::cout << "a == empty: " << (SqListEqual(a, s) ? "true" : "false") << " (expect false)" << std::endl;

  SqListDestroy(s);
  SqListDestroy(a);
  SqListDestroy(b);
  SqListDestroy(c);

  return 0;
}
