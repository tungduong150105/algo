template <typename MODNUM> void NTT(std::vector<MODNUM> &a, bool inverse = false) {
  int n = int(a.size());
  if (n == 1) return;
  static const int mod = MODNUM::mod();
  static const MODNUM root = MODNUM::get_primitive_root();
  assert(__builtin_popcount(n) == 1 && (mod - 1) % n == 0);

  int L = __builtin_ctz(n);
  std::vector<int> rev(n);
  for (int i = 0; i < n; ++i) {
    rev[i] = (rev[i >> 1] | (i & 1) << L) >> 1;
    if (i < rev[i]) std::swap(a[i], a[rev[i]]);
  }
  MODNUM base_dw = pow(root, (mod - 1) / n);
  std::vector<MODNUM> dw;
  for (int m = n; m >= 2; m >>= 1, base_dw *= base_dw) dw.push_back(base_dw);
  // root ^ ((mod - 1) / 2) -> root ^ ((mod - 1) / 4) -> ... root ^ ((mod - 1) / n)
  for (int m = 2, idx_dw = L - 1; m <= n; m <<= 1, --idx_dw) {
    for (int i = 0; i < n; i += m) {
      MODNUM w = 1;
      for (int j = 0; j < m / 2; ++j, w *= dw[idx_dw]) {
        MODNUM u = a[i + j], v = a[i + j + m / 2];
        a[i + j] = u + w * v, a[i + j + m / 2] = u - w * v;
      }
    }
  }
  if (inverse) {
    std::reverse(a.begin() + 1, a.end());
    MODNUM inv = mod_inv(MODNUM(n));
    for (auto &v : a) v *= inv;
  }
}

template <typename MODNUM>
std::vector<MODNUM> _NTTConvolution(std::vector<MODNUM> a, std::vector<MODNUM> b) {
  if (a.empty() || b.empty()) return {};
  int siz = 1, n = int(a.size()), m = int(b.size());
  while (siz < n + m) siz <<= 1;
  a.resize(siz), b.resize(siz);
  NTT(a), NTT(b);
  for (int i = 0; i < siz; ++i) a[i] *= b[i];
  NTT(a, true);
  a.resize(n + m - 1);
  return a;
}

constexpr int nttprimes[3] = {998244353, 167772161, 469762049};

int64_t garner(int r0, int r1, int r2, int mod) {
  using Z2 = ModNum<nttprimes[2]>;
  static const int64_t m01 = 1LL * nttprimes[0] * nttprimes[1];
  static const int64_t m0_inv_m1 = ModNum<nttprimes[1]>(nttprimes[0]).inv().v;
  static const int64_t m01_inv_m2 = Z2(m01).inv().v;

  int v1 = (m0_inv_m1 * (r1 + nttprimes[1] - r0)) % nttprimes[1];
  auto v2 = (Z2(r2) - r0 - Z2(nttprimes[0]) * v1) * m01_inv_m2;
  return (r0 + 1LL * nttprimes[0] * v1 + m01 % mod * v2.v) % mod;
}

template <typename MODNUM>
std::vector<MODNUM> NTTConvolutionGarner(std::vector<MODNUM> a, std::vector<MODNUM> b) {
  if (a.empty() || b.empty()) return {};
  int siz = 1, n = int(a.size()), m = int(b.size());
  while (siz < n + m) siz <<= 1;
  using Mod1 = ModNum<nttprimes[0]>;
  using Mod2 = ModNum<nttprimes[1]>;
  using Mod3 = ModNum<nttprimes[2]>;
  std::vector<Mod1> ai1(siz), bi1(siz);
  for (int i = 0; i < siz; ++i) ai1[i] = a[i].v, bi1[i] = b[i].v;
  auto ntt1 = _NTTConvolution(ai1, bi1);
  std::vector<Mod2> ai2(siz), bi2(siz);
  for (int i = 0; i < siz; ++i) ai2[i] = a[i].v, bi2[i] = b[i].v;
  auto ntt2 = _NTTConvolution(ai2, bi2);
  std::vector<Mod3> ai3(siz), bi3(siz);
  for (int i = 0; i < siz; ++i) ai3[i] = a[i].v, bi3[i] = b[i].v;
  auto ntt3 = _NTTConvolution(ai3, bi3);
  a.resize(n + m - 1);
  const int mod = MODNUM::mod();
  for (int i = 0; i < n + m - 1; i++) a[i] = garner(ntt1[i].v, ntt2[i].v, ntt3[i].v, mod);
  return a;
}

template <typename MODNUM>
std::vector<MODNUM> NTTConvolution(std::vector<MODNUM> a, std::vector<MODNUM> b) {
  if (a.empty() || b.empty()) return {};
  int sz = 1, n = int(a.size()), m = int(b.size());
  while (sz < n + m) sz <<= 1;
  if (sz <= 16) {
    std::vector<MODNUM> ret(n + m - 1);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) ret[i + j] += a[i] * b[j];
    }
    return ret;
  }
  int mod = MODNUM::mod();
  if (std::find(std::begin(nttprimes), std::end(nttprimes), mod) != std::end(nttprimes))
    return _NTTConvolution(a, b);
  return NTTConvolutionGarner(a, b);
}
