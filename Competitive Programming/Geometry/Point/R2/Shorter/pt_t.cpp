using ld = long double;

template <class T>
struct pt_t {
  T x, y;
  
  pt_t(T x = 0.0, T y = 0.0) : x(x), y(y) {
  }
  
  template <class U>
  pt_t(const pt_t<U> &p) : x(p.x), y(p.y) {
  }
  
  pt_t operator + (const pt_t &p) const { return pt_t(x + p.x, y + p.y); }
  pt_t operator - (const pt_t &p) const { return pt_t(x - p.x, y - p.y); }
  pt_t operator * (T t) const { return pt_t(x * t, y * t); }
  pt_t operator / (T t) const { return pt_t(x / t, y / t); }
  
  friend pt_t operator * (T a, const &pt_t b) { return b * a; }
  
  friend T dot(pt_t p, pt_t q) { return p.x * q.x + p.y * q.y; }
  friend T dist2(pt_t p, pt_t q) { return dot(p - q, p - q); }
  friend T norm(pt_t p) { return dot(p, p); }
  friend T cross(pt_t p, pt_t q) { return p.x * q.y - p.y * q.x; }
  
  friend ld dist(pt_t p, pt_t q) { return sqrt((ld) dist2(p, q)); }
  friend ld abs(pt_t p) { return sqrt((ld) norm(p)); }
  friend ld proj(pt_t p, pt_t q) { return dot(p, q) / abs(q); }
  friend ld angle(pt_t p, pt_t q) { return atan2((ld) cross(p, q), (ld) dot(p, q)); }
  
  friend pt_t cw90(pt_t p) { return pt_t(p.y, -p.x); }
  friend pt_t ccw90(pt_t p) { return pt_t(-p.y, p.x); }
  friend pt_t<ld> ccw(pt_t p, ld t) { return pt_t<ld>(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t)); }
};
