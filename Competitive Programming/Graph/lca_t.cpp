class lca_t {
public:
  int n;
  int max_log;
  vector<int> in, out;
  vector<vector<int>> adj, up;
  
  lca_t(int _n) : n(_n) {
    max_log = 0;
    while ((1 << max_log) <= n)
      max_log++;
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
  
  void add(int x, int y) {
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
};
