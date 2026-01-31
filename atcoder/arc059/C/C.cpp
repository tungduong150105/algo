#include "bits/stdc++.h"

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; std::cin >> n;
    std::vector<int> a(n);
    for (int &v : a) std::cin >> v;
    int ans = std::numeric_limits<int>::max() / 2;
    for (int i = -100; i <= 100; ++i) {
        int res = 0;
        for (int v : a) res += (v - i) * (v - i);
        ans = std::min(ans, res);
    }
    std::cout << ans << "\n";
    return 0;
}
