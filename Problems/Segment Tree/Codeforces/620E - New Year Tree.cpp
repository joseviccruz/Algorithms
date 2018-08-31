#include <bits/stdc++.h>

using namespace std;

int n, m, timer;
vector<int> v, id, tin, tout;
vector<vector<int>> adj;
vector<long long> t, lazy;

void dfs(int on, int p) {
	id[timer] = on;
	tin[on] = timer++;
	for(int &to : adj[on]) {
		if(to != p) {
			dfs(to, on);
		}
	}
	tout[on] = timer - 1;
}

void build(int x = 1, int l = 0, int r = n - 1) {
	if(l == r) {
		t[x] = (1ll << v[id[l]]);
	} else {
		int m = (l + r) / 2;
		build(x + x, l, m);
		build(x + x + 1, m + 1, r);
		t[x] = t[x + x] | t[x + x + 1];
	}
}

void modify(int a, int b, int c, int x = 1, int l = 0, int r = n - 1) {
	if(lazy[x]) {
		t[x] = lazy[x];
		if(l != r) {
			lazy[x + x] = lazy[x];
			lazy[x + x + 1] = lazy[x];
		}
		lazy[x] = 0;
	}
	if(a > r || l > b) {
		return;
	}
	if(a <= l && r <= b) {
		t[x] = (1ll << c);
		if(l != r) {
			lazy[x + x] = (1ll << c);
			lazy[x + x + 1] = (1ll << c);
		}
		return;
	}
	int m = (l + r) / 2;
	modify(a, b, c, x + x, l, m);
	modify(a, b, c, x + x + 1, m + 1, r);
	t[x] = t[x + x] | t[x + x + 1];
}

long long query(int a, int b, int x = 1, int l = 0, int r = n - 1) {
	if(lazy[x]) {
		t[x] = lazy[x];
		if(l != r) {
			lazy[x + x] = lazy[x];
			lazy[x + x + 1] = lazy[x];
		}
		lazy[x] = 0;
	}
	if(a > r || l > b) {
		return 0;
	}
	if(a <= l && r <= b) {
		return t[x];
	}
	int m = (l + r) / 2;
	return query(a, b, x + x, l, m) | query(a, b, x + x + 1, m + 1, r);
}

int main() {
	scanf("%d %d", &n, &m);
	v = id = tin = tout = vector<int>(n);
	adj = vector<vector<int>>(n);
	t = lazy = vector<long long>(4 * n);
	int aux = 1;
	for(int &x : v) {
		scanf("%d", &x);
	}
	for(int i = 0; i < n - 1; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		adj[--a].push_back(--b);
		adj[  b].push_back(  a);
	}
	dfs(0, 0);
	build();
	while(m--) {
		int a, b, c;
		scanf("%d %d", &a, &b);
		--b;
		if(a == 1) {
			scanf("%d", &c);
			modify(tin[b], tout[b], c);
			continue;
		}
		int ans = 0;
		for(long long q = query(tin[b], tout[b]); q; ans += (q & 1), q >>= 1);
		printf("%d%c", ans, " \n"[!m]);
	}
	return 0;
}
