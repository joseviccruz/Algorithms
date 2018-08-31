/*
A primeira linha da entrada contém um número inteiro N que indica o número de trilhas.
Cada uma das N linhas seguintes contém a descrição de uma trilha (1 <= N <= 100).
As trilhas são identificadas por números de 1 a N.
A ordem em que as trilhas aparecem na entrada determina os seus identificadores
(a primeira trilha é a de número 1, a segunda a de número 2, a última a de número N).
A descrição de uma trilha inicia com um número inteiro M que indica a quantidade de pontos de medição da trilha
(2 <= M <= 1000), seguido de M números inteiros Hi representando a altura dos pontos da trilha
(medidos a intervalos regulares e iguais para todas as linhas).
Paulo pode percorrer a trilha em qualquer sentido
(ou seja, partindo do ponto de altitude H1 em direção ao ponto de altitude HM,
ou partindo do ponto de altitude HM em direção ao ponto de altitude H1).
*/
#include <stdio.h>

int main() {
	int qnt_trilhas, i, j, descricao, desnivel, melhor_desn, trilha;
	scanf("%d", &qnt_trilhas);
	for(i = 0; i < qnt_trilhas; i++) {
		scanf("%d", &descricao);
		int caminho[descricao];
		for(j = 0; j < descricao; j++) scanf("%d", &caminho[j]);
		for(j = 0; j < descricao-1; j++) {
			desnivel += caminho[j+1] - caminho[j];
		}
		if(i == 0) {
			melhor_desn = desnivel/descricao;
			trilha = 1;
		}
		if(desnivel/descricao < melhor_desn) {
			melhor_desn = desnivel/descricao;
			trilha = i+1;
		}
	}
	printf("%d", trilha);
	return 0;
}
