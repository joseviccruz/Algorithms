// https://e-maxx.ru/algo/dinic
// https://github.com/the-tourist/algo/blob/master/flows/flow_graph.cpp

// [!!!] -> Main lines of code to pay attention to

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

using ll = long long;
using ld = long double;
using T = ll; // type of flow [!!!]

struct edge {
	int from;
	int to;
	T c;
	T f;
	edge(int _from, int _to, T _c, T _f) : from(_from), to(_to), c(_c), f(_f) {}
};

const T eps = (T) 1e-9; // Depends on type [!!!]
const T oo = 1e9; // Depends on type [!!!]

int n;
vector<vector<int>> adj;
vector<edge> edges;
vector<int> ptr;
vector<int> d;
vector<int> q; // Queue
T flow; // Depends on type [!!!]

// Adds two edges, flow in and flow out [!!!]
inline int add(int from, int to, T fcap, T bcap) { // fcap and bcap depends on type [!!!]
	assert(0 <= from && from < n && 0 <= to && to < n);
	int id = edges.size();
	edges.emplace_back(from, to, fcap, 0);
	adj[from].push_back(id);
	edges.emplace_back(to, from, bcap, 0);
	adj[to].push_back(id + 1);
	return id;
}

// To reset this flow, just clear all 'f' edges variable and 'flow' variable [!!!]

inline void init() { // Never forget to call this function [!!!]
	edges.clear();
	adj.assign(n, vector<int>());
	ptr.assign(n, 0);
	d.assign(n, 0);
	q.assign(n, 0);
	flow = 0;
}

// bfs is from 'to' to 'from'
inline bool bfs(int from, int to) {
	fill(d.begin(), d.end(), -1);
	q[0] = to;
	d[to] = 0;
	for(int l = 0, r = 1; l < r;) {
		int i = q[l++];
		for(const auto &id : adj[i]) {
			const auto &e = edges[id];
			const auto &b = edges[id ^ 1];
			if(b.c - b.f > eps && d[e.to] == -1) {
				d[e.to] = d[i] + 1;
				if(e.to == from) {
					return true;
				}
				q[r++] = e.to;
			}
		}
	}
	return false;
}
  
T dfs(int from, int to, T w) { // w = oo [!!!]
	if(from == to) {
		return w;
	}
	for(int &j = ptr[from]; j >= 0; j--) {
		int id = adj[from][j];
		const auto &e = edges[id];
		if(e.c - e.f > eps && d[e.to] == d[from] - 1) {
			T t = dfs(e.to, to, min(e.c - e.f, w));
			if(t > eps) {
				edges[id].f += t;
				edges[id ^ 1].f -= t;
				return t;
			}
		}
	}
	return 0;
}

inline T max_flow(int from, int to, bool random = false) {
	while(bfs(from, to)) {
		for(int i = 0; i < n; i++) {
			ptr[i] = (int) adj[i].size() - 1;
			if(random) {
				shuffle(adj[i].begin(), adj[i].end(), rng);
			}
		}
		T big_add = 0;
		for(T add = dfs(from, to, oo); add > eps; add = dfs(from, to, oo)) {
			big_add += add;
		}
		if(big_add <= eps) {
			break;
		}
		flow += big_add;
	}
	return flow;
}
