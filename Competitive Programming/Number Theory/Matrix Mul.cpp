template <class T>
using Matrix = vector<vector<T>>;

template <class T>
Matrix<T> operator * (const Matrix<T> &lhs, const Matrix<T> &rhs) {
	int rows = lhs.size();
	int cowls = rhs.front().size();
	int common = rhs.size();
	Matrix<T> result(rows, vector<T>(cowls));
	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cowls; j++)
			for(int k = 0; k < common; k++)
				result[i][j] += lhs[i][k] * rhs[k][j];
	return result;
}
