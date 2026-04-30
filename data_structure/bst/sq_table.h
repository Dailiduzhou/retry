#ifndef SQ_TABLE_H_
#define SQ_TABLE_H_

#include "bitree.h"

// 顺序表结构定义
#define MAX_SIZE 100

typedef struct {
  KeyType r[MAX_SIZE]; // 存储元素，r[0]闲置或作为哨兵
  int length;          // 顺序表长度
} SqTable;

// 顺序表基本操作
void InitSqTable(SqTable &L);
void DestroySqTable(SqTable &L);
bool SqTableEmpty(const SqTable &L);
int SqTableLength(const SqTable &L);
bool GetElem(const SqTable &L, int i, KeyType &e);
int LocateElem(const SqTable &L, KeyType e);
bool InsertElem(SqTable &L, int i, KeyType e);
bool DeleteElem(SqTable &L, int i, KeyType &e);
void PrintSqTable(const SqTable &L);

// BST排序函数
void BSTSort(SqTable &L);

#endif // SQ_TABLE_H_
