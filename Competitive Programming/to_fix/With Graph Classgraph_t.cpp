/*
int n;
struct edge_t {
  int to;
  T w;
};
vector<vector<edge_t>> adj;
*/

template <class T>
class graph_t {
public:
  int n;
  struct edge_t {
    int to;
    T w;
  };
  vector<vector<edge_t>> adj;
  bool directed;

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
