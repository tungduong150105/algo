#include "bits/stdc++.h"

#define dbg(...) 1501

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; std::cin >> n;
    std::vector<int> x(n);
    for (auto &v : x) std::cin >> v;
    int L; std::cin >> L;
    constexpr int LOG = 20;
    std::vector nxt(n, std::vector<int> (LOG + 1, n));
    for (int i = 0, lo = 0; i < n; ++i) {
        while (lo < n && x[lo] - x[i] <= L) ++lo;
        assert(i < lo);
        nxt[i][0] = lo - 1;
        dbg(i, lo - 1);
    }
    for (int i = 1; i <= LOG; ++i) {
        for (int j = 0; j < n; ++j) nxt[j][i] = nxt[nxt[j][i - 1]][i - 1];
    }
    auto jp = [&](int cur, int st) -> int {
        for (int i = LOG; i >= 0; --i) {
            if (st >> i & 1) cur = nxt[cur][i];
        }
        return cur;
    };
    dbg(nxt[0][0]);
    dbg(jp(0, 1));
    dbg(nxt[0][3]);
    int q; std::cin >> q;
    while (q--) {
        int a, b; std::cin >> a >> b;
        --a, --b;
        if (a > b) std::swap(a, b);
        int lo = 0, hi = n + 1;
        while (hi - lo > 1) {
            int mid = (lo + hi) / 2;
            if (jp(a, mid) < b) lo = mid;
            else hi = mid;
        }
        dbg(jp(a, lo), lo, b);
        std::cout << lo + 1 << "\n";
    }
    return 0;
}
