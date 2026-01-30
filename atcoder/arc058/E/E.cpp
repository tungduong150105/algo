#include "bits/stdc++.h"

using i64 = long long;

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

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, x, y, z; std::cin >> n >> x >> y >> z;
    int mx = (1 << (x + y + z + 1)) - 1;
    int cond = (1 << z) | (1 << (z + y)) | (1 << (z + y + x));
    std::vector<Z> dp(1 << (x + y + z + 1), 0);
    dp[1] = 1;
    Z ans = 0;
    for (int i = 0; i < n; ++i) {
        std::vector<Z> ndp(1 << (x + y + z + 1), 0);
        for (int v = 1; v <= 10; ++v) {
            for (int mask = 0; mask <= mx; ++mask) {
                ndp[((mask << v) & mx) | 1] += dp[mask];
            }
        }
        for (int mask = 0; mask <= mx; ++mask) {
            if ((mask & cond) == cond) {
                ans += ndp[mask] * pow(Z(10), n - i - 1);
                ndp[mask] = 0;
            }
        }
        std::swap(dp, ndp);
    }
    std::cout << ans << "\n";
    return 0;
}
