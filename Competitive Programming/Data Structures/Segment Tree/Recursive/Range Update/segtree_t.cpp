struct node_t {
  
  node_t() {
  }

  node_t(const node_t &lhs, const node_t &rhs) {
  }

  template <class l_t>
  void apply(const l_t &lazy) {
  }
};

struct lazy_t { int x, l, r;

  void assign() {
  }

  void operator += (const lazy_t &o) {
  }

  void clear() {
  }
};

template <class n_t, class l_t>
class segtree_t {
  int n;
  vector<n_t> tree;
  vector<l_t> lazy;
  vector<bool> dirty;

  void build(int x, int l, int r) {
    lazy[x] = {x, l, r};
    if (l == r)
      return;
    int m = (l + r) / 2;
    build(x + x, l, m);
    build(x + x + 1, m + 1, r);
    tree[x] = n_t(tree[x + x], tree[x + x + 1]);
  }

  template <class T>
  void build(int x, int l, int r, const vector<T> &base) {
    lazy[x] = {x, l, r};
    if (l == r) {
      tree[x] = n_t(base[l]);
      return;
    }
    int m = (l + r) / 2;
    build(x + x, l, m);
    build(x + x + 1, m + 1, r);
    tree[x] = n_t(tree[x + x], tree[x + x + 1]);
  }

  void push(int x, int l, int r) {
    if (dirty[x]) {
      tree[x].apply(lazy[x]);
      if (l != r) {
        lazy[x + x] += lazy[x];
        lazy[x + x + 1] += lazy[x];
        dirty[x + x] = true;
        dirty[x + x + 1] = true;
      }
      lazy[x].clear();
      dirty[x] = false;
    }
  }

  template <class... Args>
  void modify(int ll, int rr, int x, int l, int r, Args&... args) {
    push(x, l, r);
    if (ll > r || l > rr)
      return;
    if (ll <= l && r <= rr) {
      lazy[x].assign(args...);
      dirty[x] = true;
      push(x, l, r);
      return;
    }
    int m = (l + r) / 2;
    modify(ll, rr, x + x, l, m, args...);
    modify(ll, rr, x + x + 1, m + 1, r, args...);
    tree[x] = n_t(tree[x + x], tree[x + x + 1]);
  }

  n_t get(int ll, int rr, int x, int l, int r) {
    push(x, l, r);
    if (ll > r || l > rr)
      return n_t();
    if (ll <= l && r <= rr)
      return tree[x];
    int m = (l + r) / 2;
    return n_t(get(ll, rr, x + x, l, m), get(ll, rr, x + x + 1, m + 1, r));
  }

public:
  segtree_t(int _n) : n(_n) {
    tree.resize(n << 2);
    lazy.resize(n << 2);
    dirty.resize(n << 2);
    build(1, 0, n - 1);
  }

  template <class T>
  segtree_t(const vector<T> &base) : n(base.size()) {
    tree.resize(n << 2);
    lazy.resize(n << 2);
    dirty.resize(n << 2);
    build(1, 0, n - 1, base);
  }

  template <class... Args>
  void modify(int ll, int rr, const Args&... args) {
    modify(ll, rr, 1, 0, n - 1, args...);
  }

  n_t get(int ll, int rr) {
    return get(ll, rr, 1, 0, n - 1);
  }
  n_t get(int p) {
    return get(p, p, 1, 0, n - 1);
  }
};
