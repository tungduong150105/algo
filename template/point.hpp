template <typename T> struct Point {
  T x, y;
  Point(const T &_x = 0, const T &_y = 0) : x(_x), y(_y) {}
  template <typename U> operator Point<U>() { return Point<U>(U(x), U(y)); }
  Point &operator+=(const Point &lhs) {
    x += lhs.x, y += lhs.y;
    return *this;
  }
  Point &operator-=(const Point &lhs) {
    x -= lhs.x, y -= lhs.y;
    return *this;
  }
  Point &operator*=(const T &lhs) {
    x *= lhs, y *= lhs;
    return *this;
  }
  Point &operator/=(const T &lhs) {
    x /= lhs, y /= lhs;
    return *this;
  }
  Point operator-() const { return Point(-x, -y); }
  friend Point operator+(Point lhs, const Point &rhs) { return lhs += rhs; }
  friend Point operator-(Point lhs, const Point &rhs) { return lhs -= rhs; }
  friend Point operator*(Point lhs, const T &rhs) { return lhs *= rhs; }
  friend Point operator/(Point lhs, const T &rhs) { return lhs /= rhs; }
  friend Point operator*(const T &lhs, Point rhs) { return rhs *= lhs; }
  friend bool operator==(const Point &lhs, const Point &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }
  friend std::istream &operator>>(std::istream &is, Point &lhs) { return is >> lhs.x >> lhs.y; }
  friend std::ostream &operator<<(std::ostream &os, const Point &lhs) {
    return os << "(" << lhs.x << ", " << lhs.y << ")";
  }
};

template <typename T> T dot(const Point<T> &lhs, const Point<T> &rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y;
}
template <typename T> T cross(const Point<T> &lhs, const Point<T> &rhs) {
  return lhs.x * rhs.y - lhs.y * rhs.x;
}
template <typename T> T square(const Point<T> &lhs) { return dot(lhs, lhs); }
template <typename T> double length(const Point<T> &lhs) { return std::sqrt(square(lhs)); }

using P = Point<int>;
