#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

constexpr double Pi = 3.14159265358979323846;

class Point {
      public:
        Point() : x_(0.0), y_(0.0) {}
        Point(double x, double y) : x_(x), y_(y) {}

        // 获取位置
        double getX() const { return x_; }
        double getY() const { return y_; }

      private:
        double x_;
        double y_;
};

// Shape 是抽象类
class Shape {
      public:
        virtual ~Shape() {}

        // 计算面积
        virtual double area() const = 0;
        // 获取形状的名字
        virtual std::string getName() const = 0;
};

class Circle : public Shape {
      public:
        Circle(double radius) : center_(), radius_(radius) {}

        Circle(const Point &center, double radius)
                : center_(center), radius_(radius) {}

        // override 关键字表示显式重写抽象类的方法
        double area() const override { return Pi * radius_ * radius_; }

        std::string getName() const override { return "圆形"; }

        double getRadius() const { return radius_; }
        const Point &getCenter() const { return center_; }

      private:
        Point center_;
        double radius_;
};

class Rectangle : public Shape {
      public:
        Rectangle(double width, double height)
                : width_(width), height_(height) {}

        double area() const override { return width_ * height_; }

        std::string getName() const override { return "矩形"; }

        double getWidth() const { return width_; }
        double getHeight() const { return height_; }

      private:
        double width_;
        double height_;
};

// Cone 表示锥体，底面通过引用绑定到一个 Shape 对象
// Cone 是虚基类
class Cone {
      public:
        Cone(Shape &base, double height) : base_(base), height_(height) {}

        // 计算体积
        double Volume() const { return base_.area() * height_ / 3.0; }

        // 获取底面
        Shape &getBase() const { return base_; }
        double getHeight() const { return height_; }

        // 手动拼接输出
        void print() const {
                std::cout << "底面为" << base_.getName() << "，底面积 "
                          << base_.area() << "，高 " << height_ << "，体积 "
                          << Volume() << '\n';
        }

      private:
        // base 是底面，使用引用防止拷贝
        Shape &base_;
        double height_;
};

int main() {
        // 设置定点表示，保留小数点后 4 位
        std::cout << std::fixed << std::setprecision(4);

        // 构造圆
        Circle circleA(3.0);
        Circle circleB(Point(1.0, 2.0), 1.5);
        Circle circleC(0.5);

        // 构造矩形
        Rectangle rectA(4.0, 6.0);
        Rectangle rectB(5.0, 5.0);
        Rectangle rectC(2.5, 1.5);
        Rectangle rectD(10.0, 0.5);

        // 构造圆锥
        Cone coneA(circleA, 5.0);
        Cone coneB(circleB, 10.0);
        Cone coneC(circleC, 2.0);

        // 构造四棱椎体
        Cone pyramidA(rectA, 9.0);
        Cone pyramidB(rectB, 3.0);
        Cone pyramidC(rectC, 6.0);
        Cone pyramidD(rectD, 1.2);

        std::cout << "圆锥一：半径 " << circleA.getRadius() << "，高 "
                  << coneA.getHeight() << '\n';
        coneA.print();

        std::cout << "圆锥二：半径 " << circleB.getRadius() << "，圆心 ("
                  << circleB.getCenter().getX() << ", "
                  << circleB.getCenter().getY() << ")，高 " << coneB.getHeight()
                  << '\n';
        coneB.print();

        std::cout << "圆锥三：半径 " << circleC.getRadius() << "，高 "
                  << coneC.getHeight() << '\n';
        coneC.print();

        std::cout << "四棱锥一：底面 " << rectA.getWidth() << " x "
                  << rectA.getHeight() << "，高 " << pyramidA.getHeight()
                  << '\n';
        pyramidA.print();

        std::cout << "四棱锥二（正方底）：底面 " << rectB.getWidth() << " x "
                  << rectB.getHeight() << "，高 " << pyramidB.getHeight()
                  << '\n';
        pyramidB.print();

        std::cout << "四棱锥三：底面 " << rectC.getWidth() << " x "
                  << rectC.getHeight() << "，高 " << pyramidC.getHeight()
                  << '\n';
        pyramidC.print();

        std::cout << "四棱锥四（薄底）：底面 " << rectD.getWidth() << " x "
                  << rectD.getHeight() << "，高 " << pyramidD.getHeight()
                  << '\n';
        pyramidD.print();

        // 验证多态性
        std::vector<Shape *> bases;
        bases.push_back(&circleA);
        bases.push_back(&rectA);
        bases.push_back(&circleB);
        bases.push_back(&rectB);

        // 为同一个高度配多个不同底面
        for (std::size_t i = 0; i < bases.size(); ++i) {
                Cone cone(*bases[i], 3.0);
                std::cout << "多态遍历第 " << i + 1 << " 个底面："
                          << bases[i]->getName() << "，底面积 "
                          << bases[i]->area() << "，高 3，体积 "
                          << cone.Volume() << '\n';
        }

        // 常量锥体
        const Cone constCone(rectA, 12.0);
        std::cout << "常量锥体：底面 " << constCone.getBase().getName()
                  << "，底面积 " << constCone.getBase().area() << "，高 "
                  << constCone.getHeight() << "，体积 " << constCone.Volume()
                  << '\n';

        // 计算比较体积
        Cone sameBaseA(circleA, 5.0);
        Cone sameBaseB(circleA, 10.0);
        std::cout << "同一圆底、高 5 的体积 " << sameBaseA.Volume()
                  << "，高 10 的体积 " << sameBaseB.Volume()
                  << "，后者是前者的 "
                  << sameBaseB.Volume() / sameBaseA.Volume() << " 倍\n";

        return 0;
}
