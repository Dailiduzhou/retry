#include <iostream>

using namespace std;

// 判断是否为闰年
bool isLeapYear(int year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int main() {
  // 初始日期：2000年1月1日
  int year = 2000;
  int month = 1;
  int day = 1;
  int weekday = 6; // 已知2000年1月1日是周六

  int total_km = 0;

  // 预存平年每个月的天数（下标0留空，方便用1-12对应月份）
  int days_in_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  while (true) {
    // 判断当天跑量：月初1号或周一跑2千米，其他情况跑1千米
    // (注意：题目中说既是周一又是月初也只跑2千米，所以用逻辑或 || 即可满足)
    if (day == 1 || weekday == 1) {
      total_km += 2;
    } else {
      total_km += 1;
    }

    // 终止条件：当天算完后，如果是2020年10月1日则退出循环
    if (year == 2020 && month == 10 && day == 1) {
      break;
    }

    // 获取当前月份应该有的天数（处理闰年2月）
    int current_month_days = days_in_month[month];
    if (month == 2 && isLeapYear(year)) {
      current_month_days = 29;
    }

    // 日期往前推一天
    day++;
    weekday++;

    // 星期循环计算（7之后回到1）
    if (weekday == 8) {
      weekday = 1;
    }

    // 跨月处理
    if (day > current_month_days) {
      day = 1; // 回到1号
      month++; // 月份加1

      // 跨年处理
      if (month > 12) {
        month = 1; // 回到1月
        year++;    // 年份加1
      }
    }
  }

  cout << total_km << endl;

  return 0;
}
