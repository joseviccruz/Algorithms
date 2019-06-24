template <class T>
class reverse_range {
  T &x;
public:
  reverse_range(T &x) : x(x) { }
  constexpr auto begin() const -> decltype(this->x.rbegin()) { return x.rbegin(); }
  constexpr auto end() const -> decltype(this->x.rend()) { return x.rend(); }
};
 
template <class T>
reverse_range<T> reverse_iterate(T &x) { return reverse_range<T>(x); }

/* Example:
  int n;
  cin >> n;
  vector<int> v(n);
  for (int &x : v) {
    cin >> x;
  }
  for (int &x : reverse_iterate(v)) {
    cout << x << " \n"[&x == &v.front()];
  }
*/
