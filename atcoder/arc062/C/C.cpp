#include "bits/stdc++.h"

using i64 = long long;

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; std::cin >> n;
    i64 L = 1, R = 1;
    while (n--) {
        int t, a; std::cin >> t >> a;
        i64 aL = (L - 1) / t + 1, aR = (R - 1) / a + 1;
        aL = std::max(aL, aR);
        L = t * aL, R = a * aL;
    }
    std::cout << L + R << "\n";
    return 0;
}
