template <class T>
class graph_t {
public:
  struct data_t {
    int to;
    T w;
  };
  int n;
  bool directed;
  vector<vector<data_t>> adj;
  
  graph_t(int n, bool d = false) : n(n), directed(d) {
    assert(n > 0);
    adj.resize(n);
  }
  
  void add(int x, int y, T w = 1) {
    adj[x].push_back({y, w});
    if (not directed)
      adj[y].push_back({x, w});
  }
};
