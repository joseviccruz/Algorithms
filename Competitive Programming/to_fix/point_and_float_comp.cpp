using namespace rel_ops; // (!=, <=, >, >=) deriving from (== and <)
using F = ...; // type

const F eps = 1e-6;

int cmp(F a, F b = 0.0) { return abs(a - b) < eps ? 0 : (a < b) ? -1 : +1; }

class PT {
public:
	F x, y;
	PT(const F x = 0.0, const F y = 0.0) : x(x), y(y) {}
	
	// + - * /
	PT operator +=(const PT &p) { x += p.x; y += p.y; return *this; }
	PT operator -=(const PT &p) { x -= p.x; y -= p.y; return *this; }
	PT operator *=(F k) { x *= k; y *= k; return *this; }
	PT operator /=(F k) { x /= k; y /= k; return *this; }

	PT operator +(const PT &p) const { return PT(*this) += p; }
	PT operator -(const PT &p) const { return PT(*this) -= p; }
	PT operator *(F k) const { return PT(*this) *= k; }
	PT operator /(F k) const { return PT(*this) /= k; }

	// Dot, Cross, Angle, Norm
	F operator *(const PT &p) const { return x * p.x + y * p.y; } // v · w == v * w
	F operator %(const PT &p) const { return x * p.y - y * p.x; } // v ⨯ w == v % w
	F operator ^(const PT &p) const { return atan2(*this % p, *this * p); } // angle(a, b) == a ^ b
	F operator !() const { return sqrt(x * x + y * y); } // |u| == !u

	// Comparison
	bool operator ==(const PT &p) const { return !cmp(x, p.x) && !cmp(y, p.y); }
	bool operator  <(const PT &p) const { return !cmp(x, p.x) ? cmp(y, p.y) < 0 : cmp(x, p.x) < 0; }
	
	// Methods
	PT resize(F k) const { return (*this) / !(*this) * k; }
	PT rotate(F t) const { return PT(x * cos(t) - y * sin(t), x * sin(t) + y * cos(t)); } // CCW
};
