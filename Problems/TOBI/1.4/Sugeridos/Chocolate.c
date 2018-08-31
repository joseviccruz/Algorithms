#include <stdio.h>

int main() {
	int n_divisoes, pedacos[1000], i, resposta=0;
	scanf("%d", &n_divisoes);
	for(i = 0; i < n_divisoes; i++) {
		scanf("%d", &pedacos[i]);
		resposta += pedacos[i]-1;
	}
	printf("%d", resposta);
	return 0;
}
