#include "bits/stdc++.h"
#include <unordered_map>

using i64 = long;

#define dbg(...) 1501

int a[400][4];
int up[4], down[4], LF[4], RT[4], rot[4];

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    std::unordered_map<i64, int> mp;
    auto add = [&](const int &a, const int &b, const int &c, const int &d) {
        ++mp[1000000000L * a + 1000000 * b + 1000 * c + d];
        ++mp[1000000000L * b + 1000000 * c + 1000 * d + a];
        ++mp[1000000000L * c + 1000000 * d + 1000 * a + b];
        ++mp[1000000000L * d + 1000000 * a + 1000 * b + c];
    };
    auto del = [&](const int &a, const int &b, const int &c, const int &d) -> int {
        int value = --mp[1000000000L * a + 1000000 * b + 1000 * c + d];
        --mp[1000000000L * b + 1000000 * c + 1000 * d + a];
        --mp[1000000000L * c + 1000000 * d + 1000 * a + b];
        --mp[1000000000L * d + 1000000 * a + 1000 * b + c];
        return value + 1;
    };
    int n; std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i][0] >> a[i][1] >> a[i][2] >> a[i][3];
        add(a[i][0], a[i][1], a[i][2], a[i][3]);
    }
    i64 ans = 0;
    for (int i = 0; i < n; ++i) {
        del(a[i][0], a[i][1], a[i][2], a[i][3]);
        for (int j = i + 1; j < n; ++j) {
            del(a[j][0], a[j][1], a[j][2], a[j][3]);
            for (int rot2 = 0; rot2 < 4; ++rot2) {
                for (int _ = 0; _ < 4; ++_) rot[_] = a[j][(_ + 1) % 4];
                for (int _ = 0; _ < 4; ++_) a[j][_] = rot[_];
                // if ((!rot && rot2 < rot) || (rot && rot2 <= rot)) continue;
                // std::vector<int> up = {a[j][1], a[j][0], a[i][1], a[i][0]};
                // std::vector<int> down = {a[i][3], a[i][2], a[j][3], a[j][2]};
                // std::vector<int> LF = {a[j][1], a[i][0], a[i][3], a[j][2]};
                // std::vector<int> RT = {a[i][1], a[j][0], a[j][3], a[i][2]};
                up[0] = a[j][1], up[1] = a[j][0], up[2] = a[i][1], up[3] = a[i][0];
                down[0] = a[i][3], down[1] = a[i][2], down[2] = a[j][3], down[3] = a[j][2];
                LF[0] = a[j][1], LF[1] = a[i][0], LF[2] = a[i][3], LF[3] = a[j][2];
                RT[0] = a[i][1], RT[1] = a[j][0], RT[2] = a[j][3], RT[3] = a[i][2];
                dbg(a[i]);
                dbg(a[j]);
                dbg(up);
                dbg(down);
                dbg(LF);
                dbg(RT);
                i64 res = 1;
                res *= del(up[0], up[1], up[2], up[3]);
                res *= del(down[0], down[1], down[2], down[3]);
                res *= del(LF[0], LF[1], LF[2], LF[3]);
                res *= del(RT[0], RT[1], RT[2], RT[3]);
                ans += res;
                add(up[0], up[1], up[2], up[3]);
                add(down[0], down[1], down[2], down[3]);
                add(LF[0], LF[1], LF[2], LF[3]);
                add(RT[0], RT[1], RT[2], RT[3]);
            }
            add(a[j][0], a[j][1], a[j][2], a[j][3]);
        }
        add(a[i][0], a[i][1], a[i][2], a[i][3]);
    }
    std::cout << ans / 3 << "\n";
    return 0;
}
