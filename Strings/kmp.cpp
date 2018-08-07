#include <bits/stdc++.h>

using namespace std;

string S, U;

vector<int> generate(const string& s) {
	vector<int> v(s.length() + 1, 0);
	for(int i = 1; i < s.length(); i++) {
		int idx = v[i];
		while(idx && s[i] != s[idx]) idx = v[idx];
		idx += (s[i] == s[idx]);
		v[i + 1] = idx;
	}
	return v;
}

int query(const string& a, const string& b) {
	auto v = generate(b);
	int idx = 0, qnt = 0;
	for(int i = 0; i < a.length(); i++) {
		while(idx && a[i] != b[idx]) idx = v[idx];
		idx += (a[i] == b[idx]);
		if(idx == b.length()) {
			idx = v[idx];
			++qnt;
		}
	}
	return qnt;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	return 0;
}
