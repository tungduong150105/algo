#include "bits/stdc++.h"

using i64 = long long;

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, x; std::cin >> n >> x;
    std::vector<int> a(n);
    for (int &v : a) std::cin >> v;
    i64 ans = 0;
    for (int i = 1; i < n; ++i) {
        int diff = std::max(0, a[i] + a[i - 1] - x);
        ans += diff;
        a[i] -= std::min(a[i], diff);
    }
    std::cout << ans << "\n";
    return 0;
}
