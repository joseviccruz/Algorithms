#include <bits/stdc++.h>

using namespace std;

using lint = long long;

inline lint fmul(lint a, lint b, const lint mod = 1e9 + 7) {
	lint ans = 0;
	for(; b; b >>= 1) {
		if(b & 1) {
			ans = (ans + a) % mod;
		}
		a = (a + a) % mod;
	}
	return ans;
}

inline lint fexp(lint n, lint e, const lint mod = 1e9 + 7) {
	lint ans = 1;
	for(; e; e >>= 1) {
		if(e & 1) {
			ans = fmul(ans, n);
		}
		n = fmul(n, n);
	}
	return ans;
}

const int mod = 1e9 + 7;
const int maxn = 1e7 + 1;

int prime[maxn], freq[maxn], keep[maxn], have[maxn];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	iota(prime, prime + maxn, 0);
	for(int i = 2; i < maxn; i++) {
		keep[i] = 1e9;
		if(prime[i] != i) continue;
		for(int j = 2; i * j < maxn; j++) {
			prime[i * j] = min(prime[i * j], prime[i]);
		}
	}
	for(int i = 0; i < n; i++) {
		int m;
		cin >> m;
		vector<int> all;
		for(int j = 0; j < m; j++) {
			int x;
			cin >> x;
			for(; x > 1; x /= prime[x]) {
				freq[prime[x]]++;
				all.push_back(prime[x]);
			}
		}
		sort(all.begin(), all.end());
		all.resize(unique(all.begin(), all.end()) - all.begin());
		for(int &x : all) {
			keep[x] = min(keep[x], freq[x]);
			freq[x] = 0;
			have[x]++;
		}
	}
	lint ans = 1;
	for(int i = 0; i < maxn; i++) {
		if(have[i] < n) continue;
		ans = ans * fexp(i, keep[i]) % mod;
	}
	return 0 * printf("%lld\n", ans);
}
