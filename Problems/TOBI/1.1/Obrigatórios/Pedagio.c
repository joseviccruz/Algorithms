#include <stdio.h>

int main() {
	int tam_estrada, distancia_entre_pedagios, custo_km, valor_pedagio;
	int n_pedagios;
	scanf("%d %d", &tam_estrada, &distancia_entre_pedagios);
	scanf("%d %d", &custo_km, &valor_pedagio);
	n_pedagios = tam_estrada/distancia_entre_pedagios;
	printf("%d\n", n_pedagios*valor_pedagio + tam_estrada*custo_km);
	return 0;
}
