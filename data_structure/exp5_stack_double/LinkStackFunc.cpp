#include "stack_char.h"
#include "stack_double.h"
#include <cctype>
#include <cmath>
#include <iostream>

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

double evaluation(char postfix[]) {
  SqStackDouble S;
  InitStack_Double(S);

  char *p = postfix;
  char ch = *p;

  // 从左向右扫描后缀表达式
  while (ch != '\0') {
    if (ch == ' ' || ch == '\t') {
      ch = *++p;
      continue;
    }

    if (isdigit(ch)) {
      // 读取完整的数字（多位数）
      double num = 0;
      while (isdigit(ch)) {
        num = num * 10 + (ch - '0');
        ch = *++p;
      }
      Push_Double(S, num);
    } else if (OpMember(ch) && ch != '#' && ch != '(' && ch != ')') {
      // 运算符：弹出两个操作数，计算后入栈
      SElemTypeDouble b, a;
      if (Pop_Double(S, b) && Pop_Double(S, a)) {
        Push_Double(S, Operate(a, ch, b));
      }
      ch = *++p;
    } else {
      // 非法字符，跳过
      ch = *++p;
    }
  }

  SElemTypeDouble result = 0;
  Pop_Double(S, result);
  DestroyStack_Double(S);

  return result;
}

bool transform(char suffix[], char exp[]) {
  SqStackChar S;
  InitStack_Char(S);

  char *p = exp;
  char ch = *p;
  int k = 0;
  char c;
  int leftParenCount = 0;    // 左括号计数
  bool expectOperand = true; // 判断连续操作数

  while (ch != '\0') {
    if (ch == ' ' || ch == '\t') {
      ch = *++p;
      continue;
    }

    if (!OpMember(ch) && !isdigit(ch) && !isalpha(ch)) {
      DestroyStack_Char(S);
      return false;
    }

    if (isdigit(ch)) {
      if (!expectOperand) {
        DestroyStack_Char(S);
        return false;
      }
      while (isdigit(ch)) {
        suffix[k++] = ch;
        ch = *++p;
      }
      suffix[k++] = ' ';
      expectOperand = false;
    } else if (ch == '(') {
      Push_Char(S, ch);
      leftParenCount++;
      ch = *++p;
    } else if (ch == ')') {
      if (leftParenCount <= 0 || expectOperand) {
        DestroyStack_Char(S);
        return false;
      }
      leftParenCount--;
      if (!Pop_Char(S, c)) {
        DestroyStack_Char(S);
        return false; // 栈为空，括号不匹配
      }
      while (c != '(') {
        suffix[k++] = c;
        suffix[k++] = ' ';
        if (!Pop_Char(S, c)) {
          DestroyStack_Char(S);
          return false; // 栈为空，括号不匹配
        }
      }
      ch = *++p;
    } else if (OpMember(ch) && ch != '(' && ch != ')') {
      // 运算符 + - * /
      if (expectOperand) {
        DestroyStack_Char(S);
        return false; // 运算符前面缺少操作数
      }
      while (!StackEmpty_Char(S)) {
        GetTop_Char(S, c);
        if (c == '(' || !precede(c, ch)) {
          break;
        }
        suffix[k++] = c;
        suffix[k++] = ' '; // 运算符后加空格
        Pop_Char(S, c);
      }
      Push_Char(S, ch);
      ch = *++p;
      expectOperand = true;
    } else {
      DestroyStack_Char(S);
      return false;
    }
  }

  // 检查括号是否全部匹配，并且表达式以操作数结尾
  if (leftParenCount != 0 || expectOperand) {
    DestroyStack_Char(S);
    return false;
  }

  // 弹出栈中剩余的所有运算符
  while (Pop_Char(S, c)) {
    if (c == '(' || c == ')') {
      DestroyStack_Char(S);
      return false; // 还有未匹配的括号
    }
    suffix[k++] = c;
    suffix[k++] = ' '; // 运算符后加空格
  }

  if (k > 0 && suffix[k - 1] == ' ') {
    k--;
  }

  suffix[k] = '\0';
  DestroyStack_Char(S);
  return true;
}

