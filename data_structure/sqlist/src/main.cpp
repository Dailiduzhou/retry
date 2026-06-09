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

bool SqListInsert(SqList &s, ElemType val) {
  for (int i = s.size - 1; i >= 0; --i) {
    if () {
    }
  }
}

int main(int argc, char **argv) { return 0; }
