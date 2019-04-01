// vector<int> small_primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

/*
  - n = 2 ^ t * s + 1;
  - n is prime with >= 75% if:
  a ^ s == 1 mod n
  a ^ (s * 2 ^ i) == (n - 1) mod n to some value in this range [0 <= i < t]
/**/

template <class T>
inline bool miller_rabin(T a, T n) {
  T t = 0, s = n - 1;
  while (!(s & 1)) {
    s >>= 1;
    t++;
  }
  if (!(a %= n))
    return true;
  T f = fexp(a, s, n);
  if (f == 1 || f == n - 1)
    return true;
  for (int i = 1; i < t; i++) {
    if ((f = fmul(f, f, n)) == (n - 1))
      return true;
  }
  return false;
}
