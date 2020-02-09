template <class T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T t = m / a;
    m -= t * a; std::swap(a, m);
    u -= t * v; std::swap(u, v);
  }
  assert(m == 1);
  return u;
}

template <class IntegralConstant>
class modular_t {
  using T = typename std::decay<decltype(IntegralConstant::value)>::type;
  
  T value;
  
 public:
  using value_type = T;

  constexpr static T mod() { return IntegralConstant::value; }

  constexpr modular_t() : value() {}
  template <class Integer> modular_t(const Integer &x) { value = modularize(x); }
  
  template <class Integer>
  static T modularize(const Integer &v) {
    T ret;
    if (-mod() <= v && v < mod())
      ret = static_cast<T>(v);
    else
      ret = static_cast<T>(v % mod());
    if (ret < 0)
      ret += mod();
    return ret;
  }
  
  operator const T&() const noexcept { return value; }
  const T& get() const noexcept { return value; }
  
  modular_t &operator +=(const modular_t &other) { if ((value += other.value) >= mod()) value -= mod(); return *this; }
  modular_t &operator -=(const modular_t &other) { if ((value -= other.value) <      0) value += mod(); return *this; }
  
  template <class U = IntegralConstant>
  typename std::enable_if<std::is_same<typename modular_t<U>::value_type, int>::value, modular_t>::type
  &operator *=(const modular_t &other) { value = modularize(static_cast<long long>(value) * other.value); return *this; }

  template <class U = IntegralConstant>
  typename std::enable_if<std::is_same<typename modular_t<U>::value_type, long long>::value, modular_t>::type
  &operator *=(const modular_t &other) {
    auto quotient = static_cast<long double>(value) * other.value / mod();
    value = modularize(value * other.value - static_cast<long long>(quotient) * mod());
    return *this;
  }
  
  template <class U = IntegralConstant>
  typename std::enable_if<!std::is_integral<typename modular_t<U>::value_type>::value, modular_t>::type
  &operator *=(const modular_t &other) { value = modularize(value * other.value); return *this; }
  
  modular_t &operator /=(const modular_t &other) { return *this *= modular_t(inverse(other.value, mod())); }
  
  template <class Integer> modular_t &operator +=(const Integer &other) { return *this += modular_t(other); }
  template <class Integer> modular_t &operator -=(const Integer &other) { return *this -= modular_t(other); }
  template <class Integer> modular_t &operator *=(const Integer &other) { return *this *= modular_t(other); }
  template <class Integer> modular_t &operator /=(const Integer &other) { return *this /= modular_t(other); }

  modular_t &operator ++()    { return *this += 1; }
  modular_t &operator --()    { return *this -= 1; }
  modular_t  operator ++(int) { modular_t result(*this); *this += 1; return result; }
  modular_t  operator --(int) { modular_t result(*this); *this -= 1; return result; }
  
  modular_t  operator  +() const { return modular_t(+value); }
  modular_t  operator  -() const { return modular_t(-value); }
  
  modular_t  operator  +(const modular_t &other) const { return modular_t(*this) += other; }
  modular_t  operator  -(const modular_t &other) const { return modular_t(*this) -= other; }
  modular_t  operator  *(const modular_t &other) const { return modular_t(*this) *= other; }
  modular_t  operator  /(const modular_t &other) const { return modular_t(*this) /= other; }
  
  template <class Integer> modular_t operator  +(const Integer &other) const { return modular_t(*this) += other; }
  template <class Integer> modular_t operator  -(const Integer &other) const { return modular_t(*this) -= other; }
  template <class Integer> modular_t operator  *(const Integer &other) const { return modular_t(*this) *= other; }
  template <class Integer> modular_t operator  /(const Integer &other) const { return modular_t(*this) /= other; }
  
  template <class Integer> friend modular_t operator  +(const Integer &lhs, const modular_t &rhs) { return modular_t(lhs) += rhs; }
  template <class Integer> friend modular_t operator  -(const Integer &lhs, const modular_t &rhs) { return modular_t(lhs) -= rhs; }
  template <class Integer> friend modular_t operator  *(const Integer &lhs, const modular_t &rhs) { return modular_t(lhs) *= rhs; }
  template <class Integer> friend modular_t operator  /(const Integer &lhs, const modular_t &rhs) { return modular_t(lhs) /= rhs; }
  
  bool operator  <(const modular_t &other) const { return value  < other.value; }
  bool operator ==(const modular_t &other) const { return value == other.value; }
  
  template <class Integer> bool operator  <(const Integer &other) const { return value  < modular_t(other); }
  template <class Integer> bool operator ==(const Integer &other) const { return value == modular_t(other); }
  
  template <class Integer> friend bool operator  <(const Integer &lhs, const modular_t &rhs) { return modular_t(lhs)  < rhs; }
  template <class Integer> friend bool operator ==(const Integer &lhs, const modular_t &rhs) { return modular_t(lhs) == rhs; }
  
  friend std::string to_string(const modular_t &v) { return std::to_string(v.value); }
  
  friend std::ostream &operator <<(std::ostream &stream, const modular_t &v) { return stream << v.value; }
  
  friend std::istream &operator >>(std::istream &stream, modular_t &v) {
    stream >> v.value;
    v.value = modularize(v.value);
    return stream;
  }
};

template <class IntegralConstant>
struct std::hash<modular_t<IntegralConstant>> : public std::hash<typename modular_t<IntegralConstant>::value_type> {};

using mod_t = modular_t<std::integral_constant<int, 1000000007>>;

/*
using mod_type = int;
struct integral_nonconstant { static mod_type value; };
mod_type integral_nonconstant::value = 1000000007;
//using mod_t = modular_t<integral_nonconstant>;
*/
