class dsu_t {
  int n;
  vector<int> cnj;

public:
  dsu_t(int _n) : n(_n), cnj(_n) {
    iota(cnj.begin(), cnj.end(), 0);
  }
  
  inline int root(int x) {
    return (x == cnj[x] ? x : (cnj[x] = root(cnj[x])));
  }
  
  inline bool join(int x, int y) {
    x = root(x);
    y = root(y);
    if(x != y) {
      cnj[x] = y;
      return true;
    }
    return false;
  }
};
