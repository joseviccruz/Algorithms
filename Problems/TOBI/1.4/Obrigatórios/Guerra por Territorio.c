#include <stdio.h>

int main() {
	int n_secoes, i, area=0, aux=0;
	scanf("%d", &n_secoes);
	int tamanho[n_secoes];
	for(i=0; i < n_secoes; ++i) {
		scanf("%d", &tamanho[i]);
		area += tamanho[i];
	}
	area /= 2, i=0;
	while (aux != area) {
		aux += tamanho[i];
		++i;
	}
	printf("%d", i);
	return 0;
}
