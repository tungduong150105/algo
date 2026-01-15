template <typename T> T LinearRecurrence(std::vector<T> P, std::vector<T> Q, int64_t k) {
  assert(P.size() && Q.size() && Q[0] != 0);
  while (k) {
    int d = int(Q.size()) - 1;
    std::vector<T> Q_neg = Q;
    for (int i = 1; i <= d; i += 2) Q_neg[i] *= -1;
    auto _U = NTTConvolution(P, Q_neg);
    auto _V = NTTConvolution(Q, Q_neg);
    std::vector<T> V(d + 1);
    for (int i = 0; i <= d; ++i) V[i] = _V[i * 2];
    std::vector<T> U;
    for (int i = 0; i < int(_U.size()); ++i) {
      if (k % 2 == i % 2) U.push_back(_U[i]);
    }
    return LinearRecurrence(U, V, k / 2);
    k /= 2;
    std::swap(P, U);
    std::swap(Q, V);
  }
  return P[0] / Q[0];
}
