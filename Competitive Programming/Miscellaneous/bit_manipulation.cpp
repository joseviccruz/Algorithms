template <class T>
inline bool check_bit(const T &n, const int b) { return n & (T(1) << b); }

template <class T>
inline void set_bit(T &n, const int b) { n |= (T(1) << b); }

template <class T>
inline void remove_bit(T &n, const int b) { n &= ~(T(1) << b); }

template <class T>
inline void flip_bit(T &n, const int b) { n ^= (T(1) << b); }
