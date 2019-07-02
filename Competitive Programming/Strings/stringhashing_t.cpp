using lint = long long;

/**
 * p is a prime number roughly equal to the number of characters in the input alphabet
 * good p:  {29, 31, 37, 61, 67, 71, 73, 79, 101, 103, 107, 109, 113, 127 251, 257, 263, 269}
 * md is a large prime number
 * good md: {1e9 + 7, 1e9 + 9, 1e9 + 21, 1e9 + 87, (1ll << 61) - 1}
 * pass a function that fixes the alphabet, ex:
 * lowercase alphabet: return c - 'a';
 * substr_hash = (((hash[(0 : r)] - hash[(0 : l - 1)] + mod) % mod) * inverse_prime_pow[i] + mod) % mod
**/
template <lint p, lint md, class T = string>
class stringhashing_t {
  vector<lint> p_pow;
  function<int(int)> f;

  void precompute(int n) {
    int sz = p_pow.size();
    p_pow.resize(max(sz, n + 1));
    for (int i = sz; i <= n; i++)
      p_pow[i] = (p_pow[i - 1] * p) % md;
  }

public:
  stringhashing_t(const function<int(int)> &fix_string_function)
  : f(fix_string_function), p_pow(1, 1) {
  }

  lint get(const T &s, int n) {
    precompute(n);
    lint ret = 0;
    for (int i = 0; i < n; i++) {
      ret = (ret + (f(s[i]) + 1) * p_pow[i]) % md;
    }
    return ret;
  }

  lint get(const T &s) { return get(s, s.size()); }

  vector<lint> get_hashes(const T &s, int n) {
    precompute(n);
    vector<lint> ret(n);
    ret[0] = ((f(s[0]) + 1) * p_pow[0]) % md;
    for (int i = 1; i < n; i++) {
      ret[i] = (ret[i - 1] + (f(s[i]) + 1) * p_pow[i]) % md;
    }
    return ret;
  }
  
  vector<lint> get_hashes(const T &s) { return get_hashes(s, s.size()); }

  vector<int> rabin_karp(const T &s, int n, const T &u, int m) {
    precompute(max(n, m));
    vector<lint> h = get_hashes(s, n);
    lint h_u = get(u, m);
    vector<int> occurences;
    for (int i = 0; i + m - 1 < n; i++) {
      int l = (i > 0 ? h[i - 1] : 0);
      int r = h[i + m - 1];
      lint cur_u = (r + md - l) % md;
      if (cur_u == (h_u * p_pow[i]) % md)
        occurences.push_back(i);
    }
    return occurences;
  }

  vector<int> rabin_karp(const T &s, const T &u) {
    return rabin_karp(s, s.size(), u, u.size());
  }

  vector<vector<int>> group_identical_strings(const vector<T> &vs) {
    int n = vs.size();
    vector<pair<lint, int>> h(n);
    for (int i = 0; i < n; i++) {
      h[i] = make_pair(get(vs[h.size()]), h.size());
    }
    sort(h.begin(), h.end());
    vector<vector<int>> ret;
    for (int i = 0; i < n; i++) {
      if (i == 0 || h[i].first != h[i - 1].first)
        ret.emplace_back();
      ret.back().push_back(h[i].second);
    }
    return ret;
  }
};
