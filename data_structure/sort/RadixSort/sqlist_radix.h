#ifndef SQLIST_RADIX
#define SQLIST_RADIX

typedef int KeysType;

#define MAX_NUM_OF_KEY 10
#define RADIX 10
#define MAXSIZE 10000

typedef struct {
  KeysType keys[MAX_NUM_OF_KEY];
  int bitsnum;
} RcdType;

typedef struct {
  RcdType r[MAXSIZE + 1];
  int length;
} SqList;

#endif
