#include <iostream>
using namespace std;

class Vehicle {
private:
    // private：外部和派生类都不能直接修改，防止破坏计数。
    static int count;
    int power; // 功率，单位：kW

public:
    // 带默认参数的构造函数，同时支持无参构造和带参构造。
    explicit Vehicle(int power = 0) : power(power) { ++count; }

    // 拷贝会产生新对象：只复制普通属性，不能复制静态计数。
    Vehicle(const Vehicle &other) : power(other.power) { ++count; }

    // 必须为虚析构：支持通过基类指针正确删除派生类对象。
    virtual ~Vehicle() { --count; }

    // 赋值只修改已有对象，默认赋值不会复制静态成员。
    Vehicle &operator=(const Vehicle &) = default;

    // public 静态函数无需对象即可调用，只读访问 private 计数。
    static int getCount() { return count; }

    int getPower() const { return power; }
    void show() const { cout << "power: " << power << '\n'; }
};

// public 继承表示“Fuel 是一种 Vehicle”，允许向上转型。
// 本题没有菱形继承，不需要虚继承。
class Fuel : public Vehicle {
private:
    static int count;
    int fuelTank; // 油箱容量，单位：L

public:
    explicit Fuel(int power = 0, int fuelTank = 0)
        : Vehicle(power), fuelTank(fuelTank) {
        ++count;
    }

    Fuel(const Fuel &other) : Vehicle(other), fuelTank(other.fuelTank) {
        ++count;
    }

    ~Fuel() override { --count; }
    Fuel &operator=(const Fuel &) = default;

    static int getCount() { return count; }
    int getFuelTank() const { return fuelTank; }
};

class NewEnergy : public Vehicle {
private:
    static int count;
    // 本题的新能源分支均带电池，共同属性放在中间基类中。
    int batteryCapacity; // 电池容量，单位：kWh

public:
    explicit NewEnergy(int power = 0, int batteryCapacity = 0)
        : Vehicle(power), batteryCapacity(batteryCapacity) {
        ++count;
    }
    NewEnergy(const NewEnergy &other)
        : Vehicle(other), batteryCapacity(other.batteryCapacity) {
        ++count;
    }
    ~NewEnergy() override { --count; }
    NewEnergy &operator=(const NewEnergy &) = default;

    static int getCount() { return count; }
    int getBatteryCapacity() const { return batteryCapacity; }
};

class Electric : public NewEnergy {
private:
    static int count;

public:
    // Electric 继承电池属性，不重复声明，也不需要油箱属性。
    explicit Electric(int power = 0, int batteryCapacity = 0)
        : NewEnergy(power, batteryCapacity) {
        ++count;
    }
    Electric(const Electric &other) : NewEnergy(other) { ++count; }
    ~Electric() override { --count; }
    Electric &operator=(const Electric &) = default;

    static int getCount() { return count; }
};

class Hybrid : public NewEnergy {
private:
    static int count;
    // 电池继承自 NewEnergy；混合动力车另外具有油箱。
    int fuelTank; // 油箱容量，单位：L

public:
    explicit Hybrid(int power = 0, int batteryCapacity = 0, int fuelTank = 0)
        : NewEnergy(power, batteryCapacity), fuelTank(fuelTank) {
        ++count;
    }
    Hybrid(const Hybrid &other) : NewEnergy(other), fuelTank(other.fuelTank) {
        ++count;
    }
    ~Hybrid() override { --count; }
    Hybrid &operator=(const Hybrid &) = default;

    static int getCount() { return count; }
    int getFuelTank() const { return fuelTank; }
};

// 静态成员由同一类的全部对象共享，在类外定义一次。
int Vehicle::count = 0;
int Fuel::count = 0;
int NewEnergy::count = 0;
int Electric::count = 0;
int Hybrid::count = 0;

void printCounts() {
    cout << "类名\t\t类族对象数\t本类对象数\n";
    // 本类计数 = 本类族计数 - 各直接派生类的类族计数。
    // 该公式适用于本题的单继承树；增加派生类时也需更新公式。
    cout << "Vehicle\t\t" << Vehicle::getCount() << "\t\t"
         << Vehicle::getCount() - Fuel::getCount() - NewEnergy::getCount()
         << '\n';
    cout << "Fuel\t\t" << Fuel::getCount() << "\t\t" << Fuel::getCount()
         << '\n';
    cout << "NewEnergy\t" << NewEnergy::getCount() << "\t\t"
         << NewEnergy::getCount() - Electric::getCount() - Hybrid::getCount()
         << '\n';
    cout << "Electric\t" << Electric::getCount() << "\t\t"
         << Electric::getCount() << '\n';
    cout << "Hybrid\t\t" << Hybrid::getCount() << "\t\t" << Hybrid::getCount()
         << '\n';
}

