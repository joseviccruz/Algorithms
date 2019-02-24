struct node_t {
  int x;
  
  node_t(int x = 0) : x(x) {
  }
  
  node_t operator += (const node_t &o) {
    x += o.x;
  }
  
  node_t operator -= (const node_t &o) {  
    x -= o.x;
  }
};

template <class n_t>
class sqrt_t {
public:
  int n;
  int sqrt_n;
  vector<n_t> values;
  vector<n_t> blocks; 

  sqrt_t(int n) : n(n) {
    sqrt_n = sqrt(n) + 1;
    values.resize(n);
    blocks.resize(sqrt_n);
  }

  template <class T>
  sqrt_t(const vector<T> &base) : n(base.size()) {
    sqrt_n = sqrt(n) + 1;
    copy(base.begin(), base.end(), back_inserter(values));
    blocks.resize(sqrt_n);
    for (int i = 0; i < n; i++)
      blocks[i / sqrt_n] += n_t(base[i]);
  }

  template <class T>
  void modify(int x, T v) {
    blocks[x / sqrt_n] -= values[x];
    values[x] = n_t(v);
    blocks[x / sqrt_n] += values[x];
  }

  n_t get(int l, int r) {
    int ll = l / sqrt_n;
    int rr = r / sqrt_n;
    n_t ret{};
    if (ll == rr) {
      for (int i = l; i <= r; i++)
        ret += n_t(values[i]);
      return ret;
    }
    for (int i = l, end = (ll + 1) * sqrt_n - 1; i <= end; i++)
        ret += n_t(values[i]);
    for (int i = ll + 1; i <= rr - 1; i++)
      ret += blocks[i];
    for (int i = rr * sqrt_n; i <= r; i++)
        ret += n_t(values[i]);
    return ret;
  }
};
