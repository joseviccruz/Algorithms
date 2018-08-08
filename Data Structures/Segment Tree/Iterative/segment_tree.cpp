template<typename T1>
struct segment_tree { // 0-based indexing
	int n;
	vector<T1> t;
	
	inline int L(const int &x) { return (x << 1); }
	inline int R(const int &x) { return (x << 1)|1; }
	
	segment_tree(const int _n = 0) : n(_n), t(vector<T1>(_n << 1)) {}
};
