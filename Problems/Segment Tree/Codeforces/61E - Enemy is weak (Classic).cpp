#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> t, v;
vector<long long> ql, qr;
map<int, int> key;

inline int L(const int &x) { return (x << 1); }
inline int R(const int &x) { return (x << 1)|1; }

inline void modify(int x) {
	for(t[x += n]++, x >>= 1; x; x >>= 1) {
		t[x] = t[L(x)] + t[R(x)];
	}
}

inline long long query(int l, int r) {
	long long ans = 0;
	for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
		if(l & 1) {
			ans += t[l++];
		}
		if(r & 1) {
			ans += t[--r];	
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	v.resize(n), ql.resize(n), qr.resize(n);
	for(int i = 0; i < n; i++) {
		cin >> v[i];
		key[v[i]] = true;
	}
	int aux = 0;
	for(auto &u : key) {
		u.second = aux++;
	}
	t.assign((key.size() + 1) << 1, 0);
	for(int i = n - 1; ~i; i--) {
		if(i > 0 && i < n - 1) {
			qr[i] = query(0, key[v[i]] - 1);
		}
		modify(key[v[i]]);
	}
	t.assign((key.size() + 1) << 1, 0);
	for(int i = 0; i < n; i++) {
		if(i > 0 && i < n - 1) {
			ql[i] = query(key[v[i]] + 1, key.size());
		}
		modify(key[v[i]]);
	}
	long long ans = 0;
	for(int i = 0; i < n; i++) {
		ans += qr[i] * ql[i];
	}
	cout << ans << '\n';
	return 0;
}
