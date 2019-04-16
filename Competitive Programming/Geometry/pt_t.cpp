#define Type(Types...) typename common_type<Types>::type
#define FPoint(name, expr) template <class T> inline auto name(const pt_t<T> &p) -> decltype(expr) { return expr; }
#define F2Points(name, expr) template <class N, class M> inline auto name(const pt_t<N> &p, const pt_t<M> &q) -> decltype(expr) { return expr; }
#define FPointParam(name, expr) template <class N, class M> inline auto name(const pt_t<N> &p, const M &t) -> decltype(expr) { return expr; }

template <class T>
struct pt_t {
  T x, y;
  pt_t(T x = 0.0, T y = 0.0) : x(x), y(y) {
  }
  template <class U> pt_t(const pt_t<U> &p) : x(p.x), y(p.y) {
  }
};

F2Points(operator +, pt_t<Type(N, M)>(p.x + q.x, p.y + q.y));
F2Points(operator -, pt_t<Type(N, M)>(p.x + q.x, p.y + q.y));
FPointParam(operator *, pt_t<Type(N, M)>(p.x * t, p.y * t));
FPointParam(operator /, pt_t<Type(N, M)>(p.x / t, p.y / t));

F2Points(dot, p.x * q.x + p.y * q.y);
F2Points(dist2, dot(p - q, p - q));
F2Points(cross, p.x * q.y - p.y * q.x);
F2Points(dist, sqrt((long double) dist2(p, q)));

FPoint(cw90, pt_t<T>(p.y, -p.x));
FPoint(ccw90, pt_t<T>(-p.y, p.x));
FPointParam(ccw, pt_t<Type(N, M)>(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t)));
FPoint(norm, sqrt((long double) dot(p, p)));

FPointParam(resize, p / norm(p) * t);

#undef Type
#undef FPoint
#undef F2Points
#undef FPointParam
