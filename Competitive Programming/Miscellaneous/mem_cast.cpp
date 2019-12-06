template <class T, class U>
inline T mem_cast(const U &y) {
  static T x;
  static_assert(sizeof x == sizeof y);
  memcpy(&x, &y, sizeof y);
  return x;
}
