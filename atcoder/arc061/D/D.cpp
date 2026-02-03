#include "bits/stdc++.h"

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int h, w, n; std::cin >> h >> w >> n;
    std::map<std::pair<int, int>, int> mp;
    std::vector<std::pair<int, int>> a;
    for (int i = 0; i < n; ++i) {
        int x, y; std::cin >> x >> y;
        --x, --y;
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (x >= j && y >= k) a.emplace_back(x - j, y - k);
            }
        }
        ++mp[{x, y}];
    }
    std::sort(a.begin(), a.end());
    a.erase(std::unique(a.begin(), a.end()), a.end());
    auto f = [&](int x, int y) -> int {
        if (x + 2 >= h || y + 2 >= w) return 0;
        int cnt = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) cnt += mp[{x + i, y + j}];
        }
        return cnt;
    };
    std::vector<int> ans(10, 0);
    for (auto [x, y] : a) ++ans[f(x, y)];
    ans[0] = 0;
    std::cout << 1LL * (w - 2) * (h - 2) - std::accumulate(ans.begin(), ans.end(), 0LL) << "\n";
    for (int i = 1; i < 10; ++i) std::cout << ans[i] << "\n";
    return 0;
}
