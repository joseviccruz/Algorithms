vector<string> split(const string &str, const string &delim) {
  vector<string> ret(1);
  for (int i = 0; i < (int) str.size(); i++) {
    if (str.substr(i, delim.size()) == delim) {
      if (!ret.back().empty())
        ret.push_back("");
      i += (int) delim.size() - 1;
      continue;
    }
    ret.back() += str[i];
  }
  if (ret.back().empty())
    ret.pop_back();
  return ret;
}

vector<string> split(const string &str, const char &ch) {
  return split(str, string(1, ch));
}
