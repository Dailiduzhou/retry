#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

using namespace std;

class Clock {
public:
  Clock(int H = 0, int M = 0, int S = 0) {
    this->H = H;
    this->M = M;
    this->S = S;
  }

  void setTime(int H = 0, int M = 0, int S = 0) {
    this->H = H;
    this->M = M;
    this->S = S;
  }

  void ShowTime() const {
    cout << setw(2) << setfill('0') << H << ":" << setw(2) << M << ":"
         << setw(2) << S << endl;
  }

private:
  int H;
  int M;
  int S;
};

// 闹钟类
class AlarmClock : public Clock {
private:
  static const int MAX_ALARMS = 10; // 最多允许设置的闹铃个数

  struct Alarm {
    int hour;
    int minute;
    int second;
    string name;
    bool active;

    Alarm() : hour(0), minute(0), second(0), name(""), active(false) {}

    Alarm(int h, int m, int s, const string &n)
        : hour(h), minute(m), second(s), name(n), active(true) {}
  };

  vector<Alarm> alarms;
  int startHour;
  int startMinute;
  int startSecond;

  // 判断时间是否合法
  static bool isValidTime(int h, int m, int s) {
    return h >= 0 && h <= 23 && m >= 0 && m <= 59 && s >= 0 && s <= 59;
  }

  // 以下三个函数用于在基类构造前校验参数，非法则抛出异常
  static int checkHour(int h) {
    if (h < 0 || h > 23)
      throw invalid_argument("小时必须在 0~23 之间");
    return h;
  }

  static int checkMinute(int m) {
    if (m < 0 || m > 59)
      throw invalid_argument("分钟必须在 0~59 之间");
    return m;
  }

  static int checkSecond(int s) {
    if (s < 0 || s > 59)
      throw invalid_argument("秒必须在 0~59 之间");
    return s;
  }

public:
  // 构造函数：初始时间也要校验
  AlarmClock(int h = 0, int m = 0, int s = 0)
      : Clock(checkHour(h), checkMinute(m), checkSecond(s)) {
    startHour = h;
    startMinute = m;
    startSecond = s;
  }

  // 设置闹铃：id 从 1 开始，例如 1、2、3……
  void setAlarm(int id, int h, int m, int s, const string &name) {
    // 校验闹铃编号
    if (id < 1 || id > MAX_ALARMS) {
      throw invalid_argument("闹铃编号必须在 1~" + to_string(MAX_ALARMS) +
                             " 之间");
    }

    // 校验闹铃时间
    if (!isValidTime(h, m, s)) {
      throw invalid_argument("闹铃时间不合法：小时 0~23，分钟 0~59，秒 0~59");
    }

    // 校验闹铃名称
    if (name.empty()) {
      throw invalid_argument("闹铃名称不能为空");
    }

    if ((int)alarms.size() < id) {
      alarms.resize(id);
    }

    alarms[id - 1] = Alarm(h, m, s, name);
    cout << "闹钟 # " << id << endl
         << "闹钟名: " << name << " 已设置" << "(时间:" << h << " 时 " << m
         << " 分 " << s << " 秒" << ')' << endl;
  }

  // 启动闹钟
  void run() {
    time_t start = time(nullptr); // 记录开始时的系统时间

    while (true) {
      time_t now = time(nullptr);
      long elapsed = (long)(now - start); // 已经过去的秒数

      // 从构造时设定的时间开始，按系统时间流逝推进
      long total =
          startHour * 3600L + startMinute * 60L + startSecond + elapsed;
      total %= 24 * 3600L;
      if (total < 0)
        total += 24 * 3600L;

      int h = (int)(total / 3600);
      int m = (int)((total % 3600) / 60);
      int s = (int)(total % 60);

      // 更新 Clock 并显示时间
      Clock::setTime(h, m, s);
      Clock::ShowTime();

      // 检查所有闹铃
      for (size_t i = 0; i < alarms.size(); ++i) {
        if (alarms[i].active && alarms[i].hour == h && alarms[i].minute == m &&
            alarms[i].second == s) {
          cout << alarms[i].name << endl;
          // 如果希望同一个闹铃只响一次，取消下面注释
          // alarms[i].active = false;
        }
      }

      // 睡眠等待系统时间进入下一秒（避免空转占用 CPU）
      do {
        this_thread::sleep_for(chrono::milliseconds(50));
      } while (time(nullptr) == now);
    }
  }
};

int main() {
  try {
    AlarmClock myClock(6, 59, 58);

    myClock.setAlarm(1, 7, 0, 0, "起床");
    myClock.setAlarm(2, 7, 0, 10, "开手机");
    myClock.setAlarm(3, 7, 0, 30, "刷牙");

    // myClock.setAlarm(3, 25, 0, 0, "错误小时");
    // myClock.setAlarm(4, 7, 70, 0, "错误分钟");
    // myClock.setAlarm(0, 7, 0, 0, "错误编号");
    // myClock.setAlarm(5, 7, 0, 0, "");

    myClock.run();
  } catch (const exception &e) {
    cerr << "参数错误：" << e.what() << endl;
  }

  return 0;
}
