using lint = long long;

auto get_line(lint x1, lint y1, lint x2, lint y2) {
  struct line_t {
    lint a, b, c;
  };
  if (x1 == x2) {
    return line_t({1, 0, -x1});
  } else if (y1 == y2) {
    return line_t({0, 1, -y1});
  } else {
    lint g = 0;
    g = gcd(g, abs(y2 - y1));
    g = gcd(g, abs(x2 - x1));
    g = gcd(g, abs(x2 * y1 - x1 * y2));
    if (y2 - y1 > 0) {
      return line_t({ (y2 - y1) / g, -(x2 - x1) / g,  (x2 * y1 - x1 * y2) / g});
    } else {
      return line_t({-(y2 - y1) / g,  (x2 - x1) / g, -(x2 * y1 - x1 * y2) / g});
    }
  }
}
