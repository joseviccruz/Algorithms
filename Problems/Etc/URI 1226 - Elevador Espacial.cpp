#include <bits/stdc++.h>

using namespace std;

int len;
long long n, vs[20], memo[20][2][2];

long long solve(int idx, bool last, bool ok) {
	if(idx == len) return 1;
	long long &on = memo[idx][last][ok];
	if(~on) return on;
	on = 0;
	for(register int i = 0; i <= (ok ? 9 : vs[idx]); i++) {
		if(last && i == 3) continue;
		if(i == 4) continue;
		on += solve(idx + 1, i == 1, ok | i < vs[idx]);
	}
	return on;
}

inline bool can(const long long unsigned &m) {
	len = 0;
	for(register long long unsigned aux = m; aux; aux /= 10) vs[len++] = aux % 10;
	reverse(vs, vs + len);
	memset(memo, -1, sizeof memo);
	long long x = solve(0, 0, false) - 1;
	return n > x;
}

int main() {
	while(~scanf("%lld", &n)) {
		long long unsigned l = 1ll, r = 1e19 + 1ll;
		while(r - l > 1) {
			long long unsigned m = l + (r - l) / 2;
			if(can(m)) {
				l = m;
			} else {
				r = m;
			}
		}
		while(can(l)) l++;
		printf("%llu\n", l);
	}
	return 0;
}
