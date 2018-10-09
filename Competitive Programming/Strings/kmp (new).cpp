#include <bits/stdc++.h>

using namespace std;

vector<int> get_border(const string &s) {
	vector<int> b(s.size() + 1);
	int j = -1;
	b[0] = j;
	for(int i = 0; i < (int) s.size(); i++) {
		while(j >= 0 && s[i] != s[j]) {
			j = b[j];
		}
		b[i + 1] = ++j;
	}
	return b;
}

int kmp(const string &s, const string &p) {
	auto b = get_border(p);
	int ans = 0;
	int j = 0;
	for(int i = 0; i < (int) s.size(); i++) {
		while(j >= 0 && s[i] != p[j]) {
			j = b[j];
		}
		++j;
		if(j == p.size()) {
			++ans;
			j = b[j];
		}
	}
	return ans;
}

const int maxn = 1e4;
const int sigma = 26;

int aut[maxn][sigma];

inline int id(const char &c) {
	return c - 'a';
}

// KMP Automaton
// Keeps, for each size, the value of the new match if a new char is added.
void pre(const string &s) {
	for(int i = 0; i < 26; i++) {
		aut[0][i] = 0;
	}
	int brd = 0;
	aut[0][id(s[0])] = 1;
	for(int i = 1; i <= (int) s.size(); i++) {
		for(int j = 0; j < 26; j++) {
			aut[i][j] = aut[brd][j];
		}
		if(i < (int) s.size()) {
			aut[i][id(s[i])] = i + 1;
			brd = aut[brd][id(s[i])];
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	string s, p;
	cin >> s >> p;
	cout << kmp(s, p) << '\n';
	return 0;
}
