struct minQueue {
  stack<pair<int, int>> pushs, pops;
  
  void transfer() {
    while (!pushs.empty()) {
      if (pops.empty()) {
        pops.emplace(pushs.top().first, pushs.top().first);
      } else {
        pops.emplace(pushs.top().first, min(pushs.top().first, pops.top().second));
      }
      pushs.pop();
    }
  }

  void push(int v) {
    if (pushs.empty()) {
      pushs.emplace(v, v);
    } else {
      pushs.emplace(v, min(v, pushs.top().second));
    }
  }

  void pop() {
    if (pops.empty()) {
      transfer();
    }
    pops.pop();
  }

  int front() {
    if (!pops.empty()) {
      return pops.top().first;
    } else if (!pushs.empty()) {
      transfer();
      return pops.top().first;
    } else {
      assert(false);
    }
  }

  int get_min() {
    int ans = INT_MAX;
    if (!pops.empty()) {
      ans = min(ans, pops.top().second);
    }
    if (!pushs.empty()) {
      ans = min(ans, pushs.top().second);
    }
    if (pops.empty() && pushs.empty()) {
      assert(false);
    }
    return ans;
  }
};
