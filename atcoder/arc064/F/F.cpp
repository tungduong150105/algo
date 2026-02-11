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

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, k; std::cin >> n >> k;
    std::vector<int> divs;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) divs.push_back(i);
        if (n % i == 0 && n / i != i) divs.push_back(n / i);
    }
    std::sort(divs.begin(), divs.end());
    int m = int(divs.size());
    std::vector<Z> g(m);
    for (int i = 0; i < m; ++i) {
        g[i] = pow(Z(k), (divs[i] + 1) / 2); 
        for (int j = 0; j < i; ++j) {
            if (divs[i] % divs[j] == 0) g[i] -= g[j];
        }
    }
    Z ans = 0;
    for (int i = 0; i < m; ++i) ans += g[i] * (divs[i] % 2 ? divs[i] : divs[i] / 2);
    std::cout << ans << "\n";
    return 0;
}
