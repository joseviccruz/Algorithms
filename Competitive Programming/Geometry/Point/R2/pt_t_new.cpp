using Tp = int;

struct pt_t {
  Tp x, y;
  
  pt_t(Tp x = 0, Tp y = 0) : x(x), y(y) {
  }
  
  pt_t operator + (const pt_t &p) const { return pt_t(x + p.x, y + p.y); }
  pt_t operator - (const pt_t &p) const { return pt_t(x - p.x, y - p.y); }
  pt_t operator * (Tp t) const { return pt_t(x * t, y * t); }
  pt_t operator / (Tp t) const { return pt_t(x / t, y / t); }
  
  friend pt_t operator * (Tp t, const pt_t &p) { return p * t; }
};

Tp dot(pt_t p, pt_t q) { return p.x * q.x + p.y * q.y; }
Tp dist_sqr(pt_t p, pt_t q) { return dot(p - q, p - q); }
Tp cross(pt_t p, pt_t q) { return p.x * q.y - p.y * q.x; }

ld dist(pt_t p, pt_t q) { return sqrt((ld) dist_sqr(p, q)); }
ld angle(pt_t p, pt_t q) { return atan2((ld) cross(p, q), (ld) dot(p, q)); }

pt_t cw90(pt_t p) { return pt_t(p.y, -p.x); }
pt_t ccw90(pt_t p) { return pt_t(-p.y, p.x); }

// float point points
pt_t ccw(pt_t p, ld t) { return pt_t(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t)); }
pt_t resize(pt_t p, ld t) { return p / sqrt((ld) dot(p, p)) * t; }
