#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
	int n_pedras, min = INT_MAX, i, soma_escada=0, soma_errada=0 ,deslocadas=0;
	scanf("%d", &n_pedras);
	int pedras[n_pedras], escada[n_pedras];
	for(i = 0; i < n_pedras; i++) {
		scanf("%d", &pedras[i]);
		if(pedras[i] < min) min = pedras[i];
		if(i == 0) escada[i] = 0;
		else escada[i] = i;
		soma_escada += i;
		//printf("escada %d\n", escada[i]);
	}
	//printf("%d\n", soma_escada);
	for(i = 0; i < n_pedras; i++) {
		pedras[i] -= min;
		soma_errada += pedras[i];
		//printf("pedras %d\n", pedras[i]);
		//printf("diferenca %d\n", abs(pedras[i] - escada[i]));
		deslocadas += abs(pedras[i] - escada[i]);
	}
	if(soma_escada == soma_errada) printf("%d\n", deslocadas/2);
	else printf("-1\n");
	return 0;
}
