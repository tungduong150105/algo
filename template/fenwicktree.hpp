template <class T> struct FenwickTree {
  int n;
  std::vector<T> bit;
  FenwickTree() {}
  FenwickTree(int _n) { init(_n); }
  void init(int _n) {
    n = _n;
    bit.assign(n, T());
  }
  void add(int p, const T &val) {
    for (int i = p + 1; i <= n; i += i & -i) bit[i - 1] = bit[i - 1] + val;
  }
  T sum(int r) {
    T res = T();
    for (int i = r; i > 0; i -= i & -i) res = res + bit[i - 1];
    return res;
  }
  T sum(int l, int r) { return sum(r) - sum(l); }
  int findFirst(T k) {
    T sum = T();
    int pos = 0, LOG = int(std::log2(n)) + 1;
    for (int i = LOG; i >= 0; --i) {
      if (pos + (1 << i) <= n && sum + bit[pos + (1 << i) - 1] < k) {
        sum = sum + bit[pos + (1 << i) - 1];
        pos += (1 << i);
      }
    }
    return pos;
  }
};
