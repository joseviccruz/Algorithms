/*
      (p xor q) equals to (    p or q) and (not p or not q)
  not (p xor q) equals to (not p or q) and (    p or not q)

  (p or q) equals to (not p implies q) and (not q implies p)

  The edges will correspond to the implications
*/

class twosat_t {
  int n;
  int g_n;
  vector<bool> mark;
  vector<int> order, cmp;
  vector<vector<int>> adj, radj;

  void dfs_st(int v) {
    mark[v] = true;
    for (int u : adj[v])
      if (!mark[u])
        dfs_st(u);
    order.push_back(v);
  }

  void dfs_nd(int v) {
    for (int u : radj[v])
      if (cmp[u] == -1) {
        cmp[u] = cmp[v];
        dfs_nd(u);
      }
  }

  void scc() {
    for (int i = 0; i < g_n; i++)
      if (!mark[i])
        dfs_st(i);
    int cnt = 0;
    cmp.assign(g_n, -1);
    for (int i = g_n - 1; i >= 0; i--) {
      int v = order[i];
      if (cmp[v] != -1)
        continue;
      cmp[v] = cnt++;
      dfs_nd(v);
    }
  }

public:
  twosat_t(int _n) : n(_n), g_n(2 * _n) {
    adj.assign(g_n, vector<int>());
  }

  void add(int x, int v_x) {
    assert(x >= 0 && x < n);
    assert(v_x >= 0 && v_x <= 1);
    adj[2 * x + (v_x ^ 1)].push_back(2 * x + v_x);
  }

  void add(int x, int v_x, int y, int v_y) {
    assert(x >= 0 && x < n && y >= 0 && y < n);
    assert(v_x + v_y >= 0 && v_x + v_y <= 2);
    adj[2 * x + (v_x ^ 1)].push_back(2 * y + v_y);
    adj[2 * y + (v_y ^ 1)].push_back(2 * x + v_x);
  }

  vector<int> solve() {
    order.clear();
    mark.assign(g_n, false);
    radj.assign(g_n, vector<int>());
    for (int v = 0; v < g_n; v++)
      for (int u : adj[v])
        radj[u].push_back(v);
    scc();
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
      if (cmp[2 * i] == cmp[2 * i + 1])
        return vector<int>();
      ans[i] = cmp[2 * i] < cmp[2 * i + 1];
    }
    return ans;
  }
};
