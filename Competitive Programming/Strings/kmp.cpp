template <class T>
vector<int> kmp_table(int n, const T &s) {
  vector<int> p(n);
  for (int i = 1, j = 0; i < n; i++) {
    while (j > 0 && s[i] != s[j])
      j = p[j - 1];
    j += s[i] == s[j];
    p[i] = j;
  }
  return p;
}

template <class T>
vector<int> kmp_table(const T &s) {
  return kmp_table(s.size(), s);
}

template <class T>
vector<int> kmp_search(int n, const T &s, int m, const T &u, const vector<int> &p) {
  assert(m >= 1 && m == p.size());
  vector<int> ans;
  for (int i = 0, j = 0; i < n; i++) {
    while (j > 0 && (j == m || s[i] != u[j]))
      j = p[j - 1];
    j += s[i] == u[j];
    if (j == m)
      ans.push_back(i - j + 1);
  }
  return ans;
}

template <class T>
vector<int> kmp_search(const T &s, const T &u) {
  return kmp_search(s.size(), s, u.size(), u, kmp_table(u));
}
