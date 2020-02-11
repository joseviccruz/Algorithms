template <class T>
class wrapper {
  T value;

 public:
  static constexpr T eps = 1e-6;
 
  constexpr wrapper() : value() { }
  template <class U> constexpr wrapper(const U &_value) : value(_value) { }
  
  template <class U> bool operator ==(const U &other) const { return abs(value - wrapper(other).value) <= eps; }
  template <class U> bool operator !=(const U &other) const { return !(*this == other); }

  template <class U> bool operator  <(const U &other) const { return !(*this == other) && (value < wrapper(other).value); }
  template <class U> bool operator  >(const U &other) const { return wrapper(other) < *this; }
  template <class U> bool operator <=(const U &other) const { return !(*this > other) || (*this == other); }
  template <class U> bool operator >=(const U &other) const { return !(*this < other) || (*this == other); }

  template <class U> friend bool operator ==(const U &lhs, const wrapper &rhs) { return wrapper(lhs).operator ==(rhs); }
  template <class U> friend bool operator !=(const U &lhs, const wrapper &rhs) { return wrapper(lhs).operator !=(rhs); }

  template <class U> friend bool operator  <(const U &lhs, const wrapper &rhs) { return wrapper(lhs).operator  <(rhs); }
  template <class U> friend bool operator  >(const U &lhs, const wrapper &rhs) { return wrapper(lhs).operator  >(rhs); }
  template <class U> friend bool operator <=(const U &lhs, const wrapper &rhs) { return wrapper(lhs).operator <=(rhs); }
  template <class U> friend bool operator >=(const U &lhs, const wrapper &rhs) { return wrapper(lhs).operator >=(rhs); }

  constexpr operator const T &() const noexcept { return value; }
  constexpr operator T &() { return value; }
};
