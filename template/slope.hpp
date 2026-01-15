template <class T, T INF = std::numeric_limits<T>::max() / 2> struct slope {
  T min_f;
  T add_l, add_r;
  std::priority_queue<T, std::vector<T>, std::less<T>> L;
  std::priority_queue<T, std::vector<T>, std::greater<T>> R;
  void pushL(const T &a) { L.push(a - add_l); }
  T topL() const { return L.empty() ? -INF : L.top() + add_l; }
  T popL() {
    T ans = topL();
    if (L.size()) L.pop();
    return ans;
  }
  void pushR(const T &a) { R.push(a - add_r); }
  T topR() const { return R.empty() ? INF : R.top() + add_r; }
  T popR() {
    T ans = topR();
    if (R.size()) R.pop();
    return ans;
  }

  slope() : min_f(0), add_l(0), add_r(0) { static_assert(INF > 0, "INF must be greater than 0"); }
  slope &add_a_minus_x(const T &a) {
    min_f += std::max(T(0), a - topR());
    pushR(a);
    pushL(popR());
    return *this;
  }
  slope &add_x_minus_a(const T &a) {
    min_f += std::max(T(0), topL() - a);
    pushL(a);
    pushR(popL());
    return *this;
  }
  slope &add_abs(const T &a) {
    add_a_minus_x(a);
    add_x_minus_a(a);
    return *this;
  }
  slope &shift_left(const T &a) {
    add_l += a;
    return *this;
  }
  slope &shift_right(const T &a) {
    add_r += a;
    return *this;
  }
  slope &translate(const T &a) {
    add_l += a;
    add_r += a;
    return *this;
  }
};
