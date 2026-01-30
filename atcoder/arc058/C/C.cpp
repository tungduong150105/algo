#include "bits/stdc++.h"

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, k; std::cin >> n >> k;
    std::vector<int> d(10);
    for (int i = 0; i < k; ++i) {
        int x; std::cin >> x;
        d[x] = true;
    }
    while (n) {
        int cop = n;
        bool ok = true;
        while (n) {
            if (d[n % 10]) ok = false;
            n /= 10;
        }
        n = cop;
        if (ok) break;
        ++n;
    }
    std::cout << n << "\n";
    return 0;
}
