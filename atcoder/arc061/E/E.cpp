#include "bits/stdc++.h"

struct DSU {
    std::vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }
    int find(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (siz[x] < siz[y]) std::swap(x, y);
        f[y] = x, siz[x] += siz[y];
        return true;
    }
    int size(int x) { return siz[find(x)]; }
    bool same(int x, int y) { return find(x) == find(y); }
};

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; std::cin >> n >> m;
    constexpr int C = 1000000;
    std::vector edges(C, std::vector<std::pair<int, int>> ());
    for (int i = 0; i < m; ++i) {
        int u, v, c; std::cin >> u >> v >> c;
        --u, --v;
        edges[c].emplace_back(u, v);
    }
    int cnt = 0;
    DSU dsu(n);
    std::vector inComponent(n, std::vector<int> ());
    for (int c = 1; c <= C; ++c) {
        std::vector<int> vertices;
        for (auto [u, v] : edges[c]) {
            vertices.push_back(u);
            vertices.push_back(v);
            dsu.merge(u, v);
        }
        std::map<int, int> mp;
        std::sort(vertices.begin(), vertices.end());
        vertices.erase(std::unique(vertices.begin(), vertices.end()), vertices.end());
        for (int u : vertices) {
            int lead = dsu.find(u);
            if (!mp.count(lead)) mp[lead] = cnt++;
            inComponent[u].push_back(mp[lead]);
        }
        for (int u : vertices) dsu.f[u] = u;
    }
    std::vector adj(n + cnt, std::vector<int> ());
    for (int u = 0; u < n; ++u) {
        for (int v : inComponent[u]) {
            adj[u].push_back(n + v);
            adj[n + v].push_back(u);
        }
    }
    std::queue<int> bfs;
    bfs.push(0);
    constexpr int inf = std::numeric_limits<int>::max() / 2;
    std::vector<int> d(n + cnt, inf);
    d[0] = 0;
    while (bfs.size()) {
        int u = bfs.front();
        bfs.pop();
        for (int v : adj[u]) {
            if (d[v] > d[u] + 1) {
                d[v] = d[u] + 1;
                bfs.push(v);
            }
        }
    }
    if (d[n - 1] == inf) std::cout << "-1\n";
    else std::cout << d[n - 1] / 2 << "\n";
    return 0;
}
