#include "bits/stdc++.h"

using i64 = long long;

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    std::string s; std::cin >> s;
    int n = int(s.size());
    i64 ans = 0;
    for (int mask = 0; mask < (1 << (n - 1)); ++mask) {
        i64 num = s[0] - '0';
        for (int i = 0; i < n - 1; ++i) {
            if (mask >> i & 1) {
                ans += num;
                num = 0;
            }
            num *= 10;
            num += s[i + 1] - '0';
        }
        ans += num;
    }
    std::cout << ans << "\n";
    return 0;
}
