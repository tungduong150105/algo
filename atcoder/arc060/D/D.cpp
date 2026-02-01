#include "bits/stdc++.h"

using i64 = long long;

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    i64 n, s; std::cin >> n >> s;
    i64 sq = 1;
    while (sq * sq < n) ++sq;
    i64 ans = -1;
    for (i64 b = 2; b <= sq; ++b) {
        i64 sum = 0;
        i64 cp = n;
        while (cp) {
            sum += cp % b;
            cp /= b;
        }
        if (sum == s) {
            ans = b;
            break;
        }
    }
    if (ans == -1) {
        i64 cur = sq + 1;
        while (true) {
            if (cur > n) break;
            i64 div = n / cur;
            i64 up = n / div;
            // [cur, up]
            i64 rem = s - div;
            i64 b = (n - rem) / div;
            if (b >= cur && b <= up && n % b == rem) {
                ans = b;
                break;
            }
            cur = up + 1;
        }
    }
    if (ans == -1 && s == n) ans = s + 1;
    std::cout << ans << "\n";
    return 0;
}
