struct polar_cmp {
  const pt_t pivot;
  template <class... Args>
  polar_cmp(const Args&... args) : pivot(args...) {
  }
  inline bool operator () (const pt_t &p, const pt_t &q) {
    return cross(p - pivot, q - pivot) > 0.0;
  }
};
