#include "bits/stdc++.h"

template <class T> struct FenwickTree {
    int n;
    std::vector<T> bit;
    FenwickTree() {}
    FenwickTree(int _n) { init(_n); }
    void init(int _n) {
        n = _n;
        bit.assign(n, T());
    }
    void add(int p, const T& val) {
        for (int i = p + 1; i <= n; i += i & -i) bit[i - 1] = bit[i - 1] + val;
    }
    T sum(int r) {
        T res = T();
        for (int i = r; i > 0; i -= i & -i) res = res + bit[i - 1];
        return res;
    }
    T sum(int l, int r) { return sum(r) - sum(l); }
    int findFirst(T k) {
        T sum = T();
        int pos = 0, LOG = int(std::log2(n)) + 1;
        for (int i = LOG; i >= 0; --i) {
            if (pos + (1 << i) <= n && sum + bit[pos + (1 << i) - 1] < k) {
                sum = sum + bit[pos + (1 << i) - 1];
                pos += (1 << i);
            }
        }
        return pos;
    }
};

#define dbg(...) 1501

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; std::cin >> n;
    std::vector<std::array<int, 4>> a;
    for (int i = 0; i < n; ++i) {
        int x, y, z; std::cin >> x >> y >> z;
        a.push_back({x, y, z, i});
    }
    std::sort(a.begin(), a.end(), [&](const auto &lhs, const auto &rhs) {
        if (lhs[0] != rhs[0]) return lhs[0] > rhs[0];
        return (lhs[1] == rhs[1] ? lhs[2] < rhs[2] : lhs[1] < rhs[1]);
    });
    dbg(a);
    FenwickTree<int> fen(n + 1);
    std::vector<int> ans(n, 0);
    auto f = [&](auto && f, int l, int r) -> void {
        if (r - l == 1) return;
        int m = (l + r) / 2;
        f(f, l, m); f(f, m, r);
        std::vector<int> rec;
        std::vector<std::array<int, 4>> tmp;
        int L = l, R = m, tot = 0;
        while (L < m && R < r) {
            if (a[L][1] > a[R][1]) {
                ++tot;
                fen.add(a[L][2], 1);
                rec.push_back(a[L][2]);
                tmp.push_back(a[L++]);
            } else {
                ans[a[R][3]] += tot - fen.sum(a[R][2] + 1);
                tmp.push_back(a[R++]);
            }
        }
        while (L < m) tmp.push_back(a[L++]);
        while (R < r) {
            ans[a[R][3]] += tot - fen.sum(a[R][2] + 1);
            tmp.push_back(a[R++]);
        }
        dbg(tmp);
        for (int v : rec) fen.add(v, -1);
        for (int i = l; i < r; ++i) a[i] = tmp[i - l];
    };
    f(f, 0, n);
    for (int i = 0; i < n; ++i) std::cout << ans[i] << "\n";
    return 0;
}
