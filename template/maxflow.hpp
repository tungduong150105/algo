template <typename T> struct Edge {
  int to;
  T cap;
  Edge(int _to, T _cap) : to(_to), cap(_cap) {}
};

template <typename T> struct MaxFlow {
  int n;
  std::vector<Edge<T>> e;
  std::vector<std::vector<int>> g;
  std::vector<int> cur, dep;
  MaxFlow() {}
  MaxFlow(int _n) { init(_n); }
  void init(int _n) {
    e.clear();
    g.assign(_n, {});
    cur.resize(_n);
    dep.resize(_n);
    n = _n;
  }
  bool bfs(int s, int t) {
    dep.assign(n, -1);
    std::queue<int> que;
    que.push(s);
    dep[s] = 0;
    while (que.size()) {
      int u = que.front();
      que.pop();
      for (int i : g[u]) {
        auto [v, c] = e[i];
        if (c > 0 && dep[v] == -1) {
          dep[v] = dep[u] + 1;
          if (v == t) return true;
          que.push(v);
        }
      }
    }
    return false;
  }
  T dfs(int u, int t, T maxCap) {
    if (u == t) return maxCap;
    T r = maxCap;
    for (int &i = cur[u]; i < int(g[u].size()); ++i) {
      int j = g[u][i];
      auto [v, c] = e[j];
      if (c > 0 && dep[v] == dep[u] + 1) {
        auto a = dfs(v, t, std::min(r, c));
        e[j].cap -= a;
        e[j ^ 1].cap += a;
        r -= a;
        if (!r) return maxCap;
      }
    }
    return maxCap - r;
  }
  void addEdge(int u, int v, T c) {
    g[u].push_back(int(e.size()));
    e.emplace_back(v, c);
    g[v].push_back(int(e.size()));
    e.emplace_back(u, 0);
  }
  T maxFlow(int s, int t) {
    T ans = 0, inf = std::numeric_limits<T>::max() / 2;
    while (bfs(s, t)) {
      cur.assign(n, 0);
      ans += dfs(s, t, inf);
    }
    return ans;
  }
};
