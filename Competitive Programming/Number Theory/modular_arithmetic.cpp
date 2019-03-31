static constexpr int mod = 1e9 + 7;

template <class T>
inline T add(const T &a, const T &b) {
  return (a + b) < mod ? (a + b) : (a + b - mod);
}

template <class T>
inline T sub(const T &a, const T &b) {
  return (a - b) >= 0 ? (a - b) : (a - b + mod);
}

template <class T>
inline T fmul(T a, T b) {
  T res = 0;
  while (b > 0) {
    if (b & 1)
      res = add(res, a);
    a = add(a, a);
    b >>= 1;
  }
  return res;
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

template <class T>
inline T inv(T a, const T &m = mod) {
  a %= m;
  if (a < 0) a += m;
  T b = m, u = 0, v = 1, t;
  while (a > 0) {
    t = b / a;
    b -= t * a; swap(a, b);
    u -= t * v; swap(u, v);
  }
  assert(b == 1);
  if (u < 0) u += m;
  return u;
}
