template <typename T>
struct FlowNetwork {
	struct Edge {
		int to;
		T cap;
		Edge(int a, T b) : to(a), cap(b) {}
	};

	int n;
	vector<vector<int>> adj;
	vector<Edge> edges;
	vector<int> level, on;

	FlowNetwork(int a = 0) {
		n = a;
		adj.resize(a + 2);
	}

	void init(int a) {
		adj.clear();
		edges.clear();
		adj.resize(a + 1);
		n = a;
	}

	void addEdge(int from, int to, T cap) {
		adj[from].push_back(int(edges.size()));
		edges.push_back(Edge(to, cap));
		adj[to].push_back(int(edges.size()));
		edges.push_back(Edge(from, 0));
	}

	bool bfs(int sink, int src) {
		level = vector<int>(n + 2, 0);
		queue<int> q;
		level[sink] = 0;
		q.push(sink);
		while(!q.empty()) {
			int cur = q.front();
			q.pop();
			for(int id : adj[cur]) {
				if (edges[id].cap == 0) continue;
				int to = edges[id].to;
				if (level[to] == 0 && to != sink) {
					q.push(to);
					level[to] = level[cur] + 1;
				}
			}
		}
		return level[src] > 0;
	}

	T dfs(int v, int src, T cur) {
		if (v == src) return cur;
		for(; on[v] < adj[v].size(); on[v]++) {
			int id = adj[v][on[v]];
			if (level[v] + 1 != level[edges[id].to]) {
				continue;
			}
			if (edges[id].cap > 0) {
				T temp = dfs(edges[id].to, src, min(cur, edges[id].cap));
				if (temp > 0) {
					edges[id].cap -= temp;
					edges[id ^ 1].cap += temp;
					return temp;
				}
			}
		}
		return 0;
	}

	T max_flow_dinic(int sink, int src) {
		T ans = 0;
		while(bfs(sink, src)) {
			on = vector<int>(n + 2, 0);
			T cur;
			while(cur = dfs(sink, src, 1e9)) {
				ans += cur;
			}
		}
		return ans;
	}

   	bool dfs_scaling(int v, int src, T lim) {
        	if (lim == 0) return 0;
			if (v == src) return 1;
			for(; on[v] < adj[v].size(); on[v]++) {
				int id = adj[v][on[v]];
				if (level[v] + 1 != level[edges[id].to]) {
					continue;
				}
				if (edges[id].cap >= lim) {
					if (dfs(edges[id].to, src, lim)) {
						edges[id].cap -= lim;
						edges[id ^ 1].cap += lim;
						return 1;
					}
				}
			}
			return 0;
	 }

  	 T max_flow_scaling(int sink, int src, int scale) {
		T ans = 0;
		T lim = (1 << min(scale, 32));

		while (lim >= 1) {
	            if (!bfs(sink, src)) {
			lim >>= 1;
			continue;
		    }

	 	    on = vector<int>(n + 2, 0);

		    while(dfs_scaling(sink, src, 1e9)) {
					ans += lim;
           	    }
	         }

                 return ans;
         }
};
