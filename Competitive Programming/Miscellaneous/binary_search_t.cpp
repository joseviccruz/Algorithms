class binary_search_t {
public:
  int eps;
  int ll;
  int rr;

  binary_search_t(int eps = 1, int ll = 1, int rr = 0) : eps(1), ll(1), rr(0) {
  }

  template <class Int, class F, class... Args>
  Int operator () (Int l, Int r, const F &f, const Args&... args) {
    assert(l < r);
    while (r - l > eps) {
      Int m = l + ((r - l) >> 1);
      if (f(m, args...))
        l = m + ll;
      else
        r = m - rr;
    }
    return l;
  }

  template <class Float, class F, class... Args>
  Float operator () (Float l, Float r, int t, const F &f, const Args&... args) {
    assert(l < r);
    while (t--) {
      Float m = (l + r) / 2.0;
      if (f(m, args...))
        l = m;
      else
        r = m;
    }
    return l;
  }
};
