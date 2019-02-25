template <class T>
class dinic_t {
public:
  static constexpr T eps = 1e-9;
  static constexpr T inf = numeric_limits<T>::max() / 2;
  struct edge_t {
    int from, to;
    T c, f;
  };
  int n;
  vector<edge_t> edges;
  vector<vector<int>> adj;
  vector<int> h, q, ptr;
  
  dinic_t(int n) : n(n) {
    h.resize(n);
    q.resize(n);
    ptr.resize(n);
    adj.resize(n);
  }
  
  void add(int v, int u, T c = 1, T d = 0) {
    adj[v].push_back(edges.size());
    edges.push_back({v, u, c, 0});
    adj[u].push_back(edges.size());
    edges.push_back({u, v, d, 0});
  }
  
  bool bfs(int v, int u) {
    fill(h.begin(), h.end(), -1);
    h[v] = 0;
    q[0] = v;
    int l = 0, r = 1;
    while (l < r) {
      v = q[l++];
      for (int id : adj[v]) {
        edge_t e = edges[id];
        if (e.c - e.f <= eps || h[e.to] != -1)
          continue;
        h[e.to] = h[v] + 1;
        if (e.to == u)
          return true;
        q[r++] = e.to;
      }
    }
    return false;
  }
  
  T dfs(int v, int u, T w) {
    if (v == u)
      return w;
    int &p = ptr[v];
    while (p >= 0) {
      edge_t e = edges[adj[v][p]];
      if (h[e.to] == h[v] + 1 && e.c - e.f > eps) {
        T flow = dfs(e.to, u, min(w, e.c - e.f));
        if (flow > eps) {
          edges[adj[v][p]].f += flow;
          edges[adj[v][p] ^ 1].f -= flow;
          return flow;
        }
      }
      p--;
    }
    return 0;
  }
  
  T get(int v, int u, bool random_edges = false) {
    T ret{};
    while (bfs(v, u)) {
      for (int i = 0; i < n; i++) {
        ptr[i] = (int) adj[i].size() - 1;
        if (random_edges)
          shuffle(adj[i].begin(), adj[i].end(), rng);
      }
      T flow;
      while (flow = dfs(v, u, inf))
        ret += flow;
    }
    return ret;
  }
};
