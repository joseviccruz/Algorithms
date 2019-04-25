struct node_t {
  
  node_t() {
  }
  
  node_t(const node_t &lhs, const node_t &rhs) {
  }
};

template <class n_t>
class segtree_t {
  int n;
  vector<n_t> tree;

  template <class v_t>
  void build(int x, int l, int r, const v_t &base) {
    if (l == r)
      tree[x] = n_t(base[l]);
    else {
      int m = (l + r) >> 1;
      int z = x + ((m - l + 1) << 1);
      build(x + 1, l, m, base);
      build(z, m + 1, r, base);
      tree[x] = n_t(tree[x + 1], tree[z]);
    }
  }

  n_t get(int ll, int rr, int x, int l, int r) {
    if (ll <= l && r <= rr)
      return tree[x];
    int m = (l + r) >> 1;
    int z = x + ((m - l + 1) << 1);
    n_t ans{};
    if (rr <= m)
      ans = get(ll, rr, x + 1, l, m);
    else if (ll > m)
      ans = get(ll, rr, z, m + 1, r);
    else
      ans = n_t(get(ll, rr, x + 1, l, m), get(ll, rr, z, m + 1, r));
    return ans;
  }

  template <class... Args>
  void modify(int p, int x, int l, int r, const Args&... args) {
    if (p > r || l > p)
      return;
    if (l == r)
      tree[x] = n_t(args...);
    else {
      int m = (l + r) >> 1;
      int z = x + ((m - l + 1) << 1);
      modify(p, x + 1, l, m, args...);
      modify(p, z, m + 1, r, args...);
      tree[x] = n_t(tree[x + 1], tree[z]);
    }
  }

public:
  n_t get(int ll, int rr) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    return get(ll, rr, 0, 0, n - 1);
  }

  template <class... Args>
  void modify(int x, const Args&... args) {
    assert(0 <= x <= n - 1);
    modify(x, 0, 0, n - 1, args...);
  }

  template <class v_t>
  segtree_t(const v_t &base) : n(base.size()) {
    tree.resize((n << 1) - 1);
    build(0, 0, n - 1, base);
  }
  
  segtree_t(int n) : segtree_t(vector<n_t>(n)) {
  }
};
