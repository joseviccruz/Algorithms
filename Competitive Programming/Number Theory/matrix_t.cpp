template <class T>
using matrix_t = vector<vector<T>>;

template <class T>
matrix_t<T> operator * (const matrix_t<T> &lhs, const matrix_t<T> &rhs) {
  assert(lhs.front().size() == rhs.size());
  int rows = lhs.size();
  int cowls = rhs.front().size();
  int common = rhs.size();
  matrix_t<T> result(rows, vector<T>(cowls));
  for(int i = 0; i < rows; i++)
    for(int j = 0; j < cowls; j++)
      for(int k = 0; k < common; k++)
        result[i][j] += lhs[i][k] * rhs[k][j];
  return result;
}
