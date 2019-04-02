template <int N, int M, class T = int>
class matrix_t {
  array<array<T, M>, N> mat;

public:
  static constexpr int n = N;
  static constexpr int m = M;

  inline array<T, m> &operator [] (const size_t &x) {
    return mat[x];
  }

  matrix_t() : mat({}) {
  }

  matrix_t(const initializer_list<T> &il) {
    int i = 0;
    auto ptr = il.begin();
    while (ptr != il.end() && i < n * m) {
      mat[i / m][i % m] = *ptr;
      ptr++;
      i++;
    }
    while (i < n * m) {
      mat[i / m][i % m] = {};
      i++;
    }
  }

  inline matrix_t operator + (const matrix_t &other) {
    matrix_t ret;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        ret.mat[i][j] = add(mat[i][j], other.mat[i][j]);
    return ret;
  }

  inline matrix_t operator - (const matrix_t &other) {
    matrix_t ret;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        ret.mat[i][j] = sub(mat[i][j], other.mat[i][j]);
    return ret;
  }

  inline matrix_t operator * (const T &t) {
    matrix_t ret;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        ret.mat[i][j] = fmul(mat[i][j], t);
    return ret;
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
