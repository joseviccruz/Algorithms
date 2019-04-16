using ld = long double;

template <class T>
struct pt_t {
  T x, y, z;
  
  pt_t(T x = 0.0, T y = 0.0, T z = 0.0) : x(x), y(y), z(z) {
  }
  
  template <class U>
  pt_t(const pt_t<U> &p) : x(p.x), y(p.y), z(p.z) {
  }
  
  pt_t &operator += (const pt_t &p) { x += p.x, y += p.y, z += p.z; return *this; }
  pt_t &operator -= (const pt_t &p) { x -= p.x, y -= p.y, z -= p.z; return *this; }
  pt_t &operator *= (T t) { x *= t, y *= t, z *= t; return *this; }
  pt_t &operator /= (T t) { x /= t, y /= t, z /= t; return *this; }
  
  pt_t operator + (const pt_t &t) const { return pt_t(*this) += t; }
  pt_t operator - (const pt_t &t) const { return pt_t(*this) -= t; }
  pt_t operator * (T t) const { return pt_t(*this) *= t; }
  pt_t operator / (T t) const { return pt_t(*this) /= t; }
  
  friend pt_t operator * (T a, pt_t b) { return b * a; }
  friend pt_t operator / (T a, pt_t b) { return b / a; }
  friend pt_t crossR3(pt_t p, pt_t q) { return pt_t(p.y * q.z - p.z * q.y,
                                                    p.z * q.x - p.x * q.z,
                                                    p.x * q.y - p.y * q.x); }
  
  friend T dot(pt_t p, pt_t q) { return p.x * q.x + p.y * q.y + p.z * q.z; }
  friend T dist2(pt_t p, pt_t q) { return dot(p - q, p - q); }
  friend T norm(pt_t p) { return dot(p, p); }
  friend T cross(pt_t p, pt_t q) { return p.x * q.y - p.y * q.x; }
  friend T triple(pt_t p, pt_t q, pt_t r) { return dot(p, cross(q, r)); }
  
  friend ld abs(pt_t p) { return sqrt((ld) norm(p)); }
  friend ld proj(pt_t p, pt_t q) { return dot(p, q) / abs(q); }
  friend ld angle(pt_t p, pt_t q) { return acos((ld) dot(p, q) / abs(p) / abs(q)); }
  
  friend pt_t cw90(pt_t p) { return (p.y, -p.x); }
  friend pt_t ccw90(pt_t p) { return (-p.y, p.x); }
  friend pt_t<ld> ccw(pt_t p, ld t) { return pt_t<ld>(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t)); }
};
