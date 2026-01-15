template <typename T> struct Combinatoric {
  int n;
  std::vector<T> _fac, _ifac, _inv;
  Combinatoric() : n(0), _fac{1}, _ifac{1}, _inv{1} {}
  Combinatoric(int _n) : Combinatoric() { init(_n); }
  void init(int _n) {
    if (_n <= n) return;
    _fac.resize(_n + 1);
    _ifac.resize(_n + 1);
    _inv.resize(_n + 1);
    for (int i = n + 1; i <= _n; ++i) _fac[i] = _fac[i - 1] * i;
    _ifac[_n] = _fac[_n].inv();
    for (int i = _n; i > n; --i) {
      _ifac[i - 1] = _ifac[i] * i;
      _inv[i] = _ifac[i] * _fac[i - 1];
    }
    n = _n;
  }
  T fac(int _n) {
    if (_n > n) init(2 * _n);
    return _fac[_n];
  }
  T ifac(int _n) {
    if (_n > n) init(2 * _n);
    return _ifac[_n];
  }
  T inv(int _n) {
    if (_n > n) init(2 * _n);
    return _inv[_n];
  }
  T nCr(int N, int R) {
    if (N < 0 || R < 0 || N < R) return T(0);
    return fac(N) * ifac(N - R) * ifac(R);
  }
};
