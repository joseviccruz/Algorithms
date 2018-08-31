#include <stdio.h>

int main() {
	int partidas, i, a=1;
	char jogador1[11], jogador2[11];
	while(scanf("%d", &partidas) && partidas != 0) {
		int jogadas[partidas][2], result[partidas];
		scanf(" %s %s", jogador1, jogador2);
		for(i = 0; i < partidas; i++) {
			scanf("%d %d", &jogadas[i][0], &jogadas[i][1]);
			result[i] = jogadas[i][0] + jogadas[i][1];
		}
		printf("Teste %d\n", a);
		for(i = 0; i < partidas; i++) {
			if(result[i]%2 == 0) printf("%s\n", jogador1);
			else printf("%s\n", jogador2);
		}
		putchar('\n');
		a++;
	}
	return 0;
}
