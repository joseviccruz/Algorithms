using lint = long long;

template <class T>
T gcd(T a, T b, T &x, T &y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  T p = b / a;
  T g = gcd(b - p * a, a, y, x);
  x -= p * y;
  return g;
}

// p is a prime number roughly equal to the number of characters in the input alphabet
// md is a large prime number
// pass a function that fixes the alphabet, ex:
// lowercase alphabet: return c - 'a';

template <lint p, lint md, class T = string>
class hashing_t {
  int sz;
  vector<lint> p_pow;
  vector<lint> p_inv;
  function<int(int)> f;

  void precompute(int n) {
    if (sz > n)
      return;
    n++;
    p_pow.resize(n);
    p_inv.resize(n);
    lint x, y;
    for (int i = sz; i < n; i++) {
      p_pow[i] = (p_pow[i - 1] * p) % md;
      assert(gcd(p_pow[i], md, x, y) == 1);
      p_inv[i] = (x % md + md) % md;
    }
    sz = n;
  }

public:
  hashing_t(const function<int(int)> &fix_string_function)
  : f(fix_string_function), sz(1), p_pow(1, 1), p_inv(1, 1) {
  }

  lint get(const T &s, int n) {
    precompute(n);
    lint ret = 0;
    for (int i = 0; i < n; i++) {
      ret = (ret + (f(s[i]) + 1) * p_pow[i]) % md;
    }
    return ret;
  }

  lint get(const T &s) {
    return get(s, s.size());
  }

  vector<lint> get_hashes(const T &s, int n) {
    precompute(n);
    vector<lint> ret(n);
    ret[0] = ((f(s[0]) + 1) * p_pow[0]) % md;
    for (int i = 1; i < n; i++) {
      ret[i] = (ret[i - 1] + (f(s[i]) + 1) * p_pow[i]) % md;
    }
    return ret;
  }
  
  vector<lint> get_hashes(const T &s) {
    return get_hashes(s, s.size());
  }

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

  lint substr_hash(const vector<lint> &h, int i, int j) {
    precompute(j);
    int l = (i > 0 ? h[i - 1] : 0), r = h[j];
    return (((r - l + md) % md) * p_inv[i] + md) % md;
  }
};
