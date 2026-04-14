#include "validate_stack_seq.h"
#include <stack>

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
