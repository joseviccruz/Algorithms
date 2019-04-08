template <class T>
T gcd(T a, T b) {
  while (a) {
    b %= a;
    swap(a, b);
  }
  return b;
}

// - Using prime numbers: a ^ (b - 2) * a == 1 mod b
// - a * x + b * y = gcd(a, b), a * x + b * y = 1
template <class T>
T gcd(T a, T b, T &x, T &y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  T p = b / a;
  T g = gcd(b - p * a, a, y, x);
  x -= p * y;
  return g;
}

template <class T>
T lcm(T a, T b) {
  return a / gcd(a, b) * b;
}

// - x = x0 + k * (b / g)
// - y = y0 + k * (a / g)
// - can result in overflow
template <class T>
bool diophantine(T a, T b, T c, T &x, T &y, T &g) {
  if (a == 0 && b == 0) {
    if (c == 0) {
      x = y = g = 0;
      return true;
    }
    return false;
  }
  if (a == 0) {
    if (c % b == 0) {
      x = 0;
      y = c / b;
      g = abs(b);
      return true;
    }
    return false;
  }
  if (b == 0) {
    if (c % a == 0) {
      x = c / a;
      y = 0;
      g = abs(a);
      return true;
    }
    return false;
  }
  g = gcd(abs(a), abs(b), x, y);
  if (c % g != 0)
    return false;
  x *= (c / g);
  y *= (c / g);
  if (a < 0)
    x = -x;
  if (b < 0)
    y = -y;
  return true;
}

template <class T>
bool crt(T k1, T m1, T k2, T m2, T &k, T &m) {
  if ((k1 %= m1) < 0) k1 += m1;
  if ((k2 %= m2) < 0) k2 += m2;
  T x, y, g;
  if (!diophantine(m1, -m2, k2 - k1, x, y, g))
    return false;
  T dx = m2 / g;
  T delta = x / dx - (x % dx < 0);
  k = m1 * (x - dx * delta) + k1;
  m = m1 / g * m2;
  assert(0 <= k && k < m);
  return true;
}

template <class T>
bool crt(const vector<pair<T, T>> &v, T &k, T &m) {
  assert(!v.empty());
  T a, p;
  tie(k, m) = v[0];
  for (int i = 1; i < (int) v.size(); i++) {
    tie(a, p) = v[i];
    if (!crt(k, m, a, p, k, m))
      return false;
  }
  return true;
}
