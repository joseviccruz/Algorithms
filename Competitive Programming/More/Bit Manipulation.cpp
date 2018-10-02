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
	for(int i = 0; i < sizeof(T) * 8; i++) {
		ans += check_bit(n, i);
	}
	return ans;
}
