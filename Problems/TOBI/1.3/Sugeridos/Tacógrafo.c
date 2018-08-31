#include <stdio.h>

int main() {
	int intervalos, distancia=0, i;
	scanf("%d", &intervalos);
	int tempo_e_velocidade[intervalos][2];
	for(i = 0; i < intervalos; i++) {
		scanf("%d %d", &tempo_e_velocidade[i][0], &tempo_e_velocidade[i][1]);
		distancia += tempo_e_velocidade[i][0]*tempo_e_velocidade[i][1];
	}
	printf("%d", distancia);
	return 0;
}
