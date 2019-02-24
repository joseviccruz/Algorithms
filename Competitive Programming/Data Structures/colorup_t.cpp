template <class T, class Int = int>
class colorup_t {
public:
  struct range_t {
    Int l, r;
    T v;
    range_t(Int l = 0, Int r = 0, T v = {}) : l(l), r(r), v(v) {
    }
    
    inline bool operator < (const range_t &other) const {
      return l < other.l;
    }
  };
  set<range_t> ranges;

  colorup_t() {
  }

  vector<range_t> modify(Int l, Int r, T v) {
    vector<range_t> ret;
    if (l > r)
      return ret;
    auto it = ranges.lower_bound(l);
    if (it != ranges.begin()) {
      it--;
      if (it->r >= l) {
        auto er = *it;
        ranges.erase(it);
        ranges.emplace(er.l, l - 1, er.v);
        ranges.emplace(l, er.r, er.v);
      }
    }
    it = ranges.upper_bound(r);
    if (it != ranges.begin()) {
      it--;
      if (it->r > r) {
        auto er = *it;
        ranges.erase(it);
        ranges.emplace(er.l, r, er.v);
        ranges.emplace(r + 1, er.r, er.v);
      }
    }
    for (it = ranges.lower_bound(l); it != ranges.end() && it->l <= r; it++)
      ret.push_back(*it);
    ranges.erase(ranges.lower_bound(l), ranges.upper_bound(r));
    ranges.emplace(l, r, v);
    return ret;
  }
};
