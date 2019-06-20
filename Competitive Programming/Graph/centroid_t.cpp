template <class T>
class centroid_t {
public:
  struct edge_t {
    int to;
    T w;
  };
  int n;
  vector<int> sz;
  vector<bool> removed;
  vector<vector<edge_t>> adj;

  centroid_t(int n) : n(n) {
    sz.resize(n);
    removed.resize(n);
    adj.resize(n);
  }

  void add(int x, int y, T w = 1) {
    assert(0 <= x && x <= n - 1 && 0 <= y && y <= n - 1);
    adj[x].push_back({y, w});
    adj[y].push_back({x, w});
  }

  void dfs(int v, int p) {
    sz[v] = 1;
    for (edge_t e : adj[v]) {
      if (e.to == p || removed[e.to])
        continue;
      dfs(e.to, v);
      sz[v] += sz[e.to];
    }
  }

  int next_centroid(int v, int p, int m) {
    for (edge_t e : adj[v]) {
      if (e.to == p || removed[e.to])
        continue;
      if (sz[e.to] + sz[e.to] > m)
        return next_centroid(e.to, v, m);
    }
    return v;
  }

  vector<int> decompose(int v, int p) {
    vector<int> parents(n, -1); // -1 are unreachable nodes
    function<void(int, int)> dfs_ctrtree = [&](int v, int p) {
      dfs(v, v);
      int u = next_centroid(v, v, sz[v]);
      if (p == v) {
        p = u;
      }
      parents[u] = p;
      removed[u] = true;
      for (edge_t e : adj[u]) {
        if (e.to == p || removed[e.to])
          continue;
        dfs_ctrtree(e.to, u);
      }
    };
    dfs_ctrtree(v, p);
    return parents;
  }
};
