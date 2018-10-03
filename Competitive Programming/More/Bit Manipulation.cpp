template<typename T>
inline bool check_bit(const T &n, const int b) { return n & (T(1) << b); }

template<typename T>
inline void set_bit(T &n, const int b) { n |= (T(1) << b); }

template<typename T>
inline void remove_bit(T &n, const int b) { n &= ~(T(1) << b); }

template<typename T>
inline void flip_bit(T &n, const int b) { n ^= (T(1) << b); }

template<typename T>
inline int count_bits(const T &n) {
	int ans = 0;
	for(register T x = n; x; x >>= 1) {
		ans += (x & 1);
	}
	return ans;
}
/*
	Things to remember:
	- std::bitset<size_t> just have '==' and '!=' defined;
	- ...
*/
