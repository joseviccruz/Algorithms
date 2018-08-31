#include <stdio.h>

int main() {
	int i, j, n_competidores, pontos_minimo, aprovados=0;
	scanf("%d %d", &n_competidores, &pontos_minimo);
	int notas[n_competidores][2], pontuacao[n_competidores];
	for(i = 0; i < n_competidores; i++) {
		for(j = 0; j < 2; j++) {
		scanf("%d", &notas[i][j]);
		if(j == 0) pontuacao[i] = notas[i][j];
		else pontuacao[i] += notas[i][j];
		}
	}
	for(i = 0; i < n_competidores; i++) {
		if(pontuacao[i] >= pontos_minimo) aprovados++;
	}
	printf("%d", aprovados);
	return 0;
}
