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
  
  lazy_t() {
  }
  
  void operator += (const lazy_t &o) {
  }

  void reset() {
  }
};

template <class n_t, class l_t>
class segtree_t {
  int n, h;
  vector<n_t> tree;
  vector<l_t> lazy;
  vector<bool> dirty;
  
  void build() {
    for (int x = n - 1; x > 0; x--)
      tree[x] = n_t(tree[x + x], tree[x + x + 1]);
  }

  void update(int x) {
    for (x >>= 1; x > 0; x >>= 1) {
      tree[x] = n_t(tree[x + x], tree[x + x + 1]);
      if (dirty[x])
        tree[x].apply(lazy[x]);
    }
  }

  void push(int z) {
    for (int y = h; y > 0; y--) {
      int x = z >> y;
      if (dirty[x]) {
        apply(x + x, lazy[x]);
        apply(x + x + 1, lazy[x]);
        lazy[x].reset();
        dirty[x] = false;
      }
    }
  }
  
  template <class... Args>
  void apply(int x, const Args&... args) {
    tree[x].apply(l_t(args...));
    if (x < n) {
      lazy[x] += l_t(args...);
      dirty[x] = true;
    }
  }

public:
  n_t get(int l, int r) {
    assert(0 <= l && l <= n - 1 && 0 <= r && r <= n - 1);
    l += n, r += n + 1;
    n_t lhs{}, rhs{};
    for (push(l), push(r - 1); l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        lhs = n_t(lhs, tree[l++]);
      if (r & 1)
        rhs = n_t(tree[--r], rhs);
    }
    return n_t(lhs, rhs);
  }
  
  template <class... Args>
  void modify(int l, int r, const Args&... args) {
    assert(0 <= l && l <= n - 1 && 0 <= r && r <= n - 1);
    l += n, r += n + 1;
    int ll = l, rr = r;
    for (push(l), push(r - 1); l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        apply(l++, args...);
      if (r & 1)
        apply(--r, args...);
    }
    update(ll);
    update(rr - 1);
  }
  
  template <class v_t>
  segtree_t(const v_t &base) : n(base.size()), h(0) {
    while ((1 << h) < n)
      h++;
    tree.resize(n);
    lazy.resize(n);
    dirty.resize(n);
    copy(base.begin(), base.end(), back_inserter(tree));
    build();
  }
  
  segtree_t(int n) : segtree_t(vector<n_t>(n)) {
  }
};
