#include "sq_table.h"
#include <iostream>
using namespace std;

void InitSqTable(SqTable &L) {
  L.length = 0;
}

void DestroySqTable(SqTable &L) {
  L.length = 0;
}

bool SqTableEmpty(const SqTable &L) {
  return L.length == 0;
}

int SqTableLength(const SqTable &L) {
  return L.length;
}

bool GetElem(const SqTable &L, int i, KeyType &e) {
  if (i < 1 || i > L.length) {
    return false;
  }
  e = L.r[i];
  return true;
}

int LocateElem(const SqTable &L, KeyType e) {
  for (int i = 1; i <= L.length; ++i) {
    if (L.r[i] == e) {
      return i;
    }
  }
  return 0;
}

bool InsertElem(SqTable &L, int i, KeyType e) {
  if (i < 1 || i > L.length + 1 || L.length >= MAX_SIZE - 1) {
    return false;
  }
  for (int j = L.length; j >= i; --j) {
    L.r[j + 1] = L.r[j];
  }
  L.r[i] = e;
  L.length++;
  return true;
}

bool DeleteElem(SqTable &L, int i, KeyType &e) {
  if (i < 1 || i > L.length) {
    return false;
  }
  e = L.r[i];
  for (int j = i; j < L.length; ++j) {
    L.r[j] = L.r[j + 1];
  }
  L.length--;
  return true;
}

void PrintSqTable(const SqTable &L) {
  cout << "[";
  for (int i = 1; i <= L.length; ++i) {
    cout << L.r[i];
    if (i < L.length) {
      cout << ", ";
    }
  }
  cout << "]" << endl;
}
