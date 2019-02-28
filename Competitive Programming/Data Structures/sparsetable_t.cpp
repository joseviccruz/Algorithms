template <class T, class F = function<T(const T&, const T&)>>
class sparsetable_t {
public:
  int n;
  const F func;
  vector<int> lg;
  vector<vector<T>> table;
  
  sparsetable_t(const vector<T> &base, const F &func) : func(func) {
    n = base.size();
    assert(n > 0);
    lg.resize(n + 1);
    for (int i = 2; i <= n; i++)
      lg[i] = lg[i >> 1] + 1;
    int max_log = lg[n] + 1;
    table.push_back(base);
    table.resize(max_log);
    for (int j = 1; j < max_log; j++) {
      table[j].resize(n - (1 << j) + 1);
      for (int i = 0; i < n - (1 << j) + 1; i++)
        table[j][i] = func(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
    }
  }
  
  T get(int x, int y) {
    assert(0 <= x && x <= y && y <= n - 1);
    int pos = lg[y - x + 1];
    return func(table[pos][x], table[pos][y - (1 << pos) + 1]);
  }
};
