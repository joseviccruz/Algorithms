// (x1, y1) is left down
// (x2, y2) is right up

struct rect_t {
  using lint = long long;
  lint x1, y1, x2, y2;
  
  rect_t() {
  }
  
  rect_t(lint x1, lint y1, lint x2, lint y2) : x1(x1), y1(y1), x2(x2), y2(y2) {
    assert(x1 <= x2);
    assert(y1 <= y2);
  }
};
 
bool intersect(const rect_t &a, const rect_t &b) {
  if ((a.x2 < b.x1) || (b.x2 < a.x1))
    return false;
  if ((a.y2 < b.y1) || (b.y2 < a.y1))
   return false;
  return true;
}
 
bool intersect(const rect_t &a, const rect_t &b, rect_t &ret) {
  if (!intersect(a, b)) {
    ret = rect_t(0, 0, 0, 0);
    return false;
  }
  ret = rect_t(max(a.x1, b.x1), max(a.y1, b.y1), min(a.x2, b.x2), min(a.y2, b.y2));
  return true;
}
 
long long area(const rect_t &rect) {
  return (rect.x2 - rect.x1) * (rect.y2 - rect.y1);
}
