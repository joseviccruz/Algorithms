// A escola de Joãozinho...
#include <stdio.h>

int main() {
	int competidores, voltas, percurso[100][100], i, j, soma, aux=0, ganhador;
	scanf("%d %d", &competidores, &voltas);
	for(i = 0; i < competidores; i++) {
		for(j = 0; j < voltas; j++) {
			scanf("%d", &percurso[i][j]);
			aux += percurso[i][j];
		}
		if(i == 0) {
			soma = aux;
			ganhador = i+1;
		} else if(aux < soma) {
			soma = aux;
			ganhador = i+1;
		}
		aux = 0;
	}
	printf("%d", ganhador);
	return 0;
}
