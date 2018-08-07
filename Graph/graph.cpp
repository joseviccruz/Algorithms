#include <bits/stdc++.h>

using namespace std;

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
		if(cnj[a] != cnj[b]) {
			cnj[cnj[a]] = b;
			return true;
		}
		return false;
	}
};

namespace Graph {
	template<typename T>
	struct edge {
		int from, to;
		T cost;
		
		edge(const int _from, const int _to, const T _cost) : from(_from), to(_to), cost(_cost) {}
	};

	template<typename T>
	struct graph {
		int n;
		vector<edge<T>> edges;
		vector<vector<int>> adj;
		
		graph(const int _n) : n(_n) { adj.resize(n); }
		
		inline size_t size() const { return n; }
	};
	
	template<typename T>
	struct digraph : public graph<T> {
		using graph<T>::n;
		using graph<T>::edges;
		using graph<T>::adj;
		
		digraph(const int _n) : graph<T>(_n) {}
		
		inline int add(const int a, const int b, const T c) {
			assert(a >= 0 && a < n && b >= 0 && b < n);
			int id = edges.size();
			adj[a].push_back(id);
			edges.emplace_back(a, b, c);
			return id;
		}
		
		inline digraph<T> reverse() const {
			digraph<T> rev(n);
			for(edge<T> &e : edges) {
				rev.add(e.to, e.from, e.cost);
			}
			return rev;
		}
	};
	
	template<typename T>
	struct undigraph : public graph<T> {
		using graph<T>::n;
		using graph<T>::edges;
		using graph<T>::adj;
		
		undigraph(const int _n) : graph<T>(_n) {}
		
		inline int add(const int a, const int b, const T c) {
			assert(a >= 0 && a < n && b >= 0 && b < n);
			int id = edges.size();
			adj[a].push_back(id);
			adj[b].push_back(id);
			edges.emplace_back(a, b, c);
			return id;
		}
	};
	
	template<typename T>
	vector<T> dijkstra(const graph<T> &g, const int start) {
		assert(start >= 0 && start < g.size());
		vector<T> dist(g.size(), numeric_limits<T>::max());
		priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> heap;
		dist[start] = {};
		heap.emplace(dist[start], start);
		while(!heap.empty()) {
			int idx;
			T d;
			tie(d, idx) = heap.top();
			heap.pop();
			if(d > dist[idx]) continue;
			for(int id : g.adj[idx]) {
				edge<T> e = g.edges[id];
				int to = idx ^ e.from ^ e.to;
				if(d + e.cost < dist[to]) {
					dist[to] = d + e.cost;
					heap.emplace(dist[to], to);
				}
			}
		}
		return dist;
	}
	
	template<typename T>
	vector<T> spfa(const graph<T> &g, const int start) {
		assert(start >= 0 && start < g.size());
		queue<int> q;
		vector<bool> in_queue(g.size());
		vector<T> dist(g.size(), numeric_limits<T>::max());
		q.push(start);
		dist[start] = {};
		in_queue[start] = true;
		while(!q.empty()) {
			int idx = q.front();
			T d = dist[idx];
			in_queue[idx] = false;
			q.pop();
			for(int id : g.adj[idx]) {
				edge<T> e = g.edges[id];
				int to = idx ^ e.from ^ e.to;
				if(d + e.cost < dist[to]) {
					dist[to] = d + e.cost;
					if(!in_queue[to]) {
						q.push(to);
						in_queue[to] = true;
					}
				}
			}
		}
		return dist;
	}
	
	template<typename T>
	pair<T, vector<int>> kruskal(const graph<T> &g) {
		vector<int> order(g.edges.size());
		iota(order.begin(), order.end(), 0);
		sort(order.begin(), order.end(), [&g](const int &a, const int &b) {
			return g.edges[a].cost < g.edges[b].cost;
		});
		T ansf = {};
		vector<int> anss;
		dsu uf(g.size());
		for(int &id : order) {
			if(uf.join(g.edges[id].from, g.edges[id].to)) {
				ansf += g.edges[id].cost;
				anss.push_back(id);
			}
		}
		return make_pair(ansf, anss);
	}
	
	template<typename T>
	pair<T, vector<int>> prim(const graph<T> &g, const int start = 0) {
		assert(start >= 0 && start < g.size());
		vector<bool> taken(g.size());
		priority_queue<tuple<T, int, int>, vector<tuple<T, int, int>>, greater<tuple<T, int, int>>> heap;
		heap.emplace((T) {}, start, -1);
		T ansf = {};
		vector<int> anss;
		while(!heap.empty()) {
			int idx;
			T d;
			int eid;
			tie(d, idx, eid) = heap.top();
			heap.pop();
			if(taken[idx]) continue;
			taken[idx] = true;
			ansf += d;
			if(~eid) anss.push_back(eid);
			for(int id : g.adj[idx]) {
				edge<T> e = g.edges[id];
				int to = idx ^ e.from ^ e.to;
				if(!taken[to]) {
					heap.emplace(e.cost, to, id);
				}
			}
		}
		return make_pair(ansf, anss);
	}
}

using namespace Graph;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	return 0;
}
