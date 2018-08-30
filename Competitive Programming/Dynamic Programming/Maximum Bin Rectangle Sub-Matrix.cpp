#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e3 + 100;
int m, n, matrix[maxn][maxn];

int maxHist(int row[]) {
	stack<int> st;
	int i = 0, ans = 0, top, aux;
	while(i < n) {
		if(st.empty() || row[st.top()] <= row[i]) {
			st.push(i++);
		} else {
			top = row[st.top()];
			st.pop();
			aux = top*i;
			if(!st.empty()) {
				aux = top*(i - st.top() - 1);
			}
			ans = max(ans, aux);
		}
	}
	while(!st.empty()) {
		top = row[st.top()];
		st.pop();
		aux = top*i;
		if(!st.empty()) {
			aux = top*(i - st.top() - 1);
		}
		ans = max(ans, aux);
	}
	return ans;
}

int maxRect() {
	int ans = maxHist(matrix[0]);
	for(int i = 1; i < m; i++) {
		for(int j = 0; j < n; j++) {
			if(matrix[i][j]) matrix[i][j] += matrix[i-1][j];
		}
		ans = max(ans, maxHist(matrix[i]));
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> m >> n;
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			cin >> matrix[i][j];
		}
	}	
	cout << maxRect() << '\n';
	return 0;
}
