#include "bits/stdc++.h"

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    std::string s; std::cin >> s;
    if (int(s.size()) == 2) {
        if (s[0] == s[1]) std::cout << "1 2\n";
        else std::cout << "-1 -1\n";
        return 0;
    }
    for (int i = 0; i < int(s.size()) - 2; ++i) {
        if (s[i] == s[i + 1] || s[i] == s[i + 2] || s[i + 1] == s[i + 2]) {
            std::cout << i + 1 << " " << i + 3 << "\n";
            return 0;
        }
    }
    std::cout << "-1 -1\n";
    return 0;
}
