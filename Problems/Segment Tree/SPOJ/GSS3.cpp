#include <bits/stdc++.h>

using namespace std;

const int oo = 2e9;
const int maxn = 5e5 + 10;

inline int L(const int x) { return (x << 1); }
inline int R(const int x) { return (x << 1|1); }

struct node {
	int s, l, r, h;
	node() { s = l = r = h = 0; }
	node(int _s, int _l, int _r, int _h) : s(_s), l(_l), r(_r), h(_h) {}
	node(const int v) : s(v), l(v), r(v), h(v) {}
	inline node operator + (const node& n) {
		return {s + n.s, max(l, s + n.l), max(n.r, n.s + r), max({h, n.h, r + n.l})};
	}
};
 
int n, q;
node t[maxn << 1];
 
inline void build() {
	for(int x = n - 1; x; x--) {
		t[x] = t[L(x)] + t[R(x)];
	}
}
 
inline void modify(int x, const int &c) {
	for(t[x += n] = node(c), x >>= 1; x; x >>= 1) {
		t[x] = t[L(x)] + t[R(x)];
	}
}
 
inline int query(int l, int r) {
	node nl, nr = nl = node(0, -oo, -oo, -oo);
	for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
		if(l & 1) {
			nl = nl + t[l++];
		}
		if(r & 1) {
			nr = t[--r] + nr;
		}
	}
	return (nl + nr).h;
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	for(int i = 0; i < n; i++) {
		int c;
		cin >> c;
		t[i + n] = node(c);
	} build();
	cin >> q;
	while(q--) {
		int c, a, b; cin >> c >> a >> b;
		if(c) {
			cout << query(--a, --b) << '\n';
		} else {
			modify(--a, b);
		}
	}
	return 0;
}
