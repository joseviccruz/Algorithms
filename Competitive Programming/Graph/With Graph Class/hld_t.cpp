template <class T>
class hld_t {
public:
  graph_t<T> &g;
  int max_log;
  vector<vector<int>> up;
  vector<int> in, rin, out, nxt;

  hld_t(graph_t<T> &_g) : g(_g) {
    max_log = 0;
    while ((1 << max_log) <= g.n)
      max_log++;
    in.resize(g.n);
    rin.resize(g.n);
    out.resize(g.n);
    nxt.resize(g.n);
    up.resize(g.n, vector<int>(max_log));
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

  void set_root(int x) {
    assert(0 <= x && x <= g.n - 1);
    vector<int> sz(g.n);
    function<void(int, int)> dfs_sz = [&](int v, int p) {
      sz[v] = 1;
      for (int i = 0; i < (int) g.adj[v].size(); i++) {
        int u = g.adj[v][i].to;
        int a = g.adj[v][0].to;
        if (u == p)
          continue;
        dfs_sz(u, v);
        sz[v] += sz[u];
        if (p == a || sz[u] > sz[a])
          swap(g.adj[v][0], g.adj[v][i]);
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
      for (int i = 0; i < (int) g.adj[v].size(); i++) {
        int u = g.adj[v][i].to;
        if (u == p)
          continue;
        nxt[u] = (i == 0) ? nxt[v] : u;
        dfs_hld(u, v);
      }
      out[v] = t - 1;
    };
    dfs_hld(x, x);
  }

  vector<pair<int, int>> get(int x, int y, bool with_ancestor = true) {
    assert(0 <= x && x <= g.n - 1 && 0 <= y && y <= g.n - 1);
    vector<pair<int, int>> path[2];
    int z = lca(x, y);
    for (int id = 0; id < 2; id++) {
      int v = (id == 0 ? x : y);
      while (nxt[v] != nxt[z]) {
        path[id].emplace_back(in[nxt[v]], in[v]);
        v = up[nxt[v]][0];
      }
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
