template <class T>
struct polar_cmp {
  const pt_t<T> pivot;
  template <class... Args>
  polar_cmp(const Args&... args) : pivot(args...) {
  }
  inline bool operator () (const pt_t<T> &p, const pt_t<T> &q) {
    return cross(p - pivot, q - pivot) > 0.0;
  }
};
