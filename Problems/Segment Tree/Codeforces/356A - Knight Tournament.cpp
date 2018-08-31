#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> t;

inline int L(const int &x) { return (x << 1); }
inline int R(const int &x) { return (x << 1)|1; }

void modify(int a, int b, int c, int x = 1, int l = 1, int r = n) {
	if(l > b || a > r || t[x]) return;
	if(l == r) {
		if(c != l) t[x] = c;	
	} else {
		int m = (l + r) / 2;
		modify(a, b, c, L(x), l, m), modify(a, b, c, R(x), m + 1, r);
		t[x] = (t[L(x)] && t[R(x)]) ? true : false;
	}
}

int query(int a, int x = 1, int l = 1, int r = n) {
	if(l > a || a > r) return false;
	if(l == r) {
		return t[x];
	}
	int m = (l + r) / 2;
	return max(query(a, L(x), l, m), query(a, R(x), m + 1, r));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	t.resize(n << 2);
	while(m--) {
		int x, y, z;
		cin >> x >> y >> z;
		modify(x, y, z);
	}
	for(int i = 1; i <= n; i++) {
		cout << query(i) << " \n"[i == n];
	}
	return 0;
}
