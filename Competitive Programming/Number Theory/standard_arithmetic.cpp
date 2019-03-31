template <class T>
inline T add(const T &a, const T &b) {
  return (a + b);
}

template <class T>
inline T sub(const T &a, const T &b) {
  return (a - b);
}

template <class T>
inline T fmul(T a, T b) {
  return (a * b);
}

template <class T>
inline T fexp(T a, T b) {
  T res = 1;
  while (b > 0) {
    if (b & 1)
      res = fmul(res, a);
    a = fmul(a, a);
    b >>= 1;
  }
  return res;
}
