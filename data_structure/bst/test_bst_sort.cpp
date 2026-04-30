#include "bitree.h"
#include "sq_table.h"
#include <iostream>
using namespace std;

// 测试BST排序
void testBSTSort() {
  cout << "========== BST排序测试 ==========" << endl;
  
  SqTable L;
  InitSqTable(L);
  
  // 插入一些无序数据
  int data[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
  int n = sizeof(data) / sizeof(data[0]);
  
  cout << "原始数据: ";
  for (int i = 0; i < n; ++i) {
    L.r[i + 1] = data[i];
    cout << data[i] << " ";
  }
  L.length = n;
  cout << endl;
  
  cout << "原始顺序表: ";
  PrintSqTable(L);
  
  // 使用BST排序
  BSTSort(L);
  
  cout << "排序后: ";
  PrintSqTable(L);
  
  // 验证是否有序
  bool sorted = true;
  for (int i = 1; i < L.length; ++i) {
    if (L.r[i] > L.r[i + 1]) {
      sorted = false;
      break;
    }
  }
  cout << "验证结果: " << (sorted ? "排序成功" : "排序失败") << endl;
  
  DestroySqTable(L);
  cout << endl;
}

// 测试空表和单元素表
void testEdgeCases() {
  cout << "========== 边界情况测试 ==========" << endl;
  
  // 测试空表
  SqTable L1;
  InitSqTable(L1);
  cout << "空表排序前: ";
  PrintSqTable(L1);
  BSTSort(L1);
  cout << "空表排序后: ";
  PrintSqTable(L1);
  cout << endl;
  
  // 测试单元素表
  SqTable L2;
  InitSqTable(L2);
  L2.r[1] = 42;
  L2.length = 1;
  cout << "单元素表排序前: ";
  PrintSqTable(L2);
  BSTSort(L2);
  cout << "单元素表排序后: ";
  PrintSqTable(L2);
  cout << endl;
  
  // 测试已排序表
  SqTable L3;
  InitSqTable(L3);
  int sortedData[] = {10, 20, 30, 40, 50};
  for (int i = 0; i < 5; ++i) {
    L3.r[i + 1] = sortedData[i];
  }
  L3.length = 5;
  cout << "已排序表排序前: ";
  PrintSqTable(L3);
  BSTSort(L3);
  cout << "已排序表排序后: ";
  PrintSqTable(L3);
  cout << endl;
  
  // 测试逆序表
  SqTable L4;
  InitSqTable(L4);
  int reverseData[] = {50, 40, 30, 20, 10};
  for (int i = 0; i < 5; ++i) {
    L4.r[i + 1] = reverseData[i];
  }
  L4.length = 5;
  cout << "逆序表排序前: ";
  PrintSqTable(L4);
  BSTSort(L4);
  cout << "逆序表排序后: ";
  PrintSqTable(L4);
  cout << endl;
  
  DestroySqTable(L1);
  DestroySqTable(L2);
  DestroySqTable(L3);
  DestroySqTable(L4);
}

// 测试顺序表基本操作
void testSqTableOperations() {
  cout << "========== 顺序表基本操作测试 ==========" << endl;
  
  SqTable L;
  InitSqTable(L);
  
  cout << "1. 插入元素" << endl;
  InsertElem(L, 1, 10);
  InsertElem(L, 2, 20);
  InsertElem(L, 3, 30);
  InsertElem(L, 2, 15); // 在中间插入
  cout << "插入后: ";
  PrintSqTable(L);
  
  cout << "2. 查找元素" << endl;
  KeyType e;
  if (GetElem(L, 2, e)) {
    cout << "第2个元素是: " << e << endl;
  }
  int pos = LocateElem(L, 20);
  cout << "元素20的位置: " << pos << endl;
  
  cout << "3. 删除元素" << endl;
  KeyType deleted;
  DeleteElem(L, 2, deleted);
  cout << "删除第2个元素(" << deleted << ")后: ";
  PrintSqTable(L);
  
  cout << "4. 表长: " << SqTableLength(L) << endl;
  cout << "5. 是否为空: " << (SqTableEmpty(L) ? "是" : "否") << endl;
  
  DestroySqTable(L);
  cout << endl;
}

int main() {
  cout << "顺序表与BST排序测试程序" << endl;
  cout << "=========================" << endl << endl;
  
  testSqTableOperations();
  testBSTSort();
  testEdgeCases();
  
  cout << "所有测试完成!" << endl;
  
  return 0;
}
