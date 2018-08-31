#include <stdio.h>

int main() {
	int abertura, numero_de_estrelas, i, e_percebidas=0;
	scanf("%d %d", &abertura, &numero_de_estrelas);
	int fotons[numero_de_estrelas];
	for(i = 0; i < numero_de_estrelas; i++) {
		scanf("%d", &fotons[i]);
		if(abertura*fotons[i] >= 40000000) e_percebidas++;
	}
	printf("%d", e_percebidas);
	return 0;
}
