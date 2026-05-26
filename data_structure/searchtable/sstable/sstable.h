#ifndef SSTABLE_H_
#define SSTABLE_H_

typedef int KeyType;
typedef struct {
  KeyType key;
} ElemType;

typedef struct {
  ElemType *elem;
  int length;
} SSTable;

void Create(SSTable &ST, int n);
void Destroy(SSTable &ST);
int Search_Seq(const SSTable &ST, KeyType kval);
int Search_Bin(const SSTable &ST, KeyType kval);
void Traverse(const SSTable &ST);

#endif // !SSTABLE_H_
