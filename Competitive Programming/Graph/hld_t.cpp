// get will return pairs in order of the path
template <class T>
class hld_t {
public:
  struct edge_t {
    int from;
    int to;
    T data;
    edge_t(int x, int y, T d = T()) : from(x), to(y), data(d) {
    }
  };
  int n;
  int max_log;
  bool preprocessed;
  vector<edge_t> edges;
  vector<vector<int>> adj, up;
  vector<int> in, rin, out, nxt, &pos = in;
  
  int &parent(int x) {
    return up[x][0];
  }
  
  hld_t(int _n) : n(_n), max_log(0), preprocessed(false) {
    assert(n > 0);
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
  
  void add(int x, int y, T d = T()) {
    assert(x >= 0 && x < n && y >= 0 && y < n);
    int id = edges.size();
    adj[x].push_back(id);
    adj[y].push_back(id);
    edges.emplace_back(x, y, d);
  }

  int edge_id(int e) {
    assert(e >= 0 && e < edges.size());
    int x = edges[e].from;
    int y = edges[e].to;
    return parent(x) == y ? pos[x] : pos[y];
  }

  void set_root(int x) {
    assert(x >= 0 && x < n);
    assert(n - 1 == edges.size());
    vector<int> sz(n);
    function<void(int, int)> dfs_sz = [&](int v, int p) {
      sz[v] = 1;
      for (int i = 0; i < (int) adj[v].size(); i++) {
        int u = edges[adj[v][i]].from ^ edges[adj[v][i]].to ^ v;
        int a = edges[adj[v][0]].from ^ edges[adj[v][0]].to ^ v;
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
        int u = edges[adj[v][i]].from ^ edges[adj[v][i]].to ^ v;
        if (u == p)
          continue;
        nxt[u] = (i == 0) ? nxt[v] : u;
        dfs_hld(u, v);
      }
      out[v] = t;
    };
    dfs_hld(x, x);
    preprocessed = true;
  }

  vector<pair<int, int>> get(int x, int y, bool with_ancestor = true) {
    assert(preprocessed);
    array<vector<pair<int, int>>, 2> path;
    int z = lca(x, y);
    for (int id = 0; id < 2; id++) {
      int v = (id == 0 ? x : y);
      while (nxt[v] != nxt[z]) {
        path[id].emplace_back(pos[nxt[v]], pos[v]);
        v = parent(nxt[v]);
      }
      if (pos[z] + ((int) !with_ancestor) <= pos[v])
        path[id].emplace_back(pos[z] + ((int) !with_ancestor), pos[v]);
    }
    vector<pair<int, int>> ret;
    for (auto p : path[0])
      ret.emplace_back(p.second, p.first);
    ret.emplace_back(-1, pos[z]);
    reverse(path[1].begin(), path[1].end());
    for (auto p : path[1])
      ret.push_back(p);
    return ret;
  }
  
  vector<pair<int, int>> get_path(int x, int y, int with_ancestor = true) {
    auto ret = get(x, y, with_ancestor);
    for (auto &p : ret) {
      p.first = (p.first == -1) ? p.first : rin[p.first];
      p.second = (p.second == -1) ? p.second : rin[p.second];
    }
    return ret;
  }
};
