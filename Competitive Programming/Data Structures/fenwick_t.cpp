struct node_t {
  
  node_t() {
  }

  inline void operator += (node_t &other) {
  }
};

template <class T>
class fenwick_t {
  int n;
  vector<T> tree;

public:
  fenwick_t(int n) : n(n) {
    assert(n > 0);
    tree.resize(n);
  }
  
  void modify(int x, T v) {
    assert(x >= 0 && x <= n - 1);
    while (x < n) {
      tree[x] += v;
      x |= (x + 1);
    }
  }
  
  T get(int x) {
    assert(x >= 0 && x <= n - 1);
    T v{};
    while (x >= 0) {
      v += tree[x];
      x = (x & (x + 1)) - 1;
    }
    return v;
  }
};
