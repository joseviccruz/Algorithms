struct Point {
  ld x, y;
  
  Point(ld x = 0.0, ld y = 0.0) : x(x), y(y) {
  }
  
  Point operator + (const Point &p) const { return Point(x + p.x, y + p.y); }
  Point operator - (const Point &p) const { return Point(x - p.x, y - p.y); }
  Point operator * (ld t) const { return Point(x * t, y * t); }
  Point operator / (ld t) const { return Point(x / t, y / t); }
};

Point operator * (ld t, const Point &p) { return p * t; }

ld dot(Point p, Point q) { return p.x * q.x + p.y * q.y; }
ld dist_sqr(Point p, Point q) { return dot(p - q, p - q); }
ld cross(Point p, Point q) { return p.x * q.y - p.y * q.x; }

ld dist(Point p, Point q) { return sqrt((ld) dist_sqr(p, q)); }
ld angle(Point p, Point q) { return atan2((ld) cross(p, q), (ld) dot(p, q)); }

Point cw90(Point p) { return Point(p.y, -p.x); }
Point ccw90(Point p) { return Point(-p.y, p.x); }

Point ccw(Point p, ld t) { return Point(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t)); }
Point resize(Point p, ld t) { return p / sqrt((ld) dot(p, p)) * t; }
