struct SCC {
  int n;
  int scc_cnt = -1;
  std::vector<int> used, topo, cmp;
  std::vector<std::vector<int>> adj, radj;
  SCC() {}
  SCC(int _n) { init(_n); }
  void init(int _n) {
    n = _n;
    adj.resize(n);
    radj.resize(n);
    cmp.resize(n);
  }
  void _dfs(int u) {
    used[u] = true;
    for (int v : adj[u]) {
      if (used[v]) continue;
      _dfs(v);
    }
    topo.push_back(u);
  }
  void _rdfs(int u) {
    used[u] = true;
    for (int v : radj[u]) {
      if (used[v]) continue;
      _rdfs(v);
    }
    cmp[u] = scc_cnt;
  }
  void add_edges(int u, int v) {
    adj[u].push_back(v);
    radj[v].push_back(u);
  }
  int FindSCC() {
    used.assign(n, false);
    topo.clear();
    for (int u = 0; u < n; ++u) {
      if (used[u]) continue;
      _dfs(u);
    }
    used.assign(n, false);
    scc_cnt = 0;
    for (int i = int(topo.size()) - 1; i >= 0; --i) {
      if (used[topo[i]]) continue;
      _rdfs(topo[i]);
      ++scc_cnt;
    }
    return scc_cnt;
  }
};
