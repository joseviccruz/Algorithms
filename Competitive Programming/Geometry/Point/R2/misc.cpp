// Warning: Take care with integer overflow
// Some functions requires floating point

F polar_angle(const pt_t &p, const pt_t &center = pt_t(0, 0)) {
  F angle = atan2(p.y - center.y, p.x - center.x);
  return angle;// + ((angle < 0) ? 2 * PI : 0);
}

// Check if Δ ABC is valid
bool triangle(F a, F b, F c) {
  return cmp(a + b, gt, c) and cmp(a + c, gt, b) and cmp(b + c, gt, a);
}

// 2 * (Signed) Area Δ ABC
F area2(pt_t a, pt_t b, pt_t c) {
  return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

// (Signed) Area Δ ABC
ld area(pt_t a, pt_t b, pt_t c) {
  return area2(a, b, c) / 2;
}

// 2 * (Signed) Area of a polygon
F area2(const vector<pt_t> &polygon) {
  assert(polygon.size() >= 3);
  F ret = 0;
  int n = polygon.size();
  for (int i = 1; i + 1 < n; i++) {
    ret += area2(polygon[0], polygon[i], polygon[i + 1]);
  }
  return ret;
}

// (Signed) Area of a polygon
ld area(const vector<pt_t> &polygon) {
  return area2(polygon) / 2;
}

// Project point C onto line through A and B, assuming A != B
pt_t projectPointLine(pt_t a, pt_t b, pt_t c) {
  assert(not (a == b));
  return a + (b - a) * dot(b - a, c - a) / dot(b - a, b - a);
}

// Reflect point C onto line through A and B, assuming A != B
pt_t reflectPointLine(pt_t a, pt_t b, pt_t c) {
  return 2 * projectPointLine(a, b, c) - c;
}

// Project point C onto line segment through A and B
pt_t projectPointSegment(pt_t a, pt_t b, pt_t c) {
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
ld distancePointSegment(pt_t a, pt_t b, pt_t c) {
  return dist(c, projectPointSegment(a, b, c));
}

// Determines if C is between A and B
bool between(pt_t a, pt_t b, pt_t c) {
  if (a == b)
    return a == c;
  return cmp(cross(a - c, b - c), eq, 0) and not cmp(dot(a - c, b - c), gt, 0);
}

// Determines if A, B and C are collinear
bool collinear(pt_t a, pt_t b, pt_t c) {
  return cmp(area2(a, b, c), eq, 0);
}

// Determine if lines from A to B and C to D are parallel
bool linesParallel(pt_t a, pt_t b, pt_t c, pt_t d) {
  return cmp(cross(b - a, c - d), eq, 0);
}

// Determine if lines from a to b and c to d are collinear;
bool linesCollinear(pt_t a, pt_t b, pt_t c, pt_t d) {
  if (not linesParallel(a, b, c, d))
    return false;
  if (not cmp(abs(cross(a - b, a - c)), eq, 0) or not cmp(abs(cross(c - d, c - a)), eq, 0))
    return false;
  return true;
}

// Determine if line segment from A to B intersects with line segment from C to D
bool segmentsIntersect(pt_t a, pt_t b, pt_t c, pt_t d) {
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
pt_t computeLineIntersection(pt_t a, pt_t b, pt_t c, pt_t d) {
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
pt_t computeSegmentIntersection(pt_t a, pt_t b, pt_t c, pt_t d) {
  assert(segmentsIntersect(a, b, c, d));
  return computeLineIntersection(a, b, c, d);
}

// Compute circle passing through 3 given points
pt_t computeCircleCenter(pt_t a, pt_t b, pt_t c) {
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
vector<pt_t> circleCircleIntersection(pt_t p, ld r1, pt_t q, ld r2) {
  ld d = dist(p, q);
  if (cmp(d, gt, r1 + r2) or cmp(d + min(r1, r2), lt, max(r1, r2)))
    return vector<pt_t>();
  ld x = (d * d - r2 * r2 + r1 * r1) / (2 * d);
  ld y = sqrt(r1 * r1 - x * x);
  pt_t v = (q - p) / d;
  vector<pt_t> ret;
  ret.push_back(p + v * x + ccw90(v) * y);
  if (cmp(y, gt, 0))
    ret.push_back(p + v * x - ccw90(v) * y);
  return ret;
}
