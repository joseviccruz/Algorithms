namespace SegmentTree {
	/*
	struct node {
		// atributes
	
		node() {
			// empty constructor
		}
	
		node() {
			// init
		}
	
		node(const node &l, const node &r) {
			// merge
		}
	
		// get() {
			// returns the answer to the problem
		// }
	
	};
	*/

	template<typename T1>
	struct segment_tree {
		int n;
		vector<T1> t;

		inline int L(const int &x) { return (x << 1); }
		inline int R(const int &x) { return (x << 1)|1; }

		segment_tree() : n(0), t(vector<T1>()) {}
	};

	//T1 == node, T2 == typeof given problem
	template<typename T1, typename T2 = T1>
	struct classic_tree : public segment_tree<T1> { // 0-based indexing
	private:
		using segment_tree<T1>::n;
		using segment_tree<T1>::t;
		using segment_tree<T1>::L;
		using segment_tree<T1>::R;

		inline void build() {
			for(register int x = n - 1; x; x--) {
				t[x] = T1(t[L(x)], t[R(x)]);
			}
		}

	public:
		classic_tree(const int _n = 0) : n(_n), t(vector<T1>(_n)) {}
		classic_tree(const vector<T2> &base) { init(base); }

		inline void init(const vector<T2> &base) {
			n = base.size();
			t = vector<T1>(n << 1);
			for(register int i = 0; i < n; i++) { t[i + n] = T1(base[i]); }
			build();
		}

		inline void modify(int x, const T2 &c) {
			assert(x >= 0 && x < n);
			for(t[x += n] = T1(c), x >>= 1; x; x >>= 1) {
				t[x] = T1(t[L(x)], t[R(x)]);
			}
		}

		inline T1 query(int l, int r) {
			assert((l >= 0 && l < n) && (r >= 0 && r < n));
			T1 ansl{}, ansr{};
			for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
				if(l & 1) {
					ansl = T1(ansl, t[l++]);
				}
				if(r & 1) {
					ansr = T1(ansr, t[--r]);
				}
			}
			return T1(ansl, ansr);
		}
	};
}
