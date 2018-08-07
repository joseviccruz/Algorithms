#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct fenwick { // 1-based indexing
	vector<T> t;
	int n;
	
	fenwick(int _n) : n(_n) { t.resize(n + 1); }
	
	inline void modify(int x, T v) {
		assert(x > 0 && x <= n);
		for(; x <= n; x += x & -x) {
			t[x] += v;
		}
	}
	inline void upd(int x, T v) { return modify(x, v); }
	
	inline T get(int x) {
		assert(x >= 0 && x <= n);
		T ans{};
		for(; x; x -= x & -x) {
			ans += t[x];
		}
		return ans;
	}
	inline T query(int x) { return get(x); }
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	return 0;
}
