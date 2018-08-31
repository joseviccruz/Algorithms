#include <stdio.h>
#include <limits.h>
int main() {
	int carros, voltas, tempo[100], i, j, primeiro = INT_MAX, segundo = INT_MAX, terceiro = INT_MAX, aux, posicao[3];
	scanf("%d %d", &carros, &voltas);
	for(i = 0; i < carros; i++) {
		aux = 0;
		for(j = 0; j < voltas; j++) {
			scanf("%d", &tempo[j]);
			aux += tempo[j];
		}
		if(aux < primeiro) {
			terceiro = segundo;
			posicao[2] = posicao[1];
			segundo = primeiro;
			posicao[1] = posicao[0];
			primeiro = aux;
			posicao[0] = i+1;
		} else {
			if(aux < segundo) {
				terceiro = segundo;
				posicao[2] = posicao[1];
				segundo = aux;
				posicao[1] = i+1;
			} else {
				if(aux < terceiro) {
					terceiro = aux;
					posicao[2] = i+1;
				}
			}
		}
	}
	printf("%d\n%d\n%d", posicao[0], posicao[1], posicao[2]);
	return 0;
}
