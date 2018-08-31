#include <bits/stdc++.h>

using namespace std;

int n;
vector<vector<int>> t;

inline int L(const int &x) { return (x << 1); }
inline int R(const int &x) { return (x << 1)|1; }

inline void build() {
	for(int x = n - 1; x; x--) {
		merge(t[L(x)].begin(), t[L(x)].end(),
		      t[R(x)].begin(), t[R(x)].end(),
		      back_inserter(t[x]));
	}
}

inline long long query(int l, int r, const int &a, bool op) { // false == left, true == right
	long long ans = 0;
	for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
		if(l & 1) {
			if(op) {
				int idx = lower_bound(t[l].begin(), t[l].end(), a) - t[l].begin();
				ans += idx;
			} else {
				int idx = upper_bound(t[l].begin(), t[l].end(), a) - t[l].begin();
				ans += t[l].size() - idx;
			}
			l++;
		}
		if(r & 1) {
			--r;
			if(op) {
				int idx = lower_bound(t[r].begin(), t[r].end(), a) - t[r].begin();
				ans += idx;
			} else {
				int idx = upper_bound(t[r].begin(), t[r].end(), a) - t[r].begin();
				ans += t[r].size() - idx;
			}	
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	t.resize((n + 1) << 1);
	for(int i = 0; i < n; i++) {
		t[i + n].push_back(0);
		cin >> t[i + n].back();
	} build();
	long long ans = 0;
	for(int i = 1; i + 1 < n; i++) {
		ans += query(0, i - 1, t[i + n].back(), false) * query(i + 1, n, t[i + n].back(), true);
	}
	cout << ans << '\n';
	return 0;
}
