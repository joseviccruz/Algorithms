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
