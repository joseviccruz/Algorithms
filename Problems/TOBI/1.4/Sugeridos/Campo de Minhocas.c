#include <stdio.h>

int main() {
	int mminhocas[100][100], linhas, colunas, valor_def=0, aux=0, i, j;
	scanf("%d %d", &linhas, &colunas);
	for(i = 0; i < linhas; i++) {
		for(j = 0; j < colunas; j++) {
			scanf("%d", &mminhocas[i][j]);
		}
	}
	for(i = 0; i < linhas; i++) {
		for(j = 0; j < colunas; j++) {
			aux += mminhocas[i][j];
		}
		if(valor_def < aux) valor_def = aux;
		aux=0;
	}
	for(j = 0; j < colunas; j++) {
		for(i = 0; i < linhas; i++) {
			aux += mminhocas[i][j];
		}
		if(valor_def < aux) valor_def = aux;
		aux=0;
	}
	printf("%d", valor_def);
	return 0;
}
