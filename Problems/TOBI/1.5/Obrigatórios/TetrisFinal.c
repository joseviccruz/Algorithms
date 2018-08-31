#include <stdio.h>

int bubbleSort(int vetor[], int tamanho);

int main() {
	int jogadores, jog, i, j, a=1, b=1, teste, maior, menor;
	scanf("%d", &jogadores);
	while(jogadores != 0) {
		char nome[jogadores][16];
		int pontos[jogadores][12], pontuacao[jogadores], pontuacao_ordem[jogadores];
		for(i = 0; i < jogadores; ++i) {
			pontuacao[i] = 0;
			scanf(" %s", nome[i]);
			for(j = 0; j < 12; ++j) {
				scanf("%d", &pontos[i][j]);
				if(j == 0) maior = pontos[i][j], menor = pontos[i][j];
				else {
					if(pontos[i][j] > maior) maior = pontos[i][j];
					if(pontos[i][j] < menor) menor = pontos[i][j];
				}
				pontuacao[i] += pontos[i][j];
			}
			pontuacao[i] = pontuacao[i] - maior - menor;
			pontuacao_ordem[i] = pontuacao[i];
		}
		bubbleSort(pontuacao_ordem, jogadores);
		printf("Teste %d\n", a);
		for(i = 0; i < jogadores; ++i) {
				for(j = 0; j < jogadores; ++j) {
					if (pontuacao[j] == pontuacao_ordem[i]) {
						printf("%d %d %s\n", b, pontuacao[j], nome[j]);
						/*
							Teste 1
							1 5200 Joaozinho
							2 2518 Zezinho
							3 2020 Luizinho
							4 150 Carlinhos

						*/
					}
				}
			++b;
		}
		printf("\n");
		b=1, ++a;
		scanf("%d", &jogadores);
	}
}

int bubbleSort(int vetor[], int tamanho) {
	int i, j, troca;
	for(i = 0; i < tamanho; ++i) {
		for(j = i+1; j < tamanho; ++j) {
			if(vetor[i] < vetor[j]) {
				troca = vetor[i];
				vetor[i] = vetor[j];
				vetor[j] = troca;
			}
		}
	}
}
