#include "bits/stdc++.h"

std::vector<int> z_function(const std::string& s) {
    int n = int(s.size());
    std::vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i < r) z[i] = std::min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

#define dbg(...) 1501

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, k; std::cin >> n >> k;
    std::vector<std::string> s(n);
    for (auto& v : s) std::cin >> v;
    std::vector can(n + 1, std::vector<bool>(k + 1, false));
    can[n][0] = true;
    for (int i = n - 1; i >= 0; --i) {
        can[i] = can[i + 1];
        for (int j = k; j >= int(s[i].size()); --j) {
            if (can[i + 1][j - int(s[i].size())]) can[i][j] = true;
        }
    }
    dbg(can);
    std::vector<bool> dp(k + 1, false);
    dp[0] = true;
    std::string prev = "";
    for (int i = 0; i < n; ++i) {
        dbg(dp);
        std::string t = prev;
        std::string str = s[i] + '#' + t;
        dbg(str);
        auto z = z_function(str);
        dbg(z);
        // compare str[0 .. p) and str[0 .. q) + s[idx]
        auto cmp = [&](int p, int q, int idx) {
            if (p <= q) return 0;
            int s_size = int(s[idx].size());
            dbg(s_size, p);
            int lcp = z[s_size + q + 1];
            if (lcp == s_size || q + lcp >= p) return 0;
            dbg(lcp);
            if (s[idx][lcp] < t[q + lcp]) return 1;
            return -1;
        };
        // compare str[0 .. p) + s[idx] and str[0 .. q) + s[idx]
        auto cmp2 = [&](int p, int q, int idx) {
            assert(p <= q);
            int s_size = int(s[idx].size());
            int lcp = z[s_size + p + 1];
            if (q - p > lcp) {
                if (lcp == s_size) return 0;
                if (s[idx][lcp] > t[p + lcp]) return 1;
                return -1;
            }
            lcp = z[q - p];
            if (q - p + lcp == s_size) return 0;
            if (s[idx][lcp] < s[idx][q - p + lcp]) return 1;
            return -1;
        };
        int nxt = -1;
        for (int j = 0; j + int(s[i].size()) <= k; ++j) {
            if (dp[j] && can[i + 1][k - int(s[i].size()) - j]) {
                if (nxt == -1) {
                    int res = cmp(int(t.size()), j, i);
                    dbg("case", i, "at", j, ":", res);
                    if (res == 1 || (res == 0 && j + int(s[i].size()) > int(t.size()))) nxt = j;
                } else if (cmp2(nxt, j, i) >= 0) {
                    nxt = j;
                }
            }
        }
        std::vector<bool> ndp(k + 1, false);
        dbg(i, t, nxt);
        if (nxt == -1) {
            ndp = dp;
            for (int j = 0; j + int(s[i].size()) < int(t.size()); ++j) {
                if (dp[j] && can[i + 1][k - int(s[i].size()) - j] && cmp(int(t.size()), j, i) == 0) ndp[j + int(s[i].size())] = true;
            }
        } else {
            prev = t.substr(0, nxt) + s[i];
            for (int j = 0; j <= int(t.size()); ++j) {
                if (dp[j] && cmp(j, nxt, i) == 0) ndp[j] = true;
            }
            ndp[int(prev.size())] = true;
            for (int j = 0; j + int(s[i].size()) < int(prev.size()); ++j) {
                if (dp[j] && can[i + 1][k - int(s[i].size()) - j]){
                    int res;
                    if (j <= nxt) res = cmp2(j, nxt, i);
                    else res = -cmp2(nxt, j, i);
                    if (res == 0) ndp[j + int(s[i].size())] = true;
                }
            }
        }
        std::swap(dp, ndp);
    }
    std::cout << prev << "\n";
    return 0;
}
