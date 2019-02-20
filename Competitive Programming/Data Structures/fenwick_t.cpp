struct node_t {
  // atributes, don't forget to set default value
  
  node_t(...) {
    ...
  }

  inline void operator += (node_t &other) {
    
  }
};

template <typename T>
class fenwick_t {
  int n;
  vector<T> tree;

public:
  fenwick_t(int _n) : n(_n), tree(_n) {
  }
  
  void modify(int x, T v) {
    assert(x >= 0 && x < n);
    while (x < n) {
      tree[x] += v;
      x |= (x + 1);
    }
  }
  
  T get(int x) {
    assert(x >= 0 && x < n);
    T v{};
    while (x >= 0) {
      v += tree[x];
      x = (x & (x + 1)) - 1;
    }
    return v;
  }
};
