template <class T, class cmp_t = greater<T>>
class maxqueue_t {
  cmp_t cmp;
  stack<pair<T, T>> stl, str;

  void transfer() {
    while (!stl.empty()) {
      if (str.empty())
        str.emplace(stl.top().first, stl.top().first);
      else {
        T aux = cmp(stl.top().first, str.top().second) ? stl.top().first : str.top().second;
        str.emplace(stl.top().first, aux);
      }
      stl.pop();
    }
  }

public:  
  maxqueue_t() {
    while (!stl.empty())
      stl.pop();
    while (!str.empty())
      str.pop();
  }

  void push(T value) {
    if (stl.empty())
      stl.emplace(value, value);
    else {
      T aux = cmp(value, stl.top().second) ? value : stl.top().second;
      stl.emplace(value, aux);
    }
  }

  void pop() {
    if (str.empty())
      transfer();
    str.pop();
  }

  T front() {
    assert(!stl.empty() || !str.empty());
    if (!str.empty())
      return str.top().first;
    transfer();
    return str.top().first;
  }

  T get() {
    assert(!stl.empty() || !str.empty());
    if (stl.empty())
      return str.top().second;
    return cmp(stl.top().second, str.top().second) ? stl.top().second : str.top().second;
  }
};
