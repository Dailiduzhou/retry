#include <iostream>
using namespace std;

class A {
public:
  virtual void func1() { cout << "A1"; }
  void func2() { cout << "A2"; }
};

class B : public A {
public:
  void func1() { cout << "B1"; }
  void func2() { cout << "B2"; }
};

int main() {
  A *p = new B;
  p->func1();
  p->func2();
  return 0;
}
