#include <bits/stdc++.h>

using namespace std;

inline int L(const int &x) { return (x << 1); }
inline int R(const int &x) { return (x << 1)|1; }

struct node {
	int ans, l, r;
	node(int _ans = 0, int _l = 0, int _r = 0) : ans(_ans), l(_l), r(_r) {}
	inline node operator + (const node x) const {
		int aux = min(l, x.r);
		return node(ans + x.ans + aux, l + x.l - aux, r + x.r - aux);
	}
};

int n, m;
string s;
vector<node> t;

inline void build() {
	for(int x = n - 1; x; x--) {
		t[x] = t[L(x)] + t[R(x)];
	}
}

inline int query(int l, int r) {
	node ansl, ansr;
	for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
		if(l & 1) {
			ansl = ansl + t[l++];
		}
		if(r & 1) {
			ansr = t[--r] + ansr;
		}
	}
	return (ansl + ansr).ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> s;
	n = s.size();
	t.resize(n << 1);
	for(int i = 0; i < n; i++) {
		if(s[i] == '(') {
			t[i + n].l = 1;
		} else {
			t[i + n].r = 1;
		}
	} build();
	cin >> m;
	while(m--) {
		int x, y;
		cin >> x >> y;
		cout << (query(--x, --y) << 1) << '\n';
	}
	return 0;
}
