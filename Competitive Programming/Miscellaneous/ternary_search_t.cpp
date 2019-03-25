class ternary_search_t {
public:
  template <class Int, class C, class F, class... Args>
  pair<Int, Int> operator () (Int l, Int r, const C &cmp, const F &f, const Args&... args) {
    assert(l < r);
    while (l + 1 < r) {
      Int m = l + ((r - l) >> 1);
      if (cmp(f(m, args...), f(m + 1, args...)))
        l = m;
      else
        r = m;
    }
    return make_pair(l, r);
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
