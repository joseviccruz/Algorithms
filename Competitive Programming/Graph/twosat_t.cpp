/*
  (    (p xor q)) equals to (    p or q) and (not p or not q)
  (not (p xor q)) equals to (not p or q) and (    p or not q)

  (p or q) equals to (not p implies q) and (not q implies p)

  The edges will correspond to the implications
*/

class twosat_t {
  int n;
  int g_n;
  vector<int> cmp;
  vector<vector<int>> adj;

  void scc() {
    vector<vector<int>> radj(g_n);
    for (int v = 0; v < g_n; v++)
      for (int u : adj[v])
        radj[u].push_back(v);
    vector<int> order;
    vector<bool> mark(g_n);
    function<void(int)> dfs_st = [&](int v) {
      mark[v] = true;
      for (int u : adj[v])
        if (!mark[u])
          dfs_st(u);
      order.push_back(v);
    };
    for (int i = 0; i < g_n; i++)
      if (!mark[i])
        dfs_st(i);
    int cnt = 0;
    cmp.assign(g_n, -1);
    function<void(int)> dfs_nd = [&](int v) {
      for (int u : radj[v])
        if (cmp[u] == -1) {
          cmp[u] = cmp[v];
          dfs_nd(u);
        }
    };
    for (int i = g_n - 1; i >= 0; i--) {
      int v = order[i];
      if (cmp[v] != -1)
        continue;
      cmp[v] = cnt++;
      dfs_nd(v);
    }
  }

public:
  twosat_t(int _n) : n(_n), g_n(_n + _n) {
    assert(n > 0);
    adj.assign(g_n, vector<int>());
  }

  void add(int x, int v_x) {
    assert(x >= 0 && x < n);
    assert(v_x >= 0 && v_x <= 1);
    adj[x + x + (v_x ^ 1)].push_back(x + x + v_x);
  }

  void add(int x, int v_x, int y, int v_y) {
    assert(x >= 0 && x < n && y >= 0 && y < n);
    assert(v_x >= 0 && v_x <= 1 && v_y >= 0 && v_y <= 1);
    adj[x + x + (v_x ^ 1)].push_back(y + y + v_y);
    adj[y + y + (v_y ^ 1)].push_back(x + x + v_x);
  }

  vector<int> solve() {
    scc();
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
      if (cmp[i + i] == cmp[i + i + 1])
        return vector<int>();
      ans[i] = cmp[i + i] < cmp[i + i + 1];
    }
    return ans;
  }
};
