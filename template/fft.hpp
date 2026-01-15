using cmplx = std::complex<double>;
void fft(int N, std::vector<cmplx> &a, double dir) {
  int i = 0;
  for (int j = 1; j < N - 1; j++) {
    for (int k = N >> 1; k > (i ^= k); k >>= 1) {}
    if (j < i) std::swap(a[i], a[j]);
  }

  std::vector<cmplx> zeta_pow(N);
  for (int j = 0; j < N; j++) {
    double theta = M_PI / N * j * dir;
    zeta_pow[j] = {cos(theta), sin(theta)};
  }

  for (int m = 1; m < N; m *= 2) {
    for (int y = 0; y < m; y++) {
      cmplx fac = zeta_pow[N / m * y];
      for (int x = 0; x < N; x += 2 * m) {
        int u = x + y;
        int v = x + y + m;
        cmplx s = a[u] + fac * a[v];
        cmplx t = a[u] - fac * a[v];
        a[u] = s;
        a[v] = t;
      }
    }
  }
}

template <typename T>
std::vector<cmplx> conv_cmplx(const std::vector<T> &a, const std::vector<T> &b) {
  int N = 1;
  while (N < int(a.size()) + int(b.size())) N *= 2;
  std::vector<cmplx> a_(N), b_(N);
  for (int i = 0; i < int(a.size()); i++) a_[i] = a[i];
  for (int i = 0; i < int(b.size()); i++) b_[i] = b[i];
  fft(N, a_, 1);
  fft(N, b_, 1);
  for (int i = 0; i < N; i++) a_[i] *= b_[i];
  fft(N, a_, -1);
  for (int i = 0; i < N; i++) a_[i] /= N;
  return a_;
}

template <typename T>
std::vector<int64_t> fftconv(const std::vector<T> &a, const std::vector<T> &b) {
  std::vector<cmplx> ans = conv_cmplx(a, b);
  std::vector<int64_t> ret(ans.size());
  for (int i = 0; i < (int)ans.size(); i++) ret[i] = int64_t(std::floor(ans[i].real() + 0.5));
  ret.resize(a.size() + b.size() - 1);
  return ret;
}
