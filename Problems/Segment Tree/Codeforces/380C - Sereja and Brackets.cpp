#include <bits/stdc++.h>

using namespace std;

const int oo = 1e9;

struct node {
	int l, r;
	node(const int l = +oo, const int r = -oo) : l(l), r(r) {}
	inline node operator + (const int x) const { return node(min(l, x), max(r, x)); }
	inline node operator + (const node x) const { return node(min(l, x.l), max(r, x.r)); }
};

int n, m;
string s;
vector<int> op;
vector<vector<node>> t;

inline int L(const int &x) { return (x << 1); }
inline int R(const int &x) { return (x << 1)|1; }

// 0 == '(' // 1 == ')'

inline void build(const bool &o) {
	for(int x = n - 1; x; x--) {
		t[x][o] = t[L(x)][o] + t[R(x)][o];
	}
}

inline node query(int l, int r, const bool &o) {
	node ans;
	for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
		if(l & 1) {
			ans = t[l++][o] + ans;
		}
		if(r & 1) {
			ans = ans + t[--r][o];
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> s;
	n = s.size();
	op.resize(n);
	t.assign((n << 1), vector<node>(2));
	for(int i = 0; i < n; i++) {
		if(i) op[i] += op[i - 1];
		if(s[i] == '(') {
			t[i + n][0] = t[i + n][0] + i;
			op[i]++;
		} else {
			t[i + n][1] = t[i + n][1] + i;
		}
	} build(0), build(1);
	for(auto &u : op) cout << u << " \n"[&u == &op.back()];
	return 0;
	cin >> m;
	while(m--) {
		int x, y;
		cin >> x >> y;
		auto open = query(x, y, 0);
		auto close = query(x, y, 1);

	}
	return 0;
}
