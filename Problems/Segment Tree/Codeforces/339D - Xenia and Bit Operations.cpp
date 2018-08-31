#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> t;

inline int L(const int &x) { return (x << 1); }
inline int R(const int &x) { return (x << 1)|1; }

bool modify(int a, int b, int x = 1, int l = 1, int r = (1 << n)) {
	if(l > a || r < a) return false;
	if(l == r) {
		t[x] = b;
		return true;
	} else {
		int m = (l + r) / 2;
		if(modify(a, b, L(x), l, m) || modify(a, b, R(x), m + 1, r)) {
			t[x] = t[L(x)] | t[R(x)];
			return false;
		} else {
			t[x] = t[L(x)] ^ t[R(x)];
			return true;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	t.resize(((1 << n) + 1) << 2);
	for(int i = 1; i <= (1 << n); i++) {
		int x;
		cin >> x;
		modify(i, x);
	}
	while(m--) {
		int a, b;
		cin >> a >> b;
		modify(a, b);
		cout << t[1] << '\n';
	}
	return 0;
}
