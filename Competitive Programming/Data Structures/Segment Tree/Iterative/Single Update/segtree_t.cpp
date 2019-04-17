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
  
  void build() {
    for (int x = n - 1; x > 0; x--)
      tree[x] = n_t(tree[x + x], tree[x + x + 1]);
  }

public:
  segtree_t(int _n) : n(_n), tree(_n + _n) {
    assert(n > 0);
    build();
  }
  
  template <class v_t>
  segtree_t(const v_t &base) : n(base.size()), tree(base.size()) {
    assert(n > 0);
    copy(base.begin(), base.end(), back_inserter(tree));
    build();
  }

  template <class... Args>
  void modify(int x, Args&&... args) {
    assert(x >= 0 && x <= n - 1);
    for (tree[x += n] = n_t(args...), x >>= 1; x > 0; x >>= 1)
      tree[x] = n_t(tree[x + x], tree[x + x + 1]);
  }
  
  n_t get(int l, int r) {
    assert(0 <= l && l <= r && r <= n - 1);
    n_t lhs{}, rhs{};
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        lhs = n_t(lhs, tree[l++]);
      if (r & 1)
        rhs = n_t(tree[--r], rhs);
    }
    return n_t(lhs, rhs);
  }
  
  n_t get(int x) {
    assert(x >= 0 && x <= n - 1);
    return tree[x + n];
  }
};
