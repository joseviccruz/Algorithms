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
