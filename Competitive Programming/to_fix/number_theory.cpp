#include <bits/stdc++.h>

using namespace std;

using llu = long long unsigned;
using ld = long double;
using ll = long long;

namespace NumberTheory {
	const vector<llu> auxp = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	
	inline bool overflow(const llu x, const llu y, const llu oo = (1llu << 63) - 1) {
		return (ld) x * (ld) y > (ld) oo;
	}
	
	inline llu fmul(llu x, llu y, const llu mod = 1e9 + 7) {
		if(!overflow(x, y)) return (x * y) % mod;
		llu ans = 0;
		for(; y; y >>= 1) {
			if(y & 1) {
				ans = (ans + x) % mod;
			}
			x = (x + x) % mod;
		}
		return ans;
	}
	
	inline llu fexp(llu x, llu e, const llu mod = 1e9 + 7) {
		llu ans = 1;
		for(; e; e >>= 1) {
			if(e & 1) {
				ans = fmul(ans, x, mod);
			}
			x = fmul(x, x, mod);
		}
		return ans;
	}
	
	inline vector<llu> sieve(const int x) {
		vector<llu> aux(x);
		iota(aux.begin(), aux.end(), 0);
		for(register int i = 2; i < x; i++) {
			if(aux[i] != i) continue;
			for(register int j = 2; i * j < x; j++) {
				aux[i * j] = min(aux[i * j], (llu) i);
			}
		}
		return aux;
	}
	
	inline llu gcd(llu a, llu b) {
		while(a) {
			b %= a;
			swap(a, b);
		}
		return b;
	}
	
	inline llu lcm(const llu a, const llu b) { return (a / gcd(a, b)) * b; }
	
	pair<ll, ll> euclides(ll a, ll b) {
		/*
		- Using prime numbers: a ^ (b - 2) * a == 1 mod b
		- a * x + b * y = gcd(a, b), a * x + b * y = 1
		*/
		ll x = 0, ox = 1;
		ll y = 1, oy = 0;
		while(b) {
			ll q = a / b;
			ox = ox - x * q;
			oy = oy - y * q;
			a = a - b * q;
			swap(a, b);
			swap(x, ox);
			swap(y, oy);
		}
		return make_pair(ox, oy);
	}
	
	inline bool millerRabin(llu a, llu n) {
		/*
		- n = 2 ^ t * s + 1;
		- n is prime with >= 75% if:
			a ^ s == 1 mod n
			a ^ (s * 2 ^ i) == (n - 1) mod n to some value in this range [0 <= i < t]
		*/
		llu t = 0, s = n - 1;
		for(; !(s & 1); t++, s >>= 1);
		if(!(a %= n)) return true;
		llu f = fexp(a, s, n);
		if(f == 1 || f == n - 1) return true;
		for(register int i = 1; i < t; i++) {
			if((f = fmul(f, f, n)) == (n - 1)) return true;
		}
		return false;
	}
	
	// No of divisors of a number = (1 + a) * (1 + b) * ... * (1 + n), where [a, b, ..., n]
	// are coefficients of each prime value that divides this number.
}

using namespace NumberTheory;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	return 0;
}
