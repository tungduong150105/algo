#include "bits/stdc++.h"

using i64 = long long;

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int x, y, x2, y2; std::cin >> x >> y >> x2 >> y2;
    int n; std::cin >> n;
    std::vector<std::tuple<int, int, int>> a;
    for (int i = 0; i < n; ++i) {
        int _x, _y, r; std::cin >> _x >> _y >> r;
        a.emplace_back(_x, _y, r);
    }
    a.emplace_back(x, y, 0);
    a.emplace_back(x2, y2, 0);
    n += 2;
    std::vector adj(n, std::vector<std::pair<int, double>> ());
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            auto [_x, _y, r] = a[i];
            auto [_x2, _y2, r2] = a[j];
            double distance = std::sqrt(double(i64(_x - _x2) * (_x - _x2) + i64(_y - _y2) * (_y - _y2)));
            double fill = r + r2;
            adj[i].push_back({j, std::max(0.0, distance - fill)});
        }
    }
    constexpr double inf = 1E18;
    std::vector<double> d(n, inf);
    d[n - 2] = 0;
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> pq;
    pq.push({0, n - 2});
    constexpr double eps = 1e-9;
    while (pq.size()) {
        auto [du, u] = pq.top();
        pq.pop();
        if (std::abs(d[u] - du) > eps) continue;
        for (auto [v, c] : adj[u]) {
            if (d[v] - (d[u] + c) > eps) {
                d[v] = d[u] + c;
                pq.push({d[v], v});
            }
        }
    }
    std::cout << std::fixed << std::setprecision(10) << d[n - 1] << "\n";
    return 0;
}
