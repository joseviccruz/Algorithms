#include <stdio.h>

int main() {
	int i, j, tamanho, soma=0, maior;
	char tabuleiro[100][101];
	scanf("%d", &tamanho);
	for(i=0; i < tamanho; i++) {
		scanf("%s", tabuleiro[i]);
	}
	for(i=0; i < tamanho; i++) {
		if(i%2 == 0) {
			for(j=0; j < tamanho; j++) {
				if(tabuleiro[i][j] == 'o') soma++;
				if(soma > maior) maior = soma;
				if(tabuleiro[i][j] == 'A') soma = 0;
			}
		} else {
			for(j=tamanho; j >= 0; j--) {
				if(tabuleiro[i][j] == 'o') soma++;
				if(soma > maior) maior = soma;
				if(tabuleiro[i][j] == 'A') soma = 0;
			}
		}
	}
	printf("%d", maior);
	return 0;
}
