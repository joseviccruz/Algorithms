#include <bits/stdc++.h>

using namespace std;

const int maxn = 301;

int sz;
int primes[maxn];
bool memo[maxn][1010][20];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	{
		bool aux[maxn];
		memset(aux, true, sizeof aux);
		for(int i = 2; i < maxn; i++) {
			if(!aux[i]) continue;
			primes[++sz] = i;
			if(i > 2) primes[++sz] = i;
			for(int j = 2; i * j < maxn; j++) {
				aux[i * j] = false;
			}
		}
		sort(primes + 1, primes + sz + 1, [](const int &a, const int &b) { return to_string(a) > to_string(b); });
	}
	memo[0][0][0] = true;
	for(int i = 1; i <= sz; i++) {
		for(int j = 0; j < 1010; j++) {
			for(int k = 0; k < 15; k++) {
				memo[i][j][k] |= memo[i - 1][j][k];
				if(j < primes[i] || !k) continue;
				memo[i][j][k] |= memo[i - 1][j - primes[i]][k - 1];
			}
		}
	}
	for(int tc = 1, n, t; cin >> n >> t && (n + t); tc++) {
		cout << "CASE " << tc << ":\n";
		if(!memo[sz][n][t]) {
			cout << "No Solution.\n";
		} else {
			for(int x = sz, y = n, z = t; y && x && z; x--) {
				if(memo[x][y][z] && y - primes[x] >= 0 && memo[x - 1][y - primes[x]][z - 1]) {
					y -= primes[x];
					cout << primes[x] << "+\n"[!y];
					z--;
				}
			}
			
		}
	}
	return 0;
}