void test_transform_and_evaluate() {

  char suffix[100];
  bool result;
  double value;

  // 基本测试（带空格分隔）
  char test1[] = "3 + 4";
  result = transform(suffix, test1);
  value = evaluation(suffix);
  cout << "Test 1: \"" << test1 << "\" -> \"" << suffix << "\" = " << value
       << (result && value == 7 ? " (Success, Expected: 7)" : " (Failed)")
       << endl;

  char test2[] = "3 + 4 * 5";
  result = transform(suffix, test2);
  value = evaluation(suffix);
  cout << "Test 2: \"" << test2 << "\" -> \"" << suffix << "\" = " << value
       << (result && value == 23 ? " (Success, Expected: 23)" : " (Failed)")
       << endl;

  char test3[] = "( 3 + 4 ) * 5";
  result = transform(suffix, test3);
  value = evaluation(suffix);
  cout << "Test 3: \"" << test3 << "\" -> \"" << suffix << "\" = " << value
       << (result && value == 35 ? " (Success, Expected: 35)" : " (Failed)")
       << endl;

  // 多位数测试
  char test4[] = "12 + 34";
  result = transform(suffix, test4);
  value = evaluation(suffix);
  cout << "Test 4: \"" << test4 << "\" -> \"" << suffix << "\" = " << value
       << (result && value == 46 ? " (Success, Expected: 46)" : " (Failed)")
       << endl;

  char test5[] = "123 + 456 * 7";
  result = transform(suffix, test5);
  value = evaluation(suffix);
  cout << "Test 5: \"" << test5 << "\" -> \"" << suffix << "\" = " << value
       << (result && value == 3315 ? " (Success, Expected: 3315)" : " (Failed)")
       << endl;

  char test6[] = "( 10 + 20 ) * ( 3 + 4 )";
  result = transform(suffix, test6);
  value = evaluation(suffix);
  cout << "Test 6: \"" << test6 << "\" -> \"" << suffix << "\" = " << value
       << (result && value == 210 ? " (Success, Expected: 210)" : " (Failed)")
       << endl;

  char test7[] = "100 - 50 / 5";
  result = transform(suffix, test7);
  value = evaluation(suffix);
  cout << "Test 7: \"" << test7 << "\" -> \"" << suffix << "\" = " << value
       << (result && value == 90 ? " (Success, Expected: 90)" : " (Failed)")
       << endl;

  char test8[] = "(( 1 + 2 ) * 3 - 4 ) / 5";
  result = transform(suffix, test8);
  value = evaluation(suffix);
  cout << "Test 8: \"" << test8 << "\" -> \"" << suffix << "\" = " << value
       << (result && value == 1 ? " (Success, Expected: 1)" : " (Failed)")
       << endl;

  // 测试非法表达式
  cout << "\n=== Test Invalid Expressions ===" << endl;

  char test9[] = "( 3 + 4"; // 缺少右括号
  result = transform(suffix, test9);
  cout << "Test 9: \"" << test9 << "\" -> "
       << (result ? "Success" : "Failed (Expected: Failed)") << endl;

  char test10[] = "3 + 4 )"; // 多余的右括号
  result = transform(suffix, test10);
  cout << "Test 10: \"" << test10 << "\" -> "
       << (result ? "Success" : "Failed (Expected: Failed)") << endl;

  char test11[] = "3 & 4"; // 非法字符
  result = transform(suffix, test11);
  cout << "Test 11: \"" << test11 << "\" -> "
       << (result ? "Success" : "Failed (Expected: Failed)") << endl;

  char test12[] = "3 + + 4"; // 连续两个运算符
  result = transform(suffix, test12);
  cout << "Test 12: \"" << test12 << "\" -> "
       << (result ? "Success" : "Failed (Expected: Failed)") << endl;

  char test13[] = "3 4 + 5"; // 连续两个操作数
  result = transform(suffix, test13);
  cout << "Test 13: \"" << test13 << "\" -> "
       << (result ? "Success" : "Failed (Expected: Failed)") << endl;
}

