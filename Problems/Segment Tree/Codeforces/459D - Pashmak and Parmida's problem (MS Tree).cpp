#include <bits/stdc++.h>

using namespace std;

int n;
unordered_map<int, int> freq;
vector<int> v, ql, qr;

vector<vector<int>> t;

inline int L(const int &x) { return (x << 1); }
inline int R(const int &x) { return (x << 1)|1; }

inline void build() {
	for(int x = 0; x < n; x++) {
		t[x + n].emplace_back(qr[x]);
	}
	for(int x = n - 1; x; x--) {
		merge(t[L(x)].begin(), t[L(x)].end(), t[R(x)].begin(), t[R(x)].end(), back_inserter(t[x]));
	}
}

inline int query(int l, int r, const int &a) {
	int ans = 0;
	for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
		if(l & 1) {
			int idx = lower_bound(t[l].begin(), t[l].end(), a) - t[l].begin();
			ans += idx;
			l++;
		}
		if(r & 1) {
			--r;
			int idx = lower_bound(t[r].begin(), t[r].end(), a) - t[r].begin();
			ans += idx;
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
	t.resize((n + 1) << 1);
	for(int i = 0; i < n; i++) {
		cin >> v[i];
		ql[i] = ++freq[v[i]];
	}
	freq.clear();
	for(int i = n - 1; ~i; i--) {
		qr[i] = ++freq[v[i]];
	}
	build();
	long long ans = 0;
	for(int i = 0; i + 1 < n; i++) {
		ans += query(i + 1, n, ql[i]);
	}
	cout << ans << '\n';
	return 0;
}
