#include <stdio.h>

int main() {
	int n, i, j, k;
	scanf("%d", &n);
	int mapa1[n][n], mapa2[n][n], chuva[n][n];
	for(i=0; i < n; i++) {
		for(j=0; j < n; j++) {
		scanf("%d", &mapa1[i][j]);
		}
	}
	for(i=0; i < n; i++) {
		for(j=0; j < n; j++) {
		scanf("%d", &mapa2[i][j]);
		}
	}
	for(i=0; i < n; i++) {
		for(j=0; j < n; j++) {
		chuva[i][j] = mapa1[i][j] + mapa2[i][j];
		}
	}
	for(i=0; i < n; i++) {
		for(j=0; j < n; j++) {
		if(j+1 == n) printf("%d", chuva[i][j]);
		else printf("%d ", chuva[i][j]);
		}
		printf("\n");
	}
	return 0;
}

/*
	Bob trabalha no OBM (Órgão Brasileiro de Metereologia), que é a organização responsável pela medição dos índices pluviométricos (quantidade de chuva acumulada) em todo o país. Eles são muito eficientes no que fazem, mas estão com um problema: eles não sabem como proceder para calcular a quantidade acumulada de chuva que caiu em cada região em dois períodos consecutivos, muito embora eles saibam os dados de cada período separadamente.

	Como a chefia do Órgão estava muito ocupada, acabou ficando a cargo de Bob, o estagiário, a tarefa de implementar um programa que some, para cada região, a quantidade de chuva acumulada em dois períodos consecutivos.

	O mapa que o OBM usa é dividido em N x N regiões, sendo que para cada região, a cada período, é determinado um número inteiro indicando a quantidade de chuva acumulada. A quantidade de chuva acumulada total em cada região em dois períodos consecutivos é a soma das quantidades de chuva em cada um dos períodos. Mas como Bob é só um estagiário e não está acostumado a fazer nada mais do que tirar cópias de documentos, ele pediu sua ajuda para implementar o programa que calcula a quantidade de chuva acumulada total nos dois períodos para cada uma das regiões, dadas as quantidades de chuva acumulada em cada período para cada região.

	Entrada
	A primeira linha da entrada contém um inteiro N indicando a dimensão dos dois mapas que devem ser lidos. Nas próximas 2xN linhas são dados os dois mapas, cada mapa indicando a quantidade de chuva acumulada nas regiões em um período. Cada mapa é descrito em N linhas consecutivas, cada linha contendo N inteiros, sendo que cada inteiro indica a quantidade de chuva acumulada, no período, em uma região.

	Saída
	A saída deverá conter N linhas, com N inteiros em cada linha, indicando a quantidade de chuva acumulada total em cada uma das regiões nos dois períodos considerados.
Restrições

    1 ≤ N ≤ 100
    0 ≤ quantidade de chuva acumulada em cada região de cada mapa ≤ 100
*/
