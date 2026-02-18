#include "bits/stdc++.h"

template <typename T> T pow(T a, long long b) {
    T res = T(1);
    for (; b; b /= 2, a *= a) {
        if (b & 1) res *= a;
    }
    return res;
}

template <unsigned P> struct ModNum {
    static int get_primitive_root() {
        static int primitive_root = 0;
        if (!primitive_root) {
            primitive_root = [&]() {
                std::set<int> fac;
                int P_1 = P - 1;
                for (int i = 2; i * i <= P_1; ++i) {
                    while (P_1 % i == 0) {
                        fac.insert(i);
                        P_1 /= i;
                    }
                }
                if (P_1 > 1) fac.insert(P_1);
                for (int i = 1; i < int(P); ++i) {
                    bool ok = true;
                    for (int div : fac) {
                        if (pow(ModNum(i), (P - 1) / div) == 1) {
                            ok = false;
                            break;
                        }
                    }
                    if (ok) return i;
                }
                return -1;
            }();
        }
        return primitive_root;
    }
    unsigned value;
    constexpr ModNum() : value(0) {}
    static constexpr int mod() { return P; }

    template <typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
    constexpr ModNum(T a) : value((((long long)a % P) + P) % P) {}

    ModNum inv() const { return pow(*this, P - 2); }
    ModNum operator+() const { return *this; }
    ModNum operator-() const { return ModNum() - *this; }

    ModNum&operator+=(const ModNum &rhs) {
        value += rhs.value;
        if (value >= P) value -= P;
        return *this;
    }
    ModNum&operator-=(const ModNum &rhs) {
        value += P - rhs.value;
        if (value >= P) value -= P;
        return *this;
    }
    ModNum&operator*=(const ModNum &rhs) {
        value = (unsigned long long)value * rhs.value % P;
        return *this;
    }
    ModNum&operator/=(const ModNum &rhs) { return *this *= rhs.inv(); }

    bool operator==(const ModNum &rhs) const { return value == rhs.value; }
    bool operator!=(const ModNum &rhs) const { return value != rhs.value; }

    friend ModNum operator+(ModNum lhs, const ModNum &rhs) { return lhs += rhs; }
    friend ModNum operator-(ModNum lhs, const ModNum &rhs) { return lhs -= rhs; }
    friend ModNum operator*(ModNum lhs, const ModNum &rhs) { return lhs *= rhs; }
    friend ModNum operator/(ModNum lhs, const ModNum &rhs) { return lhs /= rhs; }
    friend std::ostream& operator<<(std::ostream& out, const ModNum &a) { return out << a.value; }
    friend std::istream& operator>>(std::istream& in, ModNum&a ) {
        long long in_value; in >> in_value; a = ModNum(in_value);
        return in;
    }
};

using Z = ModNum<1000000007>;

template <typename MODINT> std::vector<MODINT> nttconv(std::vector<MODINT> a, std::vector<MODINT> b, bool skip_garner);

constexpr int nttprimes[3] = {998244353, 167772161, 469762049};

template <typename MODINT> void ntt(std::vector<MODINT> &a, bool is_inverse = false) {
    int n = int(a.size());
    if (n == 1) return;
    static const int mod = MODINT::mod();
    static const MODINT root = MODINT::get_primitive_root();
    assert(__builtin_popcount(n) == 1 && (mod - 1) % n == 0);

    static std::vector<MODINT> w{1}, iw{1};
    for (int m = int(w.size()); m < n / 2; m *= 2) {
        MODINT dw = pow(root, (mod - 1) / (4 * m)), dwinv = 1 / dw;
        w.resize(m * 2), iw.resize(m * 2);
        for (int i = 0; i < m; i++) w[m + i] = w[i] * dw, iw[m + i] = iw[i] * dwinv;
    }

    if (!is_inverse) {
        for (int m = n; m /= 2;) {
            for (int s = 0, k = 0; s < n; s += 2 * m, k++) {
                for (int i = s; i < s + m; i++) {
                    MODINT x = a[i], y = a[i + m] * w[k];
                    a[i] = x + y, a[i + m] = x - y;
                }
            }
        }
    } else {
        for (int m = 1; m < n; m *= 2) {
            for (int s = 0, k = 0; s < n; s += 2 * m, k++) {
                for (int i = s; i < s + m; i++) {
                    MODINT x = a[i], y = a[i + m];
                    a[i] = x + y, a[i + m] = (x - y) * iw[k];
                }
            }
        }
        int n_inv = MODINT(n).inv().value;
        for (auto &v : a) v *= n_inv;
    }
}

