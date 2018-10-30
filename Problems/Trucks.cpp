// https://uva.onlinejudge.org/external/126/p12655.pdf
#include <bits/stdc++.h>

using namespace std;

class hld_graph { // hld + lca
public:
	using T = int;
	
	struct edge {
		int from;
		int to;
		T cost;
		edge(int a, int b, int c)
		: from(a), to(b), cost(c) {}
	};
	const int maxl = 25;
	int n, tt;
	vector<edge> edges;
	vector<vector<int>> adj, up;
	vector<int> nxt, sz, in, out, rin, eid;
	
	void init(int n) {
		this->n = n;
		tt = 0;
		edges = vector<edge>();
		adj = vector<vector<int>>(n);
		up = vector<vector<int>>(n, vector<int>(maxl));
		nxt = sz = in = out = rin = eid = vector<int>(n);
	}
	
	void add(int a, int b, T c) {
		assert(a >= 0 && b >= 0 && a < n && b < n);
		int id = edges.size();
		adj[a].push_back(id);
		adj[b].push_back(id);
		edges.emplace_back(a, b, c);
	}
	
	void dfs_sz(int v, int p) {
		sz[v] = 1;
		for(int &id : adj[v]) {
			int u = edges[id].from ^ edges[id].to ^ v;
			int front = edges[adj[v][0]].from ^ edges[adj[v][0]].to ^ v;
			if(u == p)
				continue;
			dfs_sz(u, v);
			sz[v] += sz[u];
			if(front == p || sz[u] > sz[front])
				swap(adj[v][0], id);
		}
	}
	
	void dfs_hld(int v, int p) {
		in[v] = tt++;
		rin[in[v]] = v;
		up[v][0] = p;
		for(int i = 1; i < maxl; i++)
			up[v][i] = up[up[v][i - 1]][i - 1];
		for(int &id : adj[v]) {
			int u = edges[id].from ^ edges[id].to ^ v;
			if(u == p) {
				eid[id] = v; // which vertex include this edge
				continue;
			}
			nxt[u] = (&id == &adj[v][0]) ? nxt[v] : u;
			dfs_hld(u, v);
		}
		out[v] = tt;
	}
	
	void dfs_all(int v = 0) {
		dfs_sz(v, v);
		dfs_hld(v, v);
	}
	
	bool anc(int x, int y) {
		return in[x] <= in[y] && out[x] >= out[y];
	}
	
	int lca(int x, int y) {
		if(anc(x, y))
			return x;
		if(anc(y, x))
			return y;
		for(int i = maxl - 1; ~i; i--) {
			if(!anc(up[x][i], y))
				x = up[x][i];
		}
		return up[x][0];
	}
	
	// y always has a lower depth than x
	T get(int x, int y, function<T(T, T)> merge, function<T(int, int)> f) {
		T ans = 1e9;
		for(; nxt[x] != nxt[y]; x = up[nxt[x]][0]) {
			ans = merge(ans, f(in[nxt[x]], in[x]));
		}
		return merge(ans, f(in[y] + 1, in[x])); // in[y] + 1 to doesn't include last node
	}
	
	T query(int x, int y, function<T(T, T)> merge, function<T(int, int)> f) {
		int k = lca(x, y);
		// sometimes need to remove lca query because it was included twice
		return merge(get(x, k, merge, f), get(y, k, merge, f));
	}
};

struct dsu {
	vector<int> cnj;
	int n;
	dsu(const int _n) : n(_n) {
		cnj.resize(n);
		iota(cnj.begin(), cnj.end(), 0);
	}
	inline int root(int x) {
		return (x == cnj[x] ? x : (cnj[x] = root(cnj[x])));
	}
	inline bool join(const int a, const int b) {
		cnj[a] = root(a);
		cnj[b] = root(b);
		if(a != b) {
			cnj[cnj[a]] = b;
			return true;
		}
		return false;
	}
};

const int maxn = 2e4 + 10;

int n, m, s;
int st[maxn + maxn];

inline void build() {
	for(int x = n - 1; x; x--) {
		st[x] = min(st[x + x], st[x + x + 1]);
	}
}
 
inline void modify(int x, int c) {
	for(st[x += n] = c, x >>= 1; x; x >>= 1) {
		st[x] = min(st[x + x], st[x + x + 1]);
	}
}
 
inline int query(int l, int r) {
	int ans = 1e9;
	for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
		if(l & 1) {
			ans = min(st[l++], ans);
		}
		if(r & 1) {
			ans = min(ans, st[--r]);
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	hld_graph g;
	while(cin >> n >> m >> s) {
		{
			g.init(n);
			vector<tuple<int, int, int>> ve;
			for(int i = 0; i < m; i++) {
				int a, b, c;
				cin >> a >> b >> c;
				ve.emplace_back(c, --a, --b);
			}
			sort(ve.rbegin(), ve.rend());
			dsu uf(n);
			for(auto &tu : ve) {
				int c, a, b;
				tie(c, a, b) = tu;
				if(uf.root(a) != uf.root(b)) {
					g.add(a, b, c);
					uf.join(a, b);
				}
			}
		}
		g.dfs_all();
		for(int i = 0; i < n - 1; i++) {
			st[g.in[g.eid[i]] + n] = g.edges[i].cost;
		}
		build();
		while(s--) {
			int a, b;
			cin >> a >> b;
			cout << g.query(--a, --b, [](int a, int b) -> int { return min(a, b); }, query) << '\n';
		}
	}
	return 0;
}
