struct node_t {
  
  node_t() {
  }
  
  node_t(const node_t &lhs, const node_t &rhs) {
  }
};

template <class n_t>
class psegtree_t {
  struct range_t { int l, r; };
  int n;
  int z;
  vector<n_t> tree;
  vector<int> ptr;
  vector<range_t> v;

  void new_() {
    tree.emplace_back();
    v.emplace_back();
  }

  template <class T>
  void build(int x, int l, int r, const vector<T> &base) {
    new_();
    if (l == r)
      tree[x] = n_t(base[l]);
    else {
      int m = (l + r) / 2;
      v[x].l = z++;
      build(v[x].l, l, m, base);
      v[x].r = z++;
      build(v[x].r, m + 1, r, base);
      tree[x] = n_t(tree[v[x].l], tree[v[x].r]);
    }
  }

  n_t get(int ll, int rr, int x, int l, int r) {
    if (l > rr || ll > r)
      return n_t();
    if (ll <= l && r <= rr)
      return tree[x];
    int m = (l + r) / 2;
    return n_t(get(ll, rr, v[x].l, l, m), get(ll, rr, v[x].r, m + 1, r));
  }
  
  template <class... Args>
  int modify(int p, int x, int l, int r, Args&... args) {
    if (l > p || p > r)
      return x;
    new_();
    if (l == r) {
      tree[z] = n_t(args...);
      return z++;
    }
    int m = (l + r) / 2;
    int nl = modify(p, v[x].l, l, m, args...);
    int nr = modify(p, v[x].r, m + 1, r, args...);
    v[z].l = nl;
    v[z].r = nr;
    tree[z] = n_t(tree[v[z].l], tree[v[z].r]);
    return z++;
  }

public:
  n_t get(int v, int ll, int rr) {
    assert(0 <= v && v < ptr.size());
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    return get(ll, rr, ptr[v], 0, n - 1);
  }

  template <class... Args>
  int modify(int v, int p, Args&... args) {
    assert(0 <= v && v < ptr.size());
    assert(0 <= p && p <= n - 1);
    ptr.push_back(modify(p, ptr[v], 0, n - 1, args...));
    return ptr.back();
  }

  template <class T>
  psegtree_t(const vector<T> &base, int m = 0) : n(base.size()) {
    assert(m >= 0);
    z = 1;
    tree.reserve(m);
    v.reserve(m);
    build(0, 0, n - 1, base);
    ptr.assign(1, 0);
  }
  
  psegtree_t(int n, int m = 0) : psegtree_t(vector<n_t>(n), m) {
  }
};
