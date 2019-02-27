class hld_t {
public:
  int n;
  int max_log;
  vector<vector<int>> adj, up;
  vector<int> in, rin, out, nxt;
  
  hld_t(int _n) : n(_n) {
    assert(n > 0);
    max_log = 0;
    while ((1 << max_log) <= n)
      max_log++;
    in.resize(n);
    rin.resize(n);
    out.resize(n);
    nxt.resize(n);
    adj.resize(n);
    up.resize(n, vector<int>(max_log));
  }
  
  bool anc(int x, int y) {
    return in[x] <= in[y] && out[x] >= out[y];
  }

  int lca(int x, int y) {
    if (anc(x, y))
      return x;
    if (anc(y, x))
      return y;
    for (int i = max_log - 1; i >= 0; i--)
      if (!anc(up[x][i], y))
        x = up[x][i];
    return up[x][0];
  }
  
  void add(int x, int y) {
    assert(0 <= x && x <= n - 1 && 0 <= y && y <= n - 1);
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  void set_root(int x) {
    assert(0 <= x && x <= n - 1);
    vector<int> sz(n);
    function<void(int, int)> dfs_sz = [&](int v, int p) {
      sz[v] = 1;
      for (int i = 0; i < (int) adj[v].size(); i++) {
        int u = adj[v][i];
        int a = adj[v][0];
        if (u == p)
          continue;
        dfs_sz(u, v);
        sz[v] += sz[u];
        if (p == a || sz[u] > sz[a])
          swap(adj[v][0], adj[v][i]);
      }
    };
    dfs_sz(x, x);
    int t = 0;
    function<void(int, int)> dfs_hld = [&](int v, int p) {
      in[v] = t++;
      rin[in[v]] = v;
      up[v][0] = p;
      for (int i = 1; i < max_log; i++)
        up[v][i] = up[up[v][i - 1]][i - 1];
      for (int i = 0; i < (int) adj[v].size(); i++) {
        int u = adj[v][i];
        if (u == p)
          continue;
        nxt[u] = (i == 0) ? nxt[v] : u;
        dfs_hld(u, v);
      }
      out[v] = t;
    };
    dfs_hld(x, x);
  }

  vector<pair<int, int>> get(int x, int y, bool with_ancestor = true) {
    assert(0 <= x && x <= n - 1 && 0 <= y && y <= n - 1);
    vector<pair<int, int>> path[2];
    int z = lca(x, y);
    for (int id = 0; id < 2; id++) {
      int v = (id == 0 ? x : y);
      for (; nxt[v] != nxt[z]; v = up[nxt[v]][0])
        path[id].emplace_back(in[nxt[v]], in[v]);
      if (in[z] + (!with_ancestor) <= in[v])
        path[id].emplace_back(in[z] + (!with_ancestor), in[v]);
    }
    vector<pair<int, int>> ret;
    for (auto p : path[0])
      ret.emplace_back(p.second, p.first);
    ret.emplace_back(-1, in[z]);
    copy(path[1].rbegin(), path[1].rend(), back_inserter(ret));
    return ret;
  }
};
