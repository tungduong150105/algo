#include "bits/stdc++.h"

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    std::string s; std::cin >> s;
    int ans = 0;
    for (char c : s) ans -= (c == 'p');
    std::cout << ans + int(s.size()) / 2 << "\n";
    return 0;
}
