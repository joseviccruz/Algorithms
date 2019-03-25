class binary_search_t {
public:
  // lower_bound (return  < ...)
  // upper_bound (return <= ...)
  template <class Int, class F, class... Args>
  Int operator () (Int l, Int r, const F &f, const Args&... args) {
    assert(l < r);
    while (l < r) {
      Int m = l + ((r - l) >> 1);
      if (f(m, args...))
        l = m + 1;
      else
        r = m;
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
