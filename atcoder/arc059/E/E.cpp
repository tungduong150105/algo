#include "bits/stdc++.h"

template <typename T> T pow(T a, long long b) {
    T res = T(1);
    for (; b; b /= 2, a *= a) {
        if (b & 1) res *= a;
    }
    return res;
}

template <unsigned P> struct ModNum {
    unsigned value;
    constexpr ModNum() : value(0) {}

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

#define dbg(...) 1501

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, c; std::cin >> n >> c;
    std::vector<int> a(n), b(n);
    for (int &v : a) std::cin >> v;
    for (int &v : b) std::cin >> v;
    std::vector pre(n, std::vector<Z> (c + 1, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= c; ++j) {
            for (int v = a[i]; v <= b[i]; ++v) pre[i][j] += pow(Z(v), j);
        }
    }
    std::vector<Z> dp(c + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
        std::vector<Z> ndp(c + 1, 0);
        for (int k = 0; k <= c; ++k) {
            if (!dp[k].value) continue;
            for (int j = k; j <= c; ++j) {
                ndp[j] += dp[k] * pre[i][j - k];
            }
        }
        std::swap(dp, ndp);
        dbg(dp);
    }
    std::cout << dp[c] << "\n";
    return 0;
}
