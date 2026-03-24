#ifndef SQLIST
#define SQLIST

typedef int KeyType;
typedef struct {
  KeyType key;
} RcdType;

const int MAXSIZE = 20;

typedef struct {
  RcdType r[MAXSIZE + 1];
  int length;
} SqList;

#endif // !SORT
