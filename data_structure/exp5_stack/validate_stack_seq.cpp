#include "validate_stack_seq.h"
#include <stack>
#include "stack.h"

using namespace std;

bool isValid(vector<int>& in, vector<int>& out) {
  if (in.size() != out.size()) {
    return false;
  }

  if (in.empty()) {
    return true;
  }

  stack<int> st;
  int outIdx = 0;

  for (int i = 0; i < in.size(); i++) {
    st.push(in[i]);

    while (!st.empty() && outIdx < out.size() && st.top() == out[outIdx]) {
      st.pop();
      outIdx++;
    }
  }

  return st.empty() && outIdx == out.size();
}

bool isValid_Sq(vector<int>& in, vector<int>& out) {
  if (in.size() != out.size()) {
    return false;
  }

  if (in.empty()) {
    return true;
  }

  SqStack st;
  InitStack_Sq(st);
  int outIdx = 0;
  SElemType topElem;

  for (int i = 0; i < in.size(); i++) {
    Push_Sq(st, in[i]);

    while (!StackEmpty(st) && outIdx < out.size() &&
           GetTop_Sq(st, topElem) && topElem == out[outIdx]) {
      Pop_Sq(st, topElem);
      outIdx++;
    }
  }

  DestroyStack(st);
  return StackEmpty(st) && outIdx == out.size();
}