#include <stdio.h>

int main() {
	int numero1, distancia1, velocidade1, numero2, distancia2, velocidade2;
	scanf("%d %d %d %d %d %d", &numero1, &distancia1, &velocidade1, &numero2, &distancia2, &velocidade2);
	if((double)distancia1/velocidade1 < (double)distancia2/velocidade2) printf("%d", numero1);
	else printf("%d", numero2);
	return 0;
}
