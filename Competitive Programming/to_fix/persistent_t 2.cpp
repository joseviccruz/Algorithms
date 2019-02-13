struct node_t {
  //*/
  int x;
  //*/
  
  // node = value 
  node_t(int v = 0) {
    //*/
    x = v;
    //*/
  }
  
  // merge
  node_t(const node_t &lhs, const node_t &rhs) {
    //*/
    x = lhs.x + rhs.x;
    //*/
  }
  
  // node += node
  node_t operator += (const node_t &other) {
    x += other.x;
  }
};

template <class n_t, size_t sz = 1 << 22>
class persistent_t {
public:
  int n;
  int z;
  vector<n_t> st;
  vector<int> ptr, vl, vr;
  
  void build(int x, int l, int r) {
    if (l == r) {
      st[x] = n_t();
    } else {
      int m = (l + r) / 2;
      vl[x] = z++;
      build(vl[x], l, m);
      vr[x] = z++;
      build(vr[x], m + 1, r);
      st[x] = n_t(st[vl[x]], st[vr[x]]);
    }
  }
  
  template <class T>
  void build(int x, int l, int r, const vector<T> &base) {
    if (l == r) {
      st[x] = n_t(base[l]);
    } else {
      int m = (l + r) / 2;
      vl[x] = z++;
      build(vl[x], l, m, base);
      vr[x] = z++;
      build(vr[x], m + 1, r, base);
      st[x] = n_t(st[vl[x]], st[vr[x]]);
    }
  }

  // range [a, b]
  n_t get(int a, int b, int x, int l, int r) {
    if (l > b || a > r) {
      return n_t();
    }
    if (a <= l && r <= b) {
      return st[x];
    }
    int m = (l + r) / 2;
    return n_t(get(a, b, vl[x], l, m), get(a, b, vr[x], m + 1, r));
  }
  
  // pos, value
  template <class T>
  int modify(int p, T v, int x, int l, int r) {
    if (l > p || p > r) {
      return x;
    }
    if (l == r) {
      st[z] = st[x];
      st[z] += n_t(v);
      return z++;
    }
    int m = (l + r) / 2;
    int nl = modify(p, v, vl[x], l, m);
    int nr = modify(p, v, vr[x], m + 1, r);
    vl[z] = nl;
    vr[z] = nr;
    st[z] = n_t(st[vl[z]], st[vr[z]]);
    return z++;
  }
  
  // version v, range[a, b]
  n_t get(int v, int a, int b) {
    assert(v >= 0 && v < ptr.size());
    return get(a, b, ptr[v], 0, n - 1);
  }
  
  // version v, pos p
  n_t get(int v, int p) {
    assert(v >= 0 && v < ptr.size());
    return get(p, p, ptr[v], 0, n - 1);
  }
  
  // version v, pos p, value vv
  template <class T>
  int modify(int v, int p, T vv) {
    assert(v >= 0 && v < ptr.size());
    ptr.push_back(modify(p, vv, ptr[v], 0, n - 1));
    return ptr.back();
  }
  
  persistent_t(int _n) : n(_n) {
    z = 1;
    st.assign(sz, n_t()); // [!!!]
    vl.resize(sz);
    vr.resize(sz);
    build(0, 0, n - 1);
    ptr.assign(1, 0);
  }
  
  template <class T>
  persistent_t(const vector<T> &base) {
    n = base.size();
    z = 1;
    st.assign(sz, n_t()); // [!!!]
    vl.resize(sz);
    vr.resize(sz);
    build(0, 0, n - 1, base);
    ptr.assign(1, 0);
  }
};
