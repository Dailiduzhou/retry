#include "glist.h"
#include <iostream>
using namespace std;

// 创建原子节点
GList MakeAtom(int val) {
  GList node = new GLNode;
  node->tag = ElemTag::ATOM;
  node->data = val;
  return node;
}

// 创建列表节点（hp=head, tp=tail）
GList MakeList(GList head, GList tail) {
  GList node = new GLNode;
  node->tag = ElemTag::LIST;
  node->ptr.hp = head;
  node->ptr.tp = tail;
  return node;
}

// 释放广义表
void FreeGList(GList LS) {
  if (!LS) return;
  if (LS->tag == ElemTag::LIST) {
    FreeGList(LS->ptr.hp);
    FreeGList(LS->ptr.tp);
  }
  delete LS;
}

int main() {
  // 测试1: 空表
  cout << "测试1 - 空表: ";
  OutputGList(nullptr);
  cout << endl;

  // 测试2: 单个原子 (a)
  GList a = MakeAtom(5);
  cout << "测试2 - 单原子: ";
  OutputGList(a);
  cout << endl;
  FreeGList(a);

  // 测试3: 简单列表 (1,2,3)
  GList list3 = MakeList(MakeAtom(1),
                 MakeList(MakeAtom(2),
                 MakeList(MakeAtom(3), nullptr)));
  cout << "测试3 - (1,2,3): ";
  OutputGList(list3);
  cout << endl;
  FreeGList(list3);

  // 测试4: 嵌套列表 (1,(2,3),4)
  GList inner = MakeList(MakeAtom(2),
                 MakeList(MakeAtom(3), nullptr));
  GList nested = MakeList(MakeAtom(1),
                 MakeList(inner,
                 MakeList(MakeAtom(4), nullptr)));
  cout << "测试4 - (1,(2,3),4): ";
  OutputGList(nested);
  cout << endl;
  FreeGList(nested);

  // 测试5: 多层嵌套 (1,(2,(3,4)),5)
  GList deep_inner = MakeList(MakeAtom(3),
                     MakeList(MakeAtom(4), nullptr));
  GList mid = MakeList(MakeAtom(2),
              MakeList(deep_inner, nullptr));
  GList deep = MakeList(MakeAtom(1),
               MakeList(mid,
               MakeList(MakeAtom(5), nullptr)));
  cout << "测试5 - (1,(2,(3,4)),5): ";
  OutputGList(deep);
  cout << endl;
  FreeGList(deep);

  // 测试6: 空子表 ((),1)
  GList with_empty = MakeList(nullptr,
                     MakeList(MakeAtom(1), nullptr));
  cout << "测试6 - ((),1): ";
  OutputGList(with_empty);
  cout << endl;
  FreeGList(with_empty);

  return 0;
}
