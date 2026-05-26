#ifndef INDEXTABLE_H_
#define INDEXTABLE_H_

typedef int KeyType;
typedef struct {
  KeyType key;
  int stadr;
} indexItem;

typedef struct {
  indexItem *elem;
  int length;
} indexTable;

#endif // !INDEXTABLE_H_
