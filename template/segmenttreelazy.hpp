template <class Info, class Tag> struct SegmentTreeLazy {
  int n;
  std::vector<Info> info;
  std::vector<Tag> tag;
  SegmentTreeLazy() {}
  SegmentTreeLazy(int _n) { init(_n); }
  void init(int _n) {
    n = _n;
    info.assign(4 * n, Info());
    tag.assign(4 * n, Tag());
  }
  void apply(int v, int l, int r, const Tag &x) {
    info[v].apply(x, l, r);
    tag[v].apply(x);
  }
  void push_down(int v, int l, int r) {
    int m = (l + r) >> 1;
    apply(v << 1, l, m, tag[v]);
    apply(v << 1 | 1, m, r, tag[v]);
    tag[v] = Tag();
  }
  void modify(int v, int l, int r, int idx, const Info &x) {
    if (r - l == 1) {
      info[v] = info[v] + x;
      return;
    }
    int m = (l + r) >> 1;
    push_down(v, l, r);
    if (idx < m) {
      modify(v << 1, l, m, idx, x);
    } else {
      modify(v << 1 | 1, m, r, idx, x);
    }
    info[v] = info[v << 1] + info[v << 1 | 1];
  }
  void addRange(int v, int l, int r, int lhs, int rhs, const Tag &x) {
    if (rhs <= l || lhs >= r) return;
    if (lhs <= l && r <= rhs) {
      apply(v, l, r, x);
    } else {
      push_down(v, l, r);
      int m = (l + r) >> 1;
      addRange(v << 1, l, m, lhs, rhs, x);
      addRange(v << 1 | 1, m, r, lhs, rhs, x);
      info[v] = info[v << 1] + info[v << 1 | 1];
    }
  }
  Info rangeQuery(int v, int l, int r, int lhs, int rhs) {
    if (rhs <= l || lhs >= r) return Info();
    if (lhs <= l && r <= rhs) return info[v];
    push_down(v, l, r);
    int m = (l + r) >> 1;
    return rangeQuery(v << 1, l, m, lhs, rhs) + rangeQuery(v << 1 | 1, m, r, lhs, rhs);
  }
  void modify(int idx, const Info &x) { modify(1, 0, n, idx, x); }
  void addRange(int l, int r, const Tag &x) { addRange(1, 0, n, l, r, x); }
  Info rangeQuery(int l, int r) { return rangeQuery(1, 0, n, l, r); }
};
