/*
  Things to remember:
    - std::bitset<size_t> just have '==' and '!=' defined;
    - ...
*/

template <class T>
inline bool check_bit(const T &n, const int b) { return n & (T(1) << b); }

template <class T>
inline void set_bit(T &n, const int b) { n |= (T(1) << b); }

template <class T>
inline void remove_bit(T &n, const int b) { n &= ~(T(1) << b); }

template <class T>
inline void flip_bit(T &n, const int b) { n ^= (T(1) << b); }

template <class T>
inline int count_bits(const T &n) {
  int ans = 0;
  for (T x = n; x >= 0; x >>= T(1)) {
    ans += (x & T(1));
  }
  return ans;
}
