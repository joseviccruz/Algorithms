template <class T>
class kosaraju_s_t {
public:
  struct edge_t {
    int to;
    T w;
  };
  int n;
  vector<vector<edge_t>> adj;

  kosaraju_s_t(int n) : n(n) {
    assert(n > 0);
    adj.resize(n);
  }

  void add(int x, int y, T w = 1) {
    adj[x].push_back({y, w});
  }
  
  vector<int> scc() {
    vector<vector<edge_t>> radj(n);
    for (int v = 0; v < n; v++)
      for (edge_t e : adj[v])
        radj[e.to].push_back({v, e.w});
    vector<int> order;
    vector<bool> mark(n);
    function<void(int)> dfs_st = [&](int v) {
      mark[v] = true;
      for (edge_t e : adj[v])
        if (!mark[e.to])
          dfs_st(e.to);
      order.push_back(v);
    };
    for (int i = 0; i < n; i++)
      if (!mark[i])
        dfs_st(i);
    vector<int> component(n);
    component.assign(n, -1);
    function<void(int)> dfs_nd = [&](int v) {
      for (edge_t e : radj[v])
        if (component[e.to] == -1) {
          component[e.to] = component[v];
          dfs_nd(e.to);
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
