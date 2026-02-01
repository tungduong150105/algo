#include "bits/stdc++.h"

std::vector<int> kmp(const std::string &s) {
    int n = int(s.size());
    std::vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

#define dbg(...) 1501

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    std::string s; std::cin >> s;
    int n = int(s.size());
    auto pref = kmp(s);
    int k = n - pref[n - 1];
    if (n % k == 0 && n != k) {
        if (k == 1) {
            std::cout << n << "\n" << "1\n";
        } else {
            int w = 0;
            std::reverse(s.begin(), s.end());
            auto suff = kmp(s);
            std::reverse(suff.begin(), suff.end());
            for (int i = 0; i < n - 1; ++i) {
                int k_pref = i + 1 - pref[i];
                int k_suff = n - i - 1 - suff[i + 1];
                bool ok_pref = (i + 1 != 1 && i + 1 != k_pref && (i + 1) % k_pref == 0);
                bool ok_suff = (n - i - 1 != 1 && n - i - 1 != k_suff && (n - i - 1) % k_suff == 0);
                dbg(k_pref, k_suff);
                w += !ok_pref && !ok_suff;
            }
            std::cout << "2\n" << w << "\n";
        }
    } else {
        std::cout << "1\n1\n";
    }
    return 0;
}
