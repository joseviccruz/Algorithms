class ternary_search_t {
public:
  int eps;
  int ll;
  int rr;
  
  ternary_search_t(int eps = 1, int ll = 0, int rr = 0) : eps(eps), ll(ll), rr(rr) {
  }

  template <class Int, class C, class F, class... Args>
  Int operator () (Int l, Int r, const C &cmp, const F &f, const Args&... args) {
    assert(l < r);
    while (r - l > eps) {
      Int m = l + ((r - l) >> 1);
      if (cmp(f(m, args...), f(m + 1, args...)))
        l = m + ll;
      else
        r = m - rr;
    }
    return l;
  }

  template <class Float, class C, class F, class... Args>
  Float operator () (Float l, Float r, int t, const C &cmp, const F &f, const Args&... args) {
    assert(l < r);
    while (t--) {
      Float m = (l * 2.0 + r) / 3.0;
      Float n = (l + 2.0 * r) / 3.0;
      if (cmp(f(m, args...), f(n, args...)))
        l = m;
      else
        r = n;
    }
    return l;
  }
};
