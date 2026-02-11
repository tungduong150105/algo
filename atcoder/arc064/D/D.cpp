#include "bits/stdc++.h"

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    std::string s; std::cin >> s;
    int n = int(s.size());
    if ((s[0] == s.back() && n % 2 == 0) || (s[0] != s.back() && n % 2)) std::cout << "First\n";
    else std::cout << "Second\n";
    return 0;
}
