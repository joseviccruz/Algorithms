using F = ...; // type

const F eps = 1e-6;

int cmp(F a, F b = 0.0) { return abs(a - b) < eps ? 0 : (a < b) ? -1 : +1; }

struct PT {
	F x, y;
	PT(const F x = 0.0, const F y = 0.0) : x(x), y(y) {}
	
	// + - * /
	PT operator +(const PT &p) const { return PT(x + p.x, y + p.y); }
	PT operator -(const PT &p) const { return PT(x - p.x, y - p.y); }
	PT operator *(F k) const { return PT(x * k, y * k); }
	PT operator /(F k) const { return PT(x / k, y / k); }

	// Dot, Cross, Angle, Norm
	F operator *(const PT &p) const { return x * p.x + y * p.y; } // v · w == v * w
	F operator %(const PT &p) const { return x * p.y - y * p.x; } // v ⨯ w == v % w
	F operator ^(const PT &p) const { return atan2(*this % p, *this * p); } // angle(a, b) == a ^ b
	F operator !() const { return sqrt(x * x + y * y); } // |u| == !u
};
