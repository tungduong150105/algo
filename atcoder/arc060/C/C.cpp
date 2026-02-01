#include "bits/stdc++.h"

using i64 = long long;

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, a; std::cin >> n >> a;
    std::vector<int> x(n);
    for (auto &v : x) std::cin >> v;
    std::vector dp(n + 1, std::vector<i64> (50 * 50 + 1, 0));
    dp[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = n - 1; j >= 0; --j) {
            for (int v = 50 * 50 - x[i]; v >= 0; --v) dp[j + 1][v + x[i]] += dp[j][v];
        }
    }
    i64 ans = 0;
    for (int i = 1; i <= n; ++i) ans += dp[i][i * a];
    std::cout << ans << "\n";
    return 0;
}
