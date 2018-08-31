#include <bits/stdc++.h>

using namespace std;

int n;
unordered_map<int, int> freq;
vector<int> v, ql, qr;

vector<int> t;

inline int L(const int &x) { return (x << 1); }
inline int R(const int &x) { return (x << 1)|1; }

inline void update(int x) {
	for(t[x += n]++, x >>= 1; x; x >>= 1) {
		t[x] = t[L(x)] + t[R(x)];
	}
}

inline int query(int l, int r) {
	int ans = 0;
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
	v.resize(n);
	ql.resize(n);
	qr.resize(n);
	t.resize((n + 2) << 1);
	for(int i = 0; i < n; i++) {
		cin >> v[i];
		ql[i] = ++freq[v[i]];
	}
	freq.clear();
	for(int i = n - 1; ~i; i--) {
		qr[i] = ++freq[v[i]];
	}
	long long ans = 0;
	for(int i = n - 1; ~i; i--) {
		ans += query(1, ql[i] - 1);
		update(qr[i]);
	}
	cout << ans << '\n';
	return 0;
}
