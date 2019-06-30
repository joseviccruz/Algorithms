using namespace rel_ops;
using ld = long double;
using F = ...;

const ld eps = 1e-6;

enum float_ops { lt = -1, eq, gt };
inline int sign(const ld &x) { return (abs(x) < eps) ? eq : (x > 0) ? gt : lt; }
inline bool cmp(ld lhs, int op, ld rhs) { return sign(lhs - rhs) == op; }

struct pt_t {
  F x, y;
  
  pt_t(F x = 0, F y = 0) : x(x), y(y) {
  }
  
  pt_t operator + (const pt_t &p) const { return pt_t(x + p.x, y + p.y); }
  pt_t operator - (const pt_t &p) const { return pt_t(x - p.x, y - p.y); }
  pt_t operator * (F t) const { return pt_t(x * t, y * t); }
  pt_t operator / (F t) const { return pt_t(x / t, y / t); }
  
  friend pt_t operator * (F t, const pt_t &p) { return p * t; }

  bool operator < (const pt_t &o) const {
    if (cmp(x, eq, o.x))
      return cmp(y, lt, o.y);
    return cmp(x, lt, o.x);
  }
  
  bool operator == (const pt_t &o) const {
    return cmp(x, eq, o.x) and cmp(y, eq, o.y);
  }
};

F dot(pt_t p, pt_t q) { return p.x * q.x + p.y * q.y; }
F dist_sqr(pt_t p, pt_t q) { return dot(p - q, p - q); }
F cross(pt_t p, pt_t q) { return p.x * q.y - p.y * q.x; }

ld dist(pt_t p, pt_t q) { return sqrt((ld) dist_sqr(p, q)); }
ld angle(pt_t p, pt_t q) { return atan2((ld) cross(p, q), (ld) dot(p, q)); }

pt_t cw90(pt_t p) { return pt_t(p.y, -p.x); }
pt_t ccw90(pt_t p) { return pt_t(-p.y, p.x); }

// float point points
pt_t ccw(pt_t p, ld t) { return pt_t(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t)); }
pt_t resize(pt_t p, ld t) { return p / sqrt((ld) dot(p, p)) * t; }
