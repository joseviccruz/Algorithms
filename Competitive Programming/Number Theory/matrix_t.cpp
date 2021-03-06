template <int n, int m, class T = int>
class matrix_t {
  array<array<T, m>, n> mat;

public:
  inline array<T, m> &operator [] (int x) { return mat[x]; }

  matrix_t() : mat({}) {
  }

  matrix_t(const initializer_list<T> &il) : matrix_t() {
    auto ptr = il.begin();
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (ptr != il.end())
          mat[i][j] = *ptr++;
  }

  template <int o>
  inline matrix_t<n, o> operator * (matrix_t<m, o> other) {
    matrix_t<n, o> ret;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < o; j++)
        for (int k = 0; k < m; k++)
          ret[i][j] = add(ret[i][j], fmul(mat[i][k], other[k][j]));
    return ret;
  }
};
