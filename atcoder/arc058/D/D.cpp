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
    int h, w, a, b; std::cin >> h >> w >> a >> b;
    std::vector<Z> fac(h + w + 1), ifac(h + w + 1);
    fac[0] = 1;
    for (int i = 1; i <= h + w; ++i) fac[i] = fac[i - 1] * i;
    ifac[h + w] = fac[h + w].inv();
    for (int i = h + w; i > 0; --i) ifac[i - 1] = ifac[i] * i;
    Z ans = 0;
    for (int i = b; i < w; ++i) {
        Z above = fac[h - a - 1 + i] * ifac[h - a - 1] * ifac[i];
        Z under = fac[a - 1 + w - i - 1] * ifac[a - 1] * ifac[w - i - 1];
        ans += above * under;
    }
    std::cout << ans << "\n";
    return 0;
}
