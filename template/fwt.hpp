template <typename T> void FWT(std::vector<T> &poly, bool inverse = false) {
  int n = int(poly.size());
  for (int k = 1; k < n; k <<= 1) {
    for (int i = 0; i < n; i += k << 1) {
      for (int j = 0; j < k; ++j) {
        T u = poly[i + j], v = poly[i + j + k];
        if (!inverse) {
          poly[i + j] = u + v;
          poly[i + j + k] = u - v;
        } else {
          poly[i + j] = (u + v) / 2;
          poly[i + j + k] = (u - v) / 2;
        }
      }
    }
  }
}

template <typename T> std::vector<T> convolution(std::vector<T> a, std::vector<T> b) {
  int n = 1;
  while (n < int(a.size() + b.size() - 1)) n <<= 1;
  a.resize(n);
  b.resize(n);
  FWT(a);
  FWT(b);
  for (int i = 0; i < n; ++i) a[i] *= b[i];
  FWT(a, true);
  return a;
}