// 使用 if 验证，不使用 assert。失败后仍继续测试和释放动态对象。
void check(bool condition, const char *message, bool &allPassed) {
    if (condition) {
        cout << "[通过] " << message << '\n';
    } else {
        cout << "[失败] " << message << '\n';
        allPassed = false;
    }
}

// 统一检查五个类族，避免只验证总数而遗漏某个派生类。
void checkCounts(const char *title, int vehicle, int fuel, int newEnergy,
                 int electric, int hybrid, bool &allPassed) {
    cout << "\n--- " << title << " ---\n";
    printCounts();
    bool correct = Vehicle::getCount() == vehicle && Fuel::getCount() == fuel &&
                   NewEnergy::getCount() == newEnergy &&
                   Electric::getCount() == electric &&
                   Hybrid::getCount() == hybrid;
    check(correct, "五个类族的计数符合预期", allPassed);
    if (!correct) {
        cout << "预期（Vehicle/Fuel/NewEnergy/Electric/Hybrid）：" << vehicle
             << '/' << fuel << '/' << newEnergy << '/' << electric << '/'
             << hybrid << '\n';
    }
}

int main() {
    bool allPassed = true;
    checkCounts("尚未创建对象", 0, 0, 0, 0, 0, allPassed);

    // 示例一：普通对象、数组、拷贝构造、赋值及动态数组释放。
    {
        Hybrid h1(180, 25, 45);
        Fuel fn[5], f2;
        Electric *en = new Electric[100];
        Hybrid h2 = h1; // 创建新对象，调用拷贝构造。
        checkCounts("题目示例：创建后", 108, 6, 102, 100, 2, allPassed);
        check(h2.getPower() == 180 && h2.getBatteryCapacity() == 25 &&
                  h2.getFuelTank() == 45,
              "拷贝构造保留功率、电池和油箱属性", allPassed);

        h2 = h1; // 已有对象之间赋值，不调用拷贝构造。
        checkCounts("赋值不增加对象数", 108, 6, 102, 100, 2, allPassed);

        delete[] en; // new[] 必须与 delete[] 配对。
        en = nullptr;
        checkCounts("删除动态数组后", 8, 6, 2, 0, 2, allPassed);
    } // 局部对象和数组自动析构。
    checkCounts("离开示例一的作用域后", 0, 0, 0, 0, 0, allPassed);

    // 示例二：各类直接构造、拷贝，以及通过基类指针删除派生类对象。
    {
        Vehicle v(80);
        Fuel f(100, 50);
        NewEnergy n(120, 40);
        Electric e(160, 75);
        Hybrid h(180, 25, 45);
        checkCounts("每个类各创建一个对象", 5, 1, 3, 1, 1, allPassed);

        Vehicle vCopy(v);
        Fuel fCopy(f);
        NewEnergy nCopy(n);
        Electric eCopy(e);
        Hybrid hCopy(h);
        checkCounts("各类分别拷贝一个对象", 10, 2, 6, 2, 2, allPassed);
        check(vCopy.getPower() == 80 && fCopy.getPower() == 100 &&
                  fCopy.getFuelTank() == 50 && nCopy.getPower() == 120 &&
                  nCopy.getBatteryCapacity() == 40 && eCopy.getPower() == 160 &&
                  eCopy.getBatteryCapacity() == 75 && hCopy.getPower() == 180 &&
                  hCopy.getBatteryCapacity() == 25 && hCopy.getFuelTank() == 45,
              "五个类的拷贝均正确保留属性", allPassed);

        Vehicle *car = new Hybrid(200, 30, 50);
        checkCounts("新增一个动态 Hybrid", 11, 2, 7, 2, 3, allPassed);
        delete car; // 虚析构：依次调用 Hybrid、NewEnergy、Vehicle 的析构。
        car = nullptr;
        checkCounts("通过基类指针删除后", 10, 2, 6, 2, 2, allPassed);
    }
    checkCounts("全部对象销毁后", 0, 0, 0, 0, 0, allPassed);

    // 反面案例（仅作说明，不执行错误代码）：
    // Vehicle::count = 100;  // 编译错误：静态计数是 private。
    // h.batteryCapacity = 60; // 在 h 的作用域内也不可直接访问 private 属性。
    // 拷贝构造若遗漏 ++count，会导致创建时少计数、析构时仍减一。
    // 派生类拷贝若遗漏基类拷贝或自身属性初始化，属性不能正确复制。
    // new Electric[3] 后使用 delete 而非 delete[]：未定义行为。
    // delete 局部对象地址、重复 delete 同一非空指针：未定义行为。
    // 基类析构若不是 virtual，通过基类指针删除派生类对象：未定义行为。
    // Hybrid 虽然有油箱，但不继承 Fuel，因此不计入 Fuel 类族。

    if (allPassed) {
        cout << "\n所有验证均通过。\n";
        return 0;
    } else {
        cout << "\n存在未通过的验证。\n";
        return 1;
    }
}
