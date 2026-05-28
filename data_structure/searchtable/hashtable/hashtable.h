#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <climits>
const int hashsize[10] = {997,  1009, 1013, 1019, 1021,
                          1031, 1033, 1039, 1049, 1051};
typedef int KeyType;
typedef struct {
  KeyType key;
} ElemType;

const int NULLKEY = INT_MAX;

typedef struct {
  ElemType *elem;
  int count;
  int sizeindex;
} HashTable;

enum class Status : int { SUCCESS = 1, UNSUCCESS = 0, DUPLICATE = -1 };

Status SearchHash(const HashTable &H, KeyType kval, int &p, int &c);
int Hash(int kval);
void collision(int &p, int collisions);
Status InsertHash(HashTable &H, ElemType e);
void RecreateHashTable(HashTable &H);

#endif // !HASH_TABLE_H_
