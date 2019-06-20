template <class T>
class lca_t {
public:
  struct edge_t {
    int to;
    T w;
  };
  int n;
  int max_log;
  vector<int> h, in, out;
  vector<vector<int>> up;
  vector<vector<edge_t>> adj;

  lca_t(int _n) : n(_n) {
    max_log = 0;
    while ((1 << max_log) <= n)
      max_log++;
    h.resize(n);
    in.resize(n);
    out.resize(n);
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

  void add(int x, int y, T w = 1) {
    adj[x].push_back({y, w});
    adj[y].push_back({x, w});
  }

  void set_root(int x) {
    int t = 0;
    h[x] = 0;
    function<void(int, int)> dfs = [&](int v, int p) {
      in[v] = t++;
      up[v][0] = p;
      for (int i = 1; i < max_log; i++)
        up[v][i] = up[up[v][i - 1]][i - 1];
      for (int i = 0; i < (int) adj[v].size(); i++) {
        int u = adj[v][i].to;
        if (u == p)
          continue;
        h[u] = h[v] + 1;
        dfs(u, v);
      }
      out[v] = t - 1;
    };
    dfs(x, x);
  }
};
