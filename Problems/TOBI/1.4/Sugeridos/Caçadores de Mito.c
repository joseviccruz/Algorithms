#include <stdio.h>

int main() {
	int n_raios, coord[500000][2], i, comp[500501], qnt=0;
	for(i = 0; i < 500501; i++) comp[i] = 0;
	scanf("%d", &n_raios);
	for(i = 0; i < n_raios; i++) {
		scanf("%d %d", &coord[i][0], &coord[i][1]);
		if(comp[coord[i][0]*1000 + coord[i][1]] == 1) {
			qnt=1;
		}
		comp[coord[i][0]*1000 + coord[i][1]] = 1;
	}
	printf("%d", qnt);
	return 0;
}
