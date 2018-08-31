#include <bits/stdc++.h>

using namespace std;

inline int L(const int &x) { return (x << 1); }
inline int R(const int &x) { return (x << 1)|1; }

int n, M;
vector<int> A, B, t, lazy;

void build(int x = 1, int l = 1, int r = n) {
	if(l == r) {
		t[x] = B[l];
	} else {
		int m = (l + r) / 2;
		build(L(x), l, m); build(R(x), m + 1, r);
	}
}

void modify(int a, int b, int offset, int x = 1, int l = 1, int r = n) {
	if(lazy[x] != 1e9) {
		if(l != r) {
			lazy[L(x)] = lazy[R(x)] = lazy[x];
		} else {
			t[x] = A[l + lazy[x]];
		}
		lazy[x] = 1e9;
	}
	if(l > b || a > r) return;
	if(a <= l && r <= b) {
		if(l != r) {
			lazy[L(x)] = lazy[R(x)] = offset;
		} else {
			t[x] = A[l + offset];
		}
		return;
	}
	int m = (l + r) / 2;
	modify(a, b, offset, L(x), l, m); modify(a, b, offset, R(x), m + 1, r);
}

int query(int idx, int x = 1, int l = 1, int r = n) {
	if(lazy[x] != 1e9) {
		if(l != r) {
			lazy[L(x)] = lazy[R(x)] = lazy[x];
		} else {
			t[x] = A[l + lazy[x]];
		}
		lazy[x] = 1e9;
	}
	if(l > idx || idx > r) return 0;
	if(l == r) {
		return t[x];
	}
	int m = (l + r) / 2;
	return query(idx, L(x), l, m) + query(idx, R(x), m + 1, r);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> M;
	A.resize(n + 1);
	B.resize(n + 1);
	t.resize((n + 1) << 2);
	lazy.assign((n + 1) << 2, 1e9);
	for(int i = 1; i <= n; i++) {
		cin >> A[i];
	}
	for(int i = 1; i <= n; i++) {
		cin >> B[i];
	} build();
	while(M--) {
		int o; cin >> o;
		if(o == 1) {
			int x, y, z;
			cin >> x >> y >> z;
			modify(y, y + (z - 1), x - y);
		} else {
			int x;
			cin >> x;
			cout << query(x) << '\n';
		}
	}
	return 0;
}
