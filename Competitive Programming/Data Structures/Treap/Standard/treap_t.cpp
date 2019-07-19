mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct value_t {

  value_t() {
  }

  bool operator < (const key_t &other) {
  }
};

struct node_t {
  long long sum;
  
  node_t(int sum = 0) : sum(sum) {
  }
    
  node_t(const node_t &lhs, const node_t &rhs) {
    sum = lhs.sum + rhs.sum;
  }
};

template <class T, class d_t>
class treap_t {
  struct n_t {
    unsigned p;
    T key;
    int size;
    d_t data;
    n_t *l, *r;
    template <class... Args>
    n_t(const T &key, const Args&... args)
    : p(rng()), key(key), size(1),
      data(args...), l(nullptr), r(nullptr) {
    }
  };
  using pn_t = n_t*;
  
  pn_t root;
  
  int size(pn_t t) { return t ? t->size : 0; }
  d_t data(pn_t t) { return t ? t->data : d_t(); }
  
  pn_t push(pn_t t) {
    if (t == nullptr) return t;
    t->size = 1 + size(t->l) + size(t->r);
    t->data = d_t(data(t->l), d_t(d_t(t->key), data(t->r)));
    return t;
  }
  
  void split(pn_t &t, T k, pn_t &a, pn_t &b) {
    push(t);
    pn_t tmp;
    if (t == nullptr) a = b = nullptr;
    else if (t->key < k) {
      split(t->r, k, tmp, b);
      t->r = tmp, a = push(t);
    } else {
      split(t->l, k, a, tmp);
      t->l = tmp, b = push(t);
    }
  }
  
  pn_t merge(pn_t a, pn_t b) {
    push(a), push(b);
    pn_t tmp;
    if (a == nullptr || b == nullptr) return a ? a : b;
    if (a->p < b->p) {
      a->r = merge(a->r, b);
      return push(a);
    }
    b->l = merge(a, b->l);
    return push(b);
  }
  
  pn_t find_by_order(pn_t t, int n) {
    if (t == nullptr) return t;
    push(t);
    if (n < size(t->l)) return find_by_order(t->l, n);
    else if (n == size(t->l)) return t;
    return find_by_order(t->r, n - size(t->l) - 1);
  }
  
  pn_t find(pn_t t, T k) {
    if (t == nullptr) return t;
    push(t);
    if (k < t->key) return find(t->l, k);
    else if (k == t->key) return t;
    return find(t->r, k);
  }
  
  int order_of_key(pn_t t, T k) {
    if (t == nullptr) return 0;
    push(t);
    if (k < t->key || k == t->key) return order_of_key(t->l, k);
    return 1 + size(t->l) + order_of_key(t->r, k);
  }
  
  pn_t erase(pn_t &t, T k) {
    if (t == nullptr) return t;
    push(t);
    pn_t to_erase;
    if (k < t->key) to_erase = erase(t->l, k);
    else if (k == t->key) {
      to_erase = t;
      t = merge(t->l, t->r);
    } else to_erase = erase(t->r, k);
    push(t);
    return to_erase;
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
  void emplace(const T &key, const Args&... args) {
    pn_t a, b;
    split(root, key, a, b);
    root = merge(merge(a, new n_t(key, args...)), b);
  }
  
  bool erase(T k) {
    pn_t to_erase(erase(root, k));
    if (to_erase == nullptr) return false;
    delete to_erase;
    return true;
  }

  bool erase_at(int n) { return erase(find_by_order(n).first); }
  bool count(T k) { pn_t ans(find(root, k)); return ans != nullptr; }
  
  pair<T, d_t> find(T k) {
    pn_t ans(find(root, k));
    assert(ans != nullptr);
    return make_pair(ans->key, ans->data);
  }
  
  pair<T, d_t> find_by_order(int n) {
    assert(0 <= n && n < size());
    pn_t ans(find_by_order(root, n));
    return make_pair(ans->key, ans->data);
  }
  
  int order_of_key(T k) { return order_of_key(root, k); }
  
  // [kl, kr)
  d_t get_between_keys(T kl, T kr) {
    assert(kl < kr);
    pn_t a, b, c, d;
    split(root, kl, a, d);
    split(d, kr, b, c);
    d_t ans(b->data);
    root = merge(a, merge(b, c));
    return ans;
  }
};
