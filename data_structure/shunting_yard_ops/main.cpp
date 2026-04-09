// 双栈法计算
// 直接计算中缀表达式
// 事实上隐式地把中缀转换为后缀

#include <cctype>
#include <iostream>
#include <map>
#include <stack>
#include <stdexcept>
#include <string>

class InfixEvaluator {
private:
  // 运算符优先级映射
  std::map<char, int> precedence = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

  std::stack<double> nums; // 操作数栈
  std::stack<char> ops;    // 运算符栈（含括号）

  // 执行一次运算：弹出栈顶运算符和两个操作数，计算并压回结果
  void applyOp() {
    if (ops.empty())
      throw std::runtime_error("运算符栈为空，无法计算");
    char op = ops.top();
    ops.pop();

    if (nums.size() < 2)
      throw std::runtime_error("操作数不足，无法计算");
    double b = nums.top();
    nums.pop();
    double a = nums.top();
    nums.pop();

    double result = 0.0;
    switch (op) {
    case '+':
      result = a + b;
      break;
    case '-':
      result = a - b;
      break;
    case '*':
      result = a * b;
      break;
    case '/':
      if (b == 0.0)
        throw std::runtime_error("除数不能为零");
      result = a / b;
      break;
    default:
      throw std::runtime_error(std::string("未知运算符: ") + op);
    }
    nums.push(result);
  }

public:
  double evaluate(const std::string &expression) {
    // 清空栈，确保多次调用互不影响
    while (!nums.empty())
      nums.pop();
    while (!ops.empty())
      ops.pop();

    size_t i = 0;
    const size_t n = expression.length();

    while (i < n) {
      char ch = expression[i];

      // 跳过空白字符
      if (std::isspace(static_cast<unsigned char>(ch))) {
        ++i;
        continue;
      }

      // 1. 数字（整数或浮点数）
      if (std::isdigit(static_cast<unsigned char>(ch)) || ch == '.') {
        size_t j = i;
        while (j < n &&
               (std::isdigit(static_cast<unsigned char>(expression[j])) ||
                expression[j] == '.')) {
          ++j;
        }
        std::string numStr = expression.substr(i, j - i);
        double val = std::stod(numStr);
        nums.push(val);
        i = j;
        continue;
      }

      // 2. 左括号
      if (ch == '(') {
        ops.push(ch);
      }
      // 3. 右括号：强制计算直到遇到左括号
      else if (ch == ')') {
        while (!ops.empty() && ops.top() != '(') {
          applyOp();
        }
        if (ops.empty()) {
          throw std::runtime_error("括号不匹配：缺少 '('");
        }
        ops.pop(); // 弹出 '('
      }
      // 4. 运算符 + - * /
      else if (precedence.find(ch) != precedence.end()) {
        // 只要栈顶运算符优先级 >= 当前运算符，就立即计算（保证左结合性）
        while (!ops.empty() && ops.top() != '(' &&
               precedence[ops.top()] >= precedence[ch]) {
          applyOp();
        }
        ops.push(ch);
      } else {
        throw std::runtime_error(std::string("非法字符: ") + ch);
      }

      ++i;
    }

    // 5. 表达式扫描完毕，处理栈中剩余运算符
    while (!ops.empty()) {
      if (ops.top() == '(') {
        throw std::runtime_error("括号不匹配：多余的 '('");
      }
      applyOp();
    }

    // 数字栈应当只剩一个结果
    if (nums.size() != 1) {
      throw std::runtime_error("表达式错误：操作数数量不正确");
    }
    return nums.top();
  }
};

// ========== 测试 ==========
int main() {
  InfixEvaluator evaluator;
  std::string testCases[] = {"1 + 2 * 3 - ( 4 + 5 )", "3 + 4 * 2 / ( 1 - 5 )",
                             "2.5 * 4 + 1",           "10 / 3",
                             "(1+2)*(3+4)",           "100 - 99 + 1"};

  for (const auto &expr : testCases) {
    try {
      double result = evaluator.evaluate(expr);
      std::cout << expr << " = " << result << std::endl;
    } catch (const std::exception &e) {
      std::cout << expr << " -> 错误: " << e.what() << std::endl;
    }
  }

  return 0;
}
