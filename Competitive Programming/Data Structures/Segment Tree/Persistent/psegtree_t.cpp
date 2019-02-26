struct node_t {
  
  node_t() {
  }
  
  node_t(const node_t &lhs, const node_t &rhs) {
  }
};
 
template <typename n_t, size_t sz = -1>
class psegtree_t {
  struct range_t { int l, r; };
  int n;
  int z;
  vector<n_t> st;
  vector<int> ptr;
  vector<range_t> v;

  void new_() {
    st.emplace_back();
    v.emplace_back();
  }

  void build(int x, int l, int r) {
    new_();
    if (l == r)
      st[x] = n_t();
    else {
      int m = (l + r) / 2;
      v[x].l = z++;
      build(v[x].l, l, m);
      v[x].r = z++;
      build(v[x].r, m + 1, r);
      st[x] = n_t(st[v[x].l], st[v[x].r]);
    }
  }

  template <class T>
  void build(int x, int l, int r, const vector<T> &base) {
    new_();
    if (l == r)
      st[x] = n_t(base[l]);
    else {
      int m = (l + r) / 2;
      v[x].l = z++;
      build(v[x].l, l, m, base);
      v[x].r = z++;
      build(v[x].r, m + 1, r, base);
      st[x] = n_t(st[v[x].l], st[v[x].r]);
    }
  }

  n_t get(int a, int b, int x, int l, int r) {
    if (l > b || a > r)
      return n_t();
    if (a <= l && r <= b)
      return st[x];
    int m = (l + r) / 2;
    return n_t(get(a, b, v[x].l, l, m), get(a, b, v[x].r, m + 1, r));
  }
  
  template <class... Args>
  int modify(int p, int x, int l, int r, Args&&... args) {
    if (l > p || p > r)
      return x;
    new_();
    if (l == r) {
      st[z] = n_t(args...);
      return z++;
    }
    int m = (l + r) / 2;
    int nl = modify(p, v[x].l, l, m, args...);
    int nr = modify(p, v[x].r, m + 1, r, args...);
    v[z].l = nl;
    v[z].r = nr;
    st[z] = n_t(st[v[z].l], st[v[z].r]);
    return z++;
  }

public:
  n_t get(int v, int a, int b) {
    return get(a, b, ptr[v], 0, n - 1);
  }
  
  n_t get(int v, int p) {
    return get(p, p, ptr[v], 0, n - 1);
  }

  template <class... Args>
  int modify(int v, int p, Args&&... args) {
    ptr.push_back(modify(p, ptr[v], 0, n - 1, args...));
    return ptr.back();
  }

  psegtree_t(int _n) : n(_n) {
    z = 1;
    if (sz != -1) {
      st.reserve(sz);
      v.reserve(sz);
    }
    build(0, 0, n - 1);
    ptr.assign(1, 0);
  }

  template <class T>
  psegtree_t(const vector<T> &base) : n(base.size()) {
    z = 1;
    if (sz != -1) {
      st.reserve(sz);
      v.reserve(sz);
    }
    build(0, 0, n - 1, base);
    ptr.assign(1, 0);
  }
};
