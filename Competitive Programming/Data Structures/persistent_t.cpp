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

template <class n_t>
class persistent_t {
public:
  struct v_t {
    v_t *l, *r;
    n_t data;

    v_t(n_t node = n_t()) {
      l = nullptr;
      r = nullptr;
      data = node;
    }

    v_t(v_t *lhs, v_t *rhs) {
      l = lhs;
      r = rhs;
      data = n_t(l ? l->data : n_t(), r ? r->data : n_t());
    }
  };

  int n;
  vector<v_t*> ptr;

  void clear(v_t *root) {
    if (root) {
      clear(root->l);
      clear(root->r);
    }
    delete root;
  }

  v_t *build(int l, int r) {
    if (l == r) {
      return new v_t();
    } else {
      int m = (l + r) / 2;
      return new v_t(build(l, m), build(m + 1, r));
    }
  }

  template <class T>
  v_t *build(int l, int r, const vector<T> &base) {
    if (l == r) {
      return new v_t(n_t(base[l]));
    } else {
      int m = (l + r) / 2;
      return new v_t(build(l, m, base), build(m + 1, r, base));
    }
  }

  n_t get(int a, int b, v_t *x, int l, int r) {
    if (a > r || l > b) {
      return n_t();
    }
    if (a <= l && r <= b) {
      return x->data;
    }
    int m = (l + r) / 2;
    return n_t(get(a, b, x->l, l, m), get(a, b, x->r, m + 1, r));
  }

  template <class T>
  v_t *modify(int p, T v, v_t *x, int l, int r) {
    assert(x);
    if (l == r) {
      return new v_t(n_t(v));
    }
    int m = (l + r) / 2;
    if (p <= m) {
      return new v_t(modify(p, v, x->l, l, m), x->r);
    } else {
      return new v_t(x->l, modify(p, v, x->r, m + 1, r));
    }
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
  v_t *modify(int v, int p, T vv) {
    assert(v >= 0 && v < ptr.size());
    ptr.push_back(modify(p, vv, ptr[v], 0, n - 1));
    return ptr.back();
  }
  
  persistent_t(int _n) : n(_n) {
    while (!ptr.empty()) {
      clear(ptr.back());
      ptr.pop_back();
    }
    ptr.push_back(build(0, n - 1));
  }
  
  template <typename T>
  persistent_t(const vector<T> &base) {
    while (!ptr.empty()) {
      clear(ptr.back());
      ptr.pop_back();
    }
    n = base.size();
    ptr.push_back(build(0, n - 1, base));
  }
};
