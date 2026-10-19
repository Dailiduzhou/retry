#include <iostream>
using namespace std;

// 每个类的 count 统计本类及其派生类中当前存活的对象数。
// 派生类构造时会自动调用基类构造，析构时则按相反顺序调用。
class Vehicle {
private:
  static int count;
  int power;

public:
  explicit Vehicle(int power = 0) : power(power) { ++count; }

  // 拷贝也会产生新对象，必须单独增加计数。
  Vehicle(const Vehicle &other) : power(other.power) { ++count; }

  // 虚析构保证通过 Vehicle 指针删除派生类对象时正确更新全部计数。
  virtual ~Vehicle() { --count; }

  // 赋值不会产生新对象，因此不改变计数。
  Vehicle &operator=(const Vehicle &) = default;

  static int getCount() { return count; }
  void show() const { cout << "  power:" << power << endl; }
};

class Fuel : public Vehicle {
private:
  static int count;
  int fuel_tank;

public:
  explicit Fuel(int power = 0, int fuel_tank = 0)
      : Vehicle(power), fuel_tank(fuel_tank) {
    ++count;
  }

  Fuel(const Fuel &other) : Vehicle(other), fuel_tank(other.fuel_tank) {
    ++count;
  }

  ~Fuel() override { --count; }
  Fuel &operator=(const Fuel &) = default;

  static int getCount() { return count; }
};

class NewEnergy : public Vehicle {
private:
  static int count;

public:
  explicit NewEnergy(int power = 0) : Vehicle(power) { ++count; }
  NewEnergy(const NewEnergy &other) : Vehicle(other) { ++count; }
  ~NewEnergy() override { --count; }
  NewEnergy &operator=(const NewEnergy &) = default;

  static int getCount() { return count; }
};

class Electric : public NewEnergy {
private:
  static int count;

public:
  explicit Electric(int power = 0) : NewEnergy(power) { ++count; }
  Electric(const Electric &other) : NewEnergy(other) { ++count; }
  ~Electric() override { --count; }
  Electric &operator=(const Electric &) = default;

  static int getCount() { return count; }
};

class Hybrid : public NewEnergy {
private:
  static int count;

public:
  explicit Hybrid(int power = 0) : NewEnergy(power) { ++count; }
  Hybrid(const Hybrid &other) : NewEnergy(other) { ++count; }
  ~Hybrid() override { --count; }
  Hybrid &operator=(const Hybrid &) = default;

  static int getCount() { return count; }
};

// 静态成员属于类，由所有对象共享，需要在类外定义。
int Vehicle::count = 0;
int Fuel::count = 0;
int NewEnergy::count = 0;
int Electric::count = 0;
int Hybrid::count = 0;

void printCounts(const char *title) {
  cout << "\n" << title << "\n";
  cout << "类名\t\t类族对象数\t本类对象数\n";
  // 本类对象数不包含派生类对象，减去直接派生类的类族计数即可。
  cout << "Vehicle\t\t" << Vehicle::getCount() << "\t\t"
       << Vehicle::getCount() - Fuel::getCount() - NewEnergy::getCount()
       << '\n';
  cout << "Fuel\t\t" << Fuel::getCount() << "\t\t" << Fuel::getCount() << '\n';
  cout << "NewEnergy\t" << NewEnergy::getCount() << "\t\t"
       << NewEnergy::getCount() - Electric::getCount() - Hybrid::getCount()
       << '\n';
  cout << "Electric\t" << Electric::getCount() << "\t\t" << Electric::getCount()
       << '\n';
  cout << "Hybrid\t\t" << Hybrid::getCount() << "\t\t" << Hybrid::getCount()
       << '\n';
}

int main() {
  bool allPassed = true;
  printCounts("尚未创建对象");

  {
    Hybrid h1;                        // 普通对象
    Fuel fn[5], f2;                   // 栈上数组及普通对象
    Electric *en = new Electric[100]; // 堆上数组
    Hybrid h2 = h1;                   // 拷贝构造

    printCounts("题目示例：创建对象后");
    if (Vehicle::getCount() == 108 && Fuel::getCount() == 6 &&
        NewEnergy::getCount() == 102 && Electric::getCount() == 100 &&
        Hybrid::getCount() == 2) {
      cout << "验证通过\n";
    } else {
      cout << "验证失败：对象数量与预期不符\n";
      allPassed = false;
    }

    h2 = h1; // 赋值不是拷贝构造，不改变对象数量。
    cout << "\n赋值后检查对象数量：\n";
    if (Vehicle::getCount() == 108 && NewEnergy::getCount() == 102 &&
        Hybrid::getCount() == 2) {
      cout << "验证通过\n";
    } else {
      cout << "验证失败：对象数量与预期不符\n";
      allPassed = false;
    }

    delete[] en;
    en = nullptr;
    printCounts("删除动态数组后");
    if (Vehicle::getCount() == 8 && Fuel::getCount() == 6 &&
        NewEnergy::getCount() == 2 && Electric::getCount() == 0 &&
        Hybrid::getCount() == 2) {
      cout << "验证通过\n";
    } else {
      cout << "验证失败：对象数量与预期不符\n";
      allPassed = false;
    }
  } // 离开作用域，局部对象及栈上数组自动析构。

  printCounts("离开示例作用域后");
  if (Vehicle::getCount() == 0) {
    cout << "验证通过\n";
  } else {
    cout << "验证失败：对象数量与预期不符\n";
    allPassed = false;
  }

  {
    Vehicle v;                      // 直接创建基类对象
    NewEnergy ne;                   // 直接创建中间类对象
    Vehicle *car = new Hybrid(100); // 基类指针指向堆上的派生类对象

    printCounts("直接创建基类、中间类及单个动态对象后");
    if (Vehicle::getCount() == 3 && NewEnergy::getCount() == 2 &&
        Hybrid::getCount() == 1) {
      cout << "验证通过\n";
    } else {
      cout << "验证失败：对象数量与预期不符\n";
      allPassed = false;
    }

    delete car;
    car = nullptr;
    printCounts("通过基类指针删除动态对象后");
    if (Vehicle::getCount() == 2 && NewEnergy::getCount() == 1 &&
        Hybrid::getCount() == 0) {
      cout << "验证通过\n";
    } else {
      cout << "验证失败：对象数量与预期不符\n";
      allPassed = false;
    }
  }

  printCounts("全部对象销毁后");
  if (Vehicle::getCount() == 0 && Fuel::getCount() == 0 &&
      NewEnergy::getCount() == 0 && Electric::getCount() == 0 &&
      Hybrid::getCount() == 0) {
    cout << "验证通过\n";
  } else {
    cout << "验证失败：对象数量与预期不符\n";
    allPassed = false;
  }
  if (allPassed) {
    cout << "\n所有验证均通过。\n";
    return 0;
  } else {
    cout << "\n存在未通过的验证。\n";
    return 1;
  }
}