template <int MOD> std::vector<ModNum<MOD>> nttconv_(const std::vector<int> &a, const std::vector<int> &b) {
    int sz = int(a.size());
    assert(a.size() == b.size() && __builtin_popcount(sz) == 1);
    std::vector<ModNum<MOD>> ap(sz), bp(sz);
    for (int i = 0; i < sz; i++) ap[i] = a[i], bp[i] = b[i];
    ntt(ap, false);
    if (a == b) bp = ap;
    else ntt(bp, false);
    for (int i = 0; i < sz; i++) ap[i] *= bp[i];
    ntt(ap, true);
    return ap;
}

long long garner_ntt_(int r0, int r1, int r2, int mod) {
    using mint2 = ModNum<nttprimes[2]>;
    static const long long m01 = 1LL * nttprimes[0] * nttprimes[1];
    static const long long m0_inv_m1 = ModNum<nttprimes[1]>(nttprimes[0]).inv().value;
    static const long long m01_inv_m2 = mint2(m01).inv().value;

    int v1 = (m0_inv_m1 * (r1 + nttprimes[1] - r0)) % nttprimes[1];
    auto v2 = (mint2(r2) - r0 - mint2(nttprimes[0]) * v1) * m01_inv_m2;
    return (r0 + 1LL * nttprimes[0] * v1 + m01 % mod * v2.value) % mod;
}

template <typename MODINT> std::vector<MODINT> nttconv(std::vector<MODINT> a, std::vector<MODINT> b, bool skip_garner) {
    if (a.empty() or b.empty()) return {};
    int sz = 1, n = int(a.size()), m = int(b.size());
    while (sz < n + m) sz <<= 1;
    if (sz <= 16) {
        std::vector<MODINT> ret(n + m - 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) ret[i + j] += a[i] * b[j];
        }
        return ret;
    }
    int mod = MODINT::mod();
    if (skip_garner || std::find(std::begin(nttprimes), std::end(nttprimes), mod) != std::end(nttprimes)) {
        a.resize(sz), b.resize(sz);
        if (a == b) {
            ntt(a, false);
            b = a;
        } else {
            ntt(a, false), ntt(b, false);
        }
        for (int i = 0; i < sz; i++) a[i] *= b[i];
        ntt(a, true);
        a.resize(n + m - 1);
    } else {
        std::vector<int> ai(sz), bi(sz);
        for (int i = 0; i < n; i++) ai[i] = a[i].value;
        for (int i = 0; i < m; i++) bi[i] = b[i].value;
        auto ntt0 = nttconv_<nttprimes[0]>(ai, bi);
        auto ntt1 = nttconv_<nttprimes[1]>(ai, bi);
        auto ntt2 = nttconv_<nttprimes[2]>(ai, bi);
        a.resize(n + m - 1);
        for (int i = 0; i < n + m - 1; i++) a[i] = garner_ntt_(ntt0[i].value, ntt1[i].value, ntt2[i].value, mod);
    }
    return a;
}

template <typename MODINT> std::vector<MODINT> nttconv(const std::vector<MODINT> &a, const std::vector<MODINT> &b) {
    return nttconv<MODINT>(a, b, false);
}

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m, k; std::cin >> n >> m >> k;
    std::vector<Z> fac(n + m + k + 1), ifac(n + m + k + 1);
    fac[0] = 1;
    for (int i = 1; i <= n + m + k; ++i) fac[i] = fac[i - 1] * i;
    ifac[n + m + k] = fac[n + m + k].inv();
    for (int i = n + m + k; i > 0; --i) ifac[i - 1] = ifac[i] * i;
    std::vector<Z> poly1;
    for (int i = 0; i <= m; ++i) poly1.push_back(ifac[i] * pow(Z(3), m - i));
    std::vector<Z> poly2;
    for (int i = 0; i <= k; ++i) poly2.push_back(ifac[i] * pow(Z(3), k - i));
    auto res = nttconv(poly1, poly2);
    Z ans = 0;
    for (int s = 0; s <= m + k; ++s) ans += fac[n - 1 + s] * ifac[n - 1] * res[s];
    std::cout << ans << "\n";
    return 0;
}
