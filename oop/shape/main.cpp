#include <algorithm>
#include <cmath>
#include <iostream>

namespace geo {

// 浮点数有误差，给出容许范围 epsilon
inline const double kEps = 1e-9;

inline bool nearlyEqual(double a, double b) {
  const double scale = std::max({1.0, std::fabs(a), std::fabs(b)});
  return std::fabs(a - b) <= kEps * scale;
}

// 返回 -1 / 0 / 1，0 表示在容差范围内相等
inline int compare(double a, double b) {
  if (nearlyEqual(a, b))
    return 0;
  return a < b ? -1 : 1;
}

class Point {
public:
  Point() = default;
  Point(double x, double y) : x_(x), y_(y) {}

  // 后置 const 代表不对对象进行修改
  double x() const { return x_; }
  double y() const { return y_; }

  // 两点间距离：sqrt(dx^2 + dy^2)
  double distanceTo(const Point &other) const {
    const double dx = x_ - other.x_;
    const double dy = y_ - other.y_;
    return std::hypot(dx, dy);
  }

  bool operator==(const Point &other) const {
    return nearlyEqual(x_, other.x_) && nearlyEqual(y_, other.y_);
  }
  bool operator!=(const Point &other) const { return !(*this == other); }

private:
  double x_ = 0.0;
  double y_ = 0.0;
};

// 自定义便于输出的函数
inline std::ostream &operator<<(std::ostream &os, const Point &p) {
  return os << '(' << p.x() << ", " << p.y() << ')';
}

class Circle {
public:
  Circle() : radius_(0.0), center_(Point{}) {}
  // 圆由“圆心 + 半径”组合而成：Circle has-a Point，
  // 半径为非负数
  Circle(double radius, const Point &center = Point{})
      : center_(center), radius_(std::fabs(radius)) {}

  const Point &center() const { return center_; }
  double radius() const { return radius_; }

  // 半径是长度，负值没有意义
  void setRadius(double radius) { radius_ = std::fabs(radius); }
  void setCenter(const Point &center) { center_ = center; }

  // 点与圆的位置关系：在圆内 / 在边缘上 / 在圆外
  // enum class 是 《Effective Modern C++》的推荐写法
  enum class PointPosition { Inside, OnEdge, Outside };

  PointPosition positionOf(const Point &p) const {
    const int cmp = compare(center_.distanceTo(p), radius_);
    if (cmp < 0)
      return PointPosition::Inside;
    if (cmp == 0)
      return PointPosition::OnEdge;
    return PointPosition::Outside;
  }

  // 两圆的位置关系：包含 / 相交 / 相离
  // 按题目只分三类，切点归入相邻类别：
  //   d + min(r1,r2) <= max(r1,r2)  -> 包含（内切也算包含）
  //   d >= r1 + r2                  -> 相离（外切也算相离）
  //   其余                          -> 相交
  enum class Relation { Contains, Intersect, Separate };

  Relation relationTo(const Circle &other) const {
    const double d = center_.distanceTo(other.center_);
    const double rMin = std::min(radius_, other.radius_);
    const double rMax = std::max(radius_, other.radius_);

    if (compare(d + rMin, rMax) <= 0)
      return Relation::Contains;
    if (compare(d, radius_ + other.radius_) >= 0)
      return Relation::Separate;
    return Relation::Intersect;
  }

private:
  Point center_;
  double radius_ = 0.0;
};

inline Circle::PointPosition positionOf(const Point &p, const Circle &c) {
  return c.positionOf(p);
}

inline Circle::Relation relationOf(const Circle &a, const Circle &b) {
  return a.relationTo(b);
}

inline const char *toString(Circle::PointPosition pos) {
  switch (pos) {
  case Circle::PointPosition::Inside:
    return "在圆内";
  case Circle::PointPosition::OnEdge:
    return "在边缘上";
  case Circle::PointPosition::Outside:
    return "在圆外";
  }
  return "未知";
}

inline const char *toString(Circle::Relation rel) {
  switch (rel) {
  case Circle::Relation::Contains:
    return "包含";
  case Circle::Relation::Intersect:
    return "相交";
  case Circle::Relation::Separate:
    return "相离";
  }
  return "未知";
}

} // namespace geo

int main() {
  using namespace geo;

  std::cout << "点与圆的位置关系\n\n";
  const Circle c(5.0, Point(0, 0));
  std::cout << "圆: 圆心 " << c.center() << ", 半径 " << c.radius() << "\n";
  for (const Point &p :
       {Point(0, 0), Point(3, 4), Point(-5, 0), Point(5.5, 0)}) {
    std::cout << "  点 " << p << " -> " << toString(c.positionOf(p)) << '\n';
  }

  const Circle dot(0.0, Point(1, 1));
  std::cout << "退化圆: 圆心 " << dot.center() << ", 半径 " << dot.radius()
            << "\n";
  std::cout << "  点 (1,1)   -> " << toString(dot.positionOf(Point(1, 1)))
            << '\n';
  std::cout << "  点 (1,1.1) -> " << toString(dot.positionOf(Point(1, 1.1)))
            << '\n';

  std::cout << "\n两圆的位置关系\n\n";
  // 大圆
  const Circle big(5.0, Point(0, 0));
  // 内部小圆
  const Circle smallInside(1.0, Point(1, 0));
  // 内切圆
  const Circle internallyTangent(1.0, Point(4, 0));
  // 相交圆
  const Circle crossing(3.0, Point(6, 0));
  // 外切圆
  const Circle externallyTangent(3.0, Point(8, 0));
  // 相离的圆
  const Circle farAway(1.0, Point(20, 0));

  std::cout << "圆心距 / 半径 -> 关系\n";
  for (const Circle &other :
       {smallInside, internallyTangent, crossing, externallyTangent, farAway}) {
    std::cout << "  d = " << big.center().distanceTo(other.center())
              << ", r1 = " << big.radius() << ", r2 = " << other.radius()
              << " -> " << toString(big.relationTo(other)) << '\n';
  }

  // 负半径会被规范化成非负，对象始终保持合法状态
  Circle normalized(-2.0, Point(0, 0));
  std::cout << "\n传入半径 -2 后，实际半径 = " << normalized.radius() << '\n';

  return 0;
}
