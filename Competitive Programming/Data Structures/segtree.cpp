struct node_t {
  int x;
  
  node_t(int _x = 0) {
    x = _x;
  }
  
  node_t(const node_t &lhs, const node_t &rhs) {
    x = max(lhs.x, rhs.x);
  }
};

template <class n_t>
class segtree_t {
  int n;
  vector<n_t> st;
  
  void build() {
    fill(st.begin() + n, st.end(), n_t());
    for (int x = n - 1; x; x--)
      st[x] = n_t(st[x + x], st[x + x + 1]);
  }
  
  template <class T>
  void build(const vector<T> &base) {
    for (int x = 0; x < n; x++)
      st[x + n] = n_t(base[x]);
    for (int x = n - 1; x; x--)
      st[x] = n_t(st[x + x], st[x + x + 1]);
  }

public:
  template <class T>
  void modify(int x, T y) {
    assert(x >= 0 && x < n);
    for (st[x += n] = n_t(y), x >>= 1; x; x >>= 1)
      st[x] = n_t(st[x + x], st[x + x + 1]);
  }
  
  n_t query(int l, int r) {
    assert(l >= 0 && l < n);
    assert(r >= 0 && r < n);
    n_t lhs, rhs;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        lhs = n_t(lhs, st[l++]);
      if (r & 1)
        rhs = n_t(st[--r], rhs);
    }
    return n_t(lhs, rhs);
  }
  
  n_t query(int x) {
    return st[x + n];
  }
  
  segtree_t(int _n) {
    n = _n;
    st.resize(n + n);
    build();
  }
  
  template <typename T>
  segtree_t(const vector<T> &base) {
    n = base.size();
    st.resize(n + n);
    build(base);
  }
};
