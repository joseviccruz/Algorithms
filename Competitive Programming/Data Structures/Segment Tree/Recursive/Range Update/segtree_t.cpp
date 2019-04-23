struct node_t {
  
  node_t() {
  }

  node_t(const node_t &lhs, const node_t &rhs) {
  }

  template <class l_t>
  void apply(const l_t &lazy) {
  }
};

struct lazy_t {
  
  void assign() {
  }

  void operator += (const lazy_t &o) {
  }

  void reset() {
  }

  int l, r;
  
  lazy_t(int l = 0, int r = 0) : l(l), r(r) {
    assign();
  }
};

template <class n_t, class l_t>
class segtree_t {
  int n;
  vector<n_t> tree;
  vector<l_t> lazy;
  vector<bool> dirty;

  template <class v_t>
  void build(int x, int l, int r, const v_t &base) {
    lazy.emplace_back(l, r);
    if (l == r) {
      tree[x] = n_t(base[l]);
      return;
    }
    int m = (l + r) >> 1;
    int z = x + ((m - l + 1) << 1);
    build(x + 1, l, m, base);
    build(z, m + 1, r, base);
    tree[x] = n_t(tree[x + 1], tree[z]);
  }

  void push(int x, int l, int r) {
    if (dirty[x]) {
      tree[x].apply(lazy[x]);
      int m = (l + r) >> 1;
      int z = x + ((m - l + 1) << 1);
      if (l != r) {
        lazy[x + 1] += lazy[x];
        lazy[z] += lazy[x];
        dirty[x + 1] = true;
        dirty[z] = true;
      }
      lazy[x].reset();
      dirty[x] = false;
    }
  }

  n_t get(int ll, int rr, int x, int l, int r) {
    push(x, l, r);
    if (ll > r || l > rr)
      return n_t();
    if (ll <= l && r <= rr)
      return tree[x];
    int m = (l + r) >> 1;
    int z = x + ((m - l + 1) << 1);
    return n_t(get(ll, rr, x + 1, l, m), get(ll, rr, z, m + 1, r));
  }

  template <class... Args>
  void modify(int ll, int rr, int x, int l, int r, const Args&... args) {
    push(x, l, r);
    if (ll > r || l > rr)
      return;
    if (ll <= l && r <= rr) {
      lazy[x].assign(args...);
      dirty[x] = true;
      push(x, l, r);
      return;
    }
    int m = (l + r) >> 1;
    int z = x + ((m - l + 1) << 1);
    modify(ll, rr, x + 1, l, m, args...);
    modify(ll, rr, z, m + 1, r, args...);
    tree[x] = n_t(tree[x + 1], tree[z]);
  }

public:
  n_t get(int ll, int rr) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    return get(ll, rr, 0, 0, n - 1);
  }

  template <class... Args>
  void modify(int ll, int rr, const Args&... args) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    modify(ll, rr, 0, 0, n - 1, args...);
  }

  template <class v_t>
  segtree_t(const v_t &base) : n(base.size()) {
    tree.resize((n << 1) - 1);
    lazy.reserve((n << 1) - 1);
    dirty.resize((n << 1) - 1);
    build(0, 0, n - 1, base);
  }
  
  segtree_t(int n) : segtree_t(vector<n_t>(n)) {
  }
};
