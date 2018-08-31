#include <stdio.h>
#include <string.h>

int bubble(int tamanho, int vetor[tamanho][2], char nome[][16]);

int main() {
	int jogadores, jog, i, j, teste, maior, menor;
	scanf("%d", &jogadores);
	while(jogadores != 0) {
		char nome[jogadores][16];
		int pontos[jogadores][12], pontuacao[jogadores][2];
		for(i = 0; i < jogadores; i++) {
			pontuacao[i][1] = 0;
			scanf(" %s", nome[i]);
			for(j = 0; j < 12; j++) {
				scanf("%d", &pontos[i][j]);
				if(j == 0) maior = pontos[i][j], menor = pontos[i][j];
				else {
					if(pontos[i][j] > maior) maior = pontos[i][j];
					if(pontos[i][j] < menor) menor = pontos[i][j];
				}
				pontuacao[i][1] += pontos[i][j];
			}
			pontuacao[i][0] = i;
			pontuacao[i][1] = pontuacao[i][1] - maior - menor;
		}
		bubble(jogadores, pontuacao, nome);
		for(i = 0; i < jogadores; i++) {
			printf("%d %s\n", pontuacao[i][1], nome[pontuacao[i][0]]);
			/*
				Teste 1
				1 5200 Joaozinho
				2 2518 Zezinho
				3 2020 Luizinho
				4 150 Carlinhos

			*/
		}
		scanf("%d", &jogadores);
	}

}

int bubble(int tamanho, int vetor[tamanho][2], char nome[][16]) {
	int i, aux, troca = 1;
	while(troca){
		troca = 0;
		for(i = 0; i < tamanho-1; i++) {
			if(vetor[i][1] < vetor[i + 1][1] || (vetor[i][1] == vetor[i + 1][1] && strcmp(nome[vetor[i][0]], nome[vetor[i + 1][0]]) > 0)) {
				aux = vetor[i][0];
				vetor[i][0] = vetor[i + 1][0];
				vetor[i + 1][0] = aux;
				aux = vetor[i][1];
				vetor[i][1] = vetor[i + 1][1];
				vetor[i + 1][1] = aux;
				troca = 1;
			}
		}
	}
}

/*
< 0 1 < 2
> 0 1 > 2
== 0 1 == 2
*/
