template <int n, int m, class T = int>
class matrix_t {
  array<array<T, m>, n> mat;

public:
  matrix_t() : mat({}) {
  }

  matrix_t(const initializer_list<T> &il) {
    auto ptr = il.begin();
    for (int i = 0; i < n * m; i++) {
      if (ptr != il.end()) {
        mat[i / m][i % m] = *ptr;
        ptr++;
      } else
        mat[i / m][i % m] = {};
    }
  }

  inline array<T, m> &operator [] (const size_t &x) {
    assert(0 <= x && x <= m);
    return mat[x];
  }

  template <int o>
  inline matrix_t<n, o> operator * (const matrix_t<m, o> &other) {
    matrix_t<n, o> ret;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < o; j++)
        for (int k = 0; k < m; k++)
          ret.mat[i][j] = add(ret.mat[i][j], fmul(mat[i][k], other.mat[k][j]));
    return ret;
  }
};
