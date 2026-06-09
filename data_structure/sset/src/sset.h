#ifndef SSET_H_
#define SSET_H_

#include <vector>
const int DEFAULT_CAPACITY = 100;
typedef int ElemType;
typedef struct Sset {
  ElemType *data;
  int size;
  int capacity;
} Sset;

void SetInit(Sset &s, int capacity = DEFAULT_CAPACITY);
bool SetInsert(Sset &s, ElemType val);
void SetInit(Sset &s, const std::vector<ElemType> &nums);
int LocateElem(const Sset &s, ElemType val);
void SetTraverse(const Sset &s);

#endif // !SSET_H_
