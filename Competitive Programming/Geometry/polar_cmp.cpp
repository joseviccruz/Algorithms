using namespace rel_ops;

struct polar_cmp {
  const pt_t center;
  template <class... Args>
  polar_cmp(const Args&... args) : center(args...) {
  }
  inline bool operator () (const pt_t &p, const pt_t &q) {
    return cross(p - center, q - center) < 0;
  }
};

template <class RandomIt, class... Args>
typename enable_if<is_same<typename iterator_traits<RandomIt>::value_type, pt_t>::value>::type
sort_polar(RandomIt first, RandomIt last, const pt_t& center) {
  first = partition(first, last, [&center](const pt_t& point) {
    return point == center;
  });
  auto pivot = partition(first, last, [&center](const pt_t& point) {
    return point > center;
  });
  sort(first, pivot, polar_cmp(center));
  sort(pivot, last, polar_cmp(center));
}