void test_transform() {
  cout << "\n=== Test Transform (Infix to Postfix) ===" << endl;

  char suffix[100];
  bool result;

  // 基本测试（带空格分隔）
  char test1[] = "3 + 4";
  result = transform(suffix, test1);
  cout << "Test 1: \"" << test1 << "\" -> \"" << suffix << "\" "
       << (result ? "(Success, Expected: 3 4 +)" : "(Failed)") << endl;

  char test2[] = "3 + 4 * 5";
  result = transform(suffix, test2);
  cout << "Test 2: \"" << test2 << "\" -> \"" << suffix << "\" "
       << (result ? "(Success, Expected: 3 4 5 * +)" : "(Failed)") << endl;

  char test3[] = "( 3 + 4 ) * 5";
  result = transform(suffix, test3);
  cout << "Test 3: \"" << test3 << "\" -> \"" << suffix << "\" "
       << (result ? "(Success, Expected: 3 4 + 5 *)" : "(Failed)") << endl;

  // 多位数测试
  char test4[] = "12 + 34";
  result = transform(suffix, test4);
  cout << "Test 4: \"" << test4 << "\" -> \"" << suffix << "\" "
       << (result ? "(Success, Expected: 12 34 +)" : "(Failed)") << endl;

  char test5[] = "123 + 456 * 7";
  result = transform(suffix, test5);
  cout << "Test 5: \"" << test5 << "\" -> \"" << suffix << "\" "
       << (result ? "(Success, Expected: 123 456 7 * +)" : "(Failed)") << endl;

  char test6[] = "( 10 + 20 ) * ( 3 + 4 )";
  result = transform(suffix, test6);
  cout << "Test 6: \"" << test6 << "\" -> \"" << suffix << "\" "
       << (result ? "(Success, Expected: 10 20 + 3 4 + *)" : "(Failed)")
       << endl;

  char test7[] = "100 - 50 / 5";
  result = transform(suffix, test7);
  cout << "Test 7: \"" << test7 << "\" -> \"" << suffix << "\" "
       << (result ? "(Success, Expected: 100 50 5 / -)" : "(Failed)") << endl;

  char test8[] = "(( 1 + 2 ) * 3 - 4 ) / 5";
  result = transform(suffix, test8);
  cout << "Test 8: \"" << test8 << "\" -> \"" << suffix << "\" "
       << (result ? "(Success, Expected: 1 2 + 3 * 4 - 5 /)" : "(Failed)")
       << endl;

  // 测试非法表达式
  cout << "\n=== Test Invalid Expressions ===" << endl;

  char test9[] = "( 3 + 4"; // 缺少右括号
  result = transform(suffix, test9);
  cout << "Test 9: \"" << test9 << "\" -> "
       << (result ? "Success" : "Failed (Expected: Failed)") << endl;

  char test10[] = "3 + 4 )"; // 多余的右括号
  result = transform(suffix, test10);
  cout << "Test 10: \"" << test10 << "\" -> "
       << (result ? "Success" : "Failed (Expected: Failed)") << endl;

  char test11[] = "3 & 4"; // 非法字符
  result = transform(suffix, test11);
  cout << "Test 11: \"" << test11 << "\" -> "
       << (result ? "Success" : "Failed (Expected: Failed)") << endl;

  char test12[] = "3 + + 4"; // 连续两个运算符
  result = transform(suffix, test12);
  cout << "Test 12: \"" << test12 << "\" -> "
       << (result ? "Success" : "Failed (Expected: Failed)") << endl;

  char test13[] = "3 4 + 5"; // 连续两个操作数
  result = transform(suffix, test13);
  cout << "Test 13: \"" << test13 << "\" -> "
       << (result ? "Success" : "Failed (Expected: Failed)") << endl;
}

int main() {
  test_transform_and_evaluate();
  return 0;
}
