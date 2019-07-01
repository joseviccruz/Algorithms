mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct node_t {
  
  node_t() {
  }
    
  node_t(const node_t &lhs, const node_t &rhs) {
  }
};


template <class T, class d_t>
class treap_t {
  struct n_t {
    unsigned p;
    T key;
    int size;
    bool rev;
    d_t data;
    n_t *l, *r;
    template <class... Args>
    n_t(const Args&... args)
    : p(rng()), key(args...), size(1), rev(false),
      data(key), l(nullptr), r(nullptr) {
    }
  };
  using pn_t = n_t*;
  
  pn_t root;
  
  int size(pn_t t) { return t ? t->size : 0; }
  d_t data(pn_t t) { return t ? t->data : d_t(); }
  
  pn_t update(pn_t t) {
    if (t == nullptr) return t;
    t->size = 1 + size(t->l) + size(t->r);
    t->data = d_t(d_t(t->key), d_t(data(t->l), data(t->r)));
    if (t->l != nullptr) t->l->rev ^= t->rev;
    if (t->r != nullptr) t->r->rev ^= t->rev;
    if (t->rev) {
      swap(t->l, t->r);
      t->rev = false;
    }
    return t;
  }
  
  void split(pn_t &t, int k, pn_t &a, pn_t &b) {
    update(t);
    pn_t tmp;
    if (t == nullptr)
      a = b = nullptr;
    else if (size(t->l) < k) {
      split(t->r, k - size(t->l) - 1, tmp, b);
      t->r = tmp;
      a = update(t);
    } else {
      split(t->l, k, a, tmp);
      t->l = tmp;
      b = update(t);
    }
  }
  
  pn_t merge(pn_t a, pn_t b) {
    update(a), update(b);
    pn_t tmp;
    if (a == nullptr || b == nullptr)
      return a ? a : b;
    if (a->p < b->p) {
      a->r = merge(a->r, b);
      return update(a);
    }
    b->l = merge(a, b->l);
    return update(b);
  }
  
  pn_t find_by_order(pn_t t, int n) {
    if (t == nullptr) return t;
    update(t);
    if (n < size(t->l)) return find_by_order(t->l, n);
    else if (n == size(t->l)) return t;
    return find_by_order(t->r, n - size(t->l) - 1);
  }
  
  void clear(pn_t &t) {
    if (t == nullptr) return;
    if (t->l) clear(t->l);
    if (t->r) clear(t->r);
    delete t;
    t = nullptr;
  }

public:
  treap_t() : root(nullptr) {}
  ~treap_t() { clear(); }
  void clear() { clear(root); }
  int size() { return size(root); }
  
  template <class... Args>
  void emplace_at(int n, const Args&... args) {
    pn_t a, b;
    split(root, n, a, b);
    root = merge(merge(a, new n_t(args...)), b);
  }
  
  bool erase(int n) {
    pn_t a, b, c, d;
    split(root, n, a, b);
    split(b, 1, c, d);
    root = merge(a, d);
    if (c == nullptr) return false;
    delete c;
    return true;
  }
  
  pair<T, d_t> find_by_order(int n) {
    assert(0 <= n && n < size());
    pn_t ans(find_by_order(root, n));
    return make_pair(ans->key, ans->data);
  }
  
  d_t get(int l, int r) {
    assert(0 <= l && l <= r && r < size());
    pn_t a, b, c, d;
    split(root, l, a, d);
    split(d, r - l + 1, b, c);
    d_t ans(b->data);
    root = merge(a, merge(b, c));
    return ans;
  }
  
  void reverse(int l, int r) {
    assert(0 <= l && l <= r && r < size());
    pn_t a, b, c, d;
    split(root, l, a, d);
    split(d, r - l + 1, b, c);
    if (b != nullptr) b->rev ^= true;
    root = merge(a, merge(b, c));
  }
};
