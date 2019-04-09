#include <bits/stdc++.h>

using namespace std;

class lca_t {
public:
  int n;
  int max_log;
  vector<int> h, in, out;
  vector<vector<int>> adj, up;

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

  void add(int x, int y) {
    adj[x].push_back(y);
    adj[y].push_back(x);
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
        int u = adj[v][i];
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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> p(n), mex_p(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i];
    mex_p[p[i]] = i;
  }
  static lca_t g(n);
  for (int i = 1; i < n; i++) {
    int j;
    cin >> j;
    j--;
    g.add(i, j);
  }
  g.set_root(0);
  struct node_t {
    int m_l, m_r;
    
    node_t(int x = -1) : m_l(x), m_r(x) {
    }
    
    node_t(int l, int r) : m_l(l), m_r(r) {
    }
    
    node_t(const node_t &lhs, const node_t &rhs) {
      node_t ret;
      if (lhs.m_l != -1 && rhs.m_l != -1) {
        ret = merge(lhs.m_l, lhs.m_r, rhs.m_l);
        if (ret.m_l != -1)
          ret = merge(ret.m_l, ret.m_r, rhs.m_r);
      }
      *this = ret;
    }
    
    node_t merge(int l, int m, int r) {
      int lm = g.h[l] + g.h[m] - 2 * g.h[g.lca(l, m)], &ml = lm;
      int lr = g.h[l] + g.h[r] - 2 * g.h[g.lca(l, r)], &rl = lr;
      int mr = g.h[m] + g.h[r] - 2 * g.h[g.lca(m, r)], &rm = mr;
      if (lm + mr == lr)
        return node_t(l, r);
      if (lr + rm == lm)
        return node_t(l, m);
      if (ml + lr == mr)
        return node_t(m, r);
      return node_t(-1, -1);
    }
  };
  vector<node_t> tree(n + n - 1);
  function<void(int, int, int, int, int)>
  modify = [&](int p, int node, int x, int l, int r) -> void {
    if (p > r || l > p)
      return;
    if (l == r) {
      tree[x] = node_t(node);
      return;
    }
    int m = (l + r) >> 1;
    int z = x + ((m - l + 1) << 1);
    modify(p, node, x + 1, l, m);
    modify(p, node, z, m + 1, r);
    tree[x] = node_t(tree[x + 1], tree[z]);
  };
  function<int(node_t, int, int, int)>
  get = [&](node_t node, int x, int l, int r) -> int {
    if (l == r)
      return l;
    node_t temp = node_t(node, tree[x + 1]);
    int m = (l + r) >> 1;
    int z = x + ((m - l + 1) << 1);
    if (temp.m_l == -1)
      return get(node, x + 1, l, m);
    return get(temp, z, m + 1, r);
  };
  for (int i = 0; i < n; i++)
    modify(i, mex_p[i], 0, 0, n - 1);
  int q;
  cin >> q;
  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int l, r;
      cin >> l >> r;
      --l, --r;
      swap(p[l], p[r]);
      swap(mex_p[p[l]], mex_p[p[r]]);
      modify(p[l], mex_p[p[l]], 0, 0, n - 1);
      modify(p[r], mex_p[p[r]], 0, 0, n - 1);
      continue;
    }
    cout << ((tree[0].m_l == -1) ? get(node_t(mex_p[0]), 0, 0, n - 1) : n) << '\n';
  }
  return 0;
}
