#include "glist.h"
#include <iostream>
using namespace std;
void OutputGList(GList LS) {
  if (!LS) {
    cout << "()";
  } else {
    if (LS->tag == ElemTag::ATOM) {
      cout << LS->data;
    } else {
      cout << '(';
      GLNode *p = LS;
      while (p) {
        OutputGList(p->ptr.hp);
        p = p->ptr.tp;
        if (p) {
          cout << ',';
        }
      }
      cout << ')';
    }
  }
}
