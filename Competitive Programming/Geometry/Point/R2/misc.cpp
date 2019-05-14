// Warning: Take care with integer overflow

// Some functions requires floating point
using PT = pt_t<ld>;

// Check if Δ ABC is valid
template <class T>
bool triangle(T a, T b, T c) {
  return cmp(a + b, gt, c) and cmp(a + c, gt, b) and cmp(b + c, gt, a);
}

// 2 * (Signed) Area Δ ABC
template <class T>
T area2(pt_t<T> a, pt_t<T> b, pt_t<T> c) {
  return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

// (Signed) Area Δ ABC
ld area(PT a, PT b, PT c) {
  return area2(a, b, c) / 2;
}

// 2 * (Signed) Area of a polygon
template <class T>
T area2(const vector<pt_t<T>> &polygon) {
  assert(polygon.size() >= 3);
  T ret = 0;
  int n = polygon.size();
  for (int i = 1; i + 1 < n; i++) {
    ret += area2(polygon[0], polygon[i], polygon[i + 1]);
  }
  return ret;
}

// (Signed) Area of a polygon
ld area(const vector<PT> &polygon) {
  return area2(polygon) / 2;
}

// Project point C onto line through A and B, assuming A != B
PT projectPointLine(PT a, PT b, PT c) {
  assert(not (a == b));
  return a + (b - a) * dot(b - a, c - a) / dot(b - a, b - a);
}

// Reflect point C onto line through A and B, assuming A != B
PT reflectPointLine(PT a, PT b, PT c) {
  return 2 * projectPointLine(a, b, c) - c;
}

// Project point C onto line segment through A and B
PT projectPointSegment(PT a, PT b, PT c) {
  ld r = dot(b - a, b - a);
  if (cmp(r, eq, 0))
    return a;
  r = dot(c - a, b - a) / r;
  if (cmp(r, lt, 0))
    return a;
  if (cmp(r, gt, 1))
    return b;
  return a + (b - a) * r;
}

// Compute distance from C to segment between A and B
ld distancePointSegment(PT a, PT b, PT c) {
  return dist(c, projectPointSegment(a, b, c));
}

// Determines if C is between A and B
template <class T>
bool between(pt_t<T> a, pt_t<T> b, pt_t<T> c) {
  if (a == b)
    return a == c;
  return cmp(cross(a - c, b - c), eq, 0) and not cmp(dot(a - c, b - c), gt, 0);
}

// Determines if A, B and C are collinear
template <class T>
bool collinear(pt_t<T> a, pt_t<T> b, pt_t<T> c) {
  return cmp(area2(a, b, c), eq, 0);
}

// Determine if lines from A to B and C to D are parallel
template <class T>
bool linesParallel(pt_t<T> a, pt_t<T> b, pt_t<T> c, pt_t<T> d) {
  return cmp(cross(b - a, c - d), eq, 0);
}

// Determine if lines from a to b and c to d are collinear;
template <class T>
bool linesCollinear(pt_t<T> a, pt_t<T> b, pt_t<T> c, pt_t<T> d) {
  if (not linesParallel(a, b, c, d))
    return false;
  if (not cmp(abs(cross(a - b, a - c)), eq, 0) or not cmp(abs(cross(c - d, c - a)), eq, 0))
    return false;
  return true;
}

// Determine if line segment from A to B intersects with line segment from C to D
template <class T>
bool segmentsIntersect(pt_t<T> a, pt_t<T> b, pt_t<T> c, pt_t<T> d) {
  if (between(a, b, c) or between(a, b, d) or between(c, d, a) or between(c, d, b))
    return true;
  if (collinear(a, b, c) or collinear(a, b, d) or collinear(c, d, a) or collinear(c, d, b))
    return false;
  if (cmp(cross(d - a, b - a) * cross(c - a, b - a), gt, 0))
    return false;
  if (cmp(cross(a - c, d - c) * cross(b - c, d - c), gt, 0))
    return false;
  return true;
}

/*
 * Compute intersection of line passing through A and B
 * with line passing through C and D, assuming that unique
 * intersection exists
 */
PT computeLineIntersection(PT a, PT b, PT c, PT d) {
  assert(not linesParallel(a, b, c, d));
  b = b - a, d = c - d, c = c - a;
  assert(cmp(dot(b, b), gt, 0) and cmp(dot(d, d), gt, 0));
  return a + b * cross(c, d) / cross(b, d);
}

/*
 * Compute intersection of segment passing through A and B
 * with segment passing through C and D, assuming that unique
 * intersection exists
 */
PT computeSegmentIntersection(PT a, PT b, PT c, PT d) {
  assert(segmentsIntersect(a, b, c, d));
  return computeLineIntersection(a, b, c, d);
}

// Compute circle passing through 3 given points
PT computeCircleCenter(PT a, PT b, PT c) {
  b = (a + b) / 2, c = (a + c) / 2;
  return computeLineIntersection(b, b + cw90(a - b), c, c + cw90(a - c));
}

/* 
 * Compute the arc degree of circle with radius r1
 * intersected with circle with radius r2 and with
 * distance between them equals to d
 */
ld circleCircleIntersectionAngle(ld r1, ld r2, ld d) {
  assert(triangle(r1, r2, d));
  return 2 * acos(((d * d + r2 * r2) - r1 * r1) / (2 * r2 * d));
}

// Compute intersection of circle centered at a with radius r with circle centered at b with radius R
vector<PT> circleCircleIntersection(PT p, ld r1, PT q, ld r2) {
  ld d = dist(p, q);
  if (cmp(d, gt, r1 + r2) or cmp(d + min(r1, r2), lt, max(r1, r2)))
    return vector<PT>();
  ld x = (d * d - r2 * r2 + r1 * r1) / (2 * d);
  ld y = sqrt(r1 * r1 - x * x);
  PT v = (q - p) / d;
  vector<PT> ret;
  ret.push_back(p + v * x + ccw90(v) * y);
  if (cmp(y, gt, 0))
    ret.push_back(p + v * x - ccw90(v) * y);
  return ret;
}
