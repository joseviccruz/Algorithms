class kosaraju_s_t {
public:
  int n;
  vector<vector<int>> adj;

  kosaraju_s_t(int n) : n(n) {
    assert(n > 0);
    adj.resize(n);
  }

  void add(int x, int y) {
    adj[x].push_back(y);
  }
  
  vector<int> scc() {
    vector<vector<int>> radj(n);
    for (int v = 0; v < n; v++)
      for (int u : adj[v])
        radj[u].push_back(v);
    vector<int> order;
    vector<bool> mark(n);
    function<void(int)> dfs_st = [&](int v) {
      mark[v] = true;
      for (int u : adj[v])
        if (!mark[u])
          dfs_st(u);
      order.push_back(v);
    };
    for (int i = 0; i < n; i++)
      if (!mark[i])
        dfs_st(i);
    vector<int> component(n);
    component.assign(n, -1);
    function<void(int)> dfs_nd = [&](int v) {
      for (int u : radj[v])
        if (component[u] == -1) {
          component[u] = component[v];
          dfs_nd(u);
        }
    };
    int cnt = 0;
    for (int i = n - 1; i >= 0; i--) {
      int v = order[i];
      if (component[v] != -1)
        continue;
      component[v] = cnt++;
      dfs_nd(v);
    }
    return component;
  }
};
