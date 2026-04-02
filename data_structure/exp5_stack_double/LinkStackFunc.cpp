#include "stack_double.h"
#include "stack_char.h"
#include <iostream>
#include <cctype>
#include <cmath>

using namespace std;

const char ops[] = {'#', '(', ')', '+', '-', '*', '/'};

bool OpMember(char c) {
  for (int i = 0; i < 7; i++) {
    if (ops[i] == c)
      return true;
  }
  return false;
}

double Operate(double a, char op, double b) {
  switch (op) {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
    return a / b;
  default:
    return 0;
  }
}

int GetPriority(char op) {
  switch (op) {
  case '#':
    return 0;
  case '(':
    return 1;
  case '+':
  case '-':
    return 2;
  case '*':
  case '/':
    return 3;
  case ')':
    return 4;
  default:
    return -1;
  }
}

bool precede(char op1, char op2) {
  return GetPriority(op1) >= GetPriority(op2);
}

double evaluation(char prefix[]) {
  SqStackDouble S;
  InitStack_Double(S);
  
  int len = 0;
  while (prefix[len] != '#' && prefix[len] != '\0') {
    len++;
  }
  
  for (int i = len - 1; i >= 0; i--) {
    char ch = prefix[i];
    
    if (ch == ' ' || ch == '\t') {
      continue;
    }
    
    if (isdigit(ch)) {
      Push_Double(S, ch - '0');
    } else if (OpMember(ch) && ch != '#' && ch != '(' && ch != ')') {
      SElemTypeDouble a, b;
      if (Pop_Double(S, a) && Pop_Double(S, b)) {
        Push_Double(S, Operate(a, ch, b));
      }
    }
  }
  
  SElemTypeDouble result = 0;
  Pop_Double(S, result);
  DestroyStack_Double(S);
  
  return result;
}

void transform(char suffix[], char exp[]) {
  SqStackChar S;
  InitStack_Char(S);
  Push_Char(S, '#');
  
  char *p = exp;
  char ch = *p;
  int k = 0;
  char c;
  
  while (ch != '#' && ch != '\0') {
    if (ch == ' ' || ch == '\t') {
      ch = *++p;
      continue;
    }
    
    if (!OpMember(ch)) {
      suffix[k++] = ch;
      ch = *++p;
    } else if (ch == '(') {
      Push_Char(S, ch);
      ch = *++p;
    } else if (ch == ')') {
      Pop_Char(S, c);
      while (c != '(') {
        suffix[k++] = c;
        Pop_Char(S, c);
      }
      ch = *++p;
    } else {
      GetTop_Char(S, c);
      while (c != '#' && precede(c, ch)) {
        suffix[k++] = c;
        Pop_Char(S, c);
        GetTop_Char(S, c);
      }
      Push_Char(S, ch);
      ch = *++p;
    }
  }
  
  while (Pop_Char(S, c) && c != '#') {
    suffix[k++] = c;
  }
  
  suffix[k] = '\0';
  DestroyStack_Char(S);
}

void test_evaluation() {
  cout << "=== Test Prefix Evaluation ===" << endl;
  
  char test1[] = "+ 3 4#";
  cout << "Test 1: \"" << test1 << "\" = " << evaluation(test1) << " (Expected: 7)" << endl;
  
  char test2[] = "*+3 4 5#";
  cout << "Test 2: \"" << test2 << "\" = " << evaluation(test2) << " (Expected: 35)" << endl;
  
  char test3[] = "-*+12 3 4 5#";
  cout << "Test 3: \"" << test3 << "\" = " << evaluation(test3) << " (Expected: 5, " << "因为从右向左扫描: +12=1+2=3, *33=3*3=9, -94=9-4=5)" << endl;
  
  char test4[] = "/ * + 1 2 3 3#";
  cout << "Test 4: \"" << test4 << "\" = " << evaluation(test4) << " (Expected: 3)" << endl;
  
  char test5[] = "+ * 2 3 / 8 4#";
  cout << "Test 5: \"" << test5 << "\" = " << evaluation(test5) << " (Expected: 8)" << endl;
}

void test_transform() {
  cout << "\n=== Test Transform (Infix to Postfix) ===" << endl;
  
  char suffix[100];
  
  char test1[] = "3+4#";
  transform(suffix, test1);
  cout << "Test 1: \"" << test1 << "\" -> \"" << suffix << "\" (Expected: 34+)" << endl;
  
  char test2[] = "3+4*5#";
  transform(suffix, test2);
  cout << "Test 2: \"" << test2 << "\" -> \"" << suffix << "\" (Expected: 345*+)" << endl;
  
  char test3[] = "(3+4)*5#";
  transform(suffix, test3);
  cout << "Test 3: \"" << test3 << "\" -> \"" << suffix << "\" (Expected: 34+5*)" << endl;
  
  char test4[] = "a+b*c-d#";
  transform(suffix, test4);
  cout << "Test 4: \"" << test4 << "\" -> \"" << suffix << "\" (Expected: abc*+d-)" << endl;
  
  char test5[] = "((a+b)*c-d)/e#";
  transform(suffix, test5);
  cout << "Test 5: \"" << test5 << "\" -> \"" << suffix << "\" (Expected: ab+c*d-e/)" << endl;
}

int main() {
  test_evaluation();
  test_transform();
  return 0;
}
