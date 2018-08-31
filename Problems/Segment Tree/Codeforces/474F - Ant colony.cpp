#include <bits/stdc++.h>

using namespace std;

inline int L(const int &x) { return (x << 1); }
inline int R(const int &x) { return (x << 1|1); }

long long gcd(const long long a, const long long b) { return !a ? b : gcd(b % a, a); }
long long lcm(const long long a, const long long b) { return (a * b) / gcd(a, b); }

struct node {
	int x, qnt;
	node(const int _x = 0, const int _qnt = 0) : x(_x), qnt(_qnt) {}
	inline node operator + (const node &n) const {
		if(x == n.x) {
			return node(x, qnt + n.qnt);
		} else if(gcd(x, n.x) == n.x) {
			return node(n.x, n.qnt);
		} else if(gcd(x, n.x) == x) {
			return node(x, qnt);
		} else {
			return node(gcd(x, n.x), 0);
		}
	}
};

int n, m;
vector<node> t;

inline void build() {
	for(int x = n - 1; x; x--) {
		t[x] = t[L(x)] + t[R(x)];
	}
}

inline int query(int l, int r) {
	node al, ar;
	for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
		if(l & 1) {
			al = al + t[l++];
		}
		if(r & 1) {
			ar = t[--r] + ar;
		}
	}
	return (al + ar).qnt;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	t.resize((n + 1) << 1);
	for(int i = 0; i < n; i++) {
		int x;
		cin >> x;
		t[i + n] = node(x, 1);
	} build();
	cin >> m;
	while(m--) {
		int l, r;
		cin >> l >> r; --l, --r;
		cout << (r - l + 1) - query(l, r) << '\n';
	}
	return 0;
}
