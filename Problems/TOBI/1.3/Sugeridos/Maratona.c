#include <stdio.h>

int main() {
	int postosDeAgua, distanciaIntermediaria, i, j=0;
	scanf("%d %d", &postosDeAgua, &distanciaIntermediaria);
	int posto[postosDeAgua];
	for(i = 0; i < postosDeAgua; i++) scanf("%d", &posto[i]);
	if(42195 - posto[postosDeAgua-1] > distanciaIntermediaria) {
		j = 1;
		printf("N");
	} else {
		for(i = 0; i < (postosDeAgua-1); i++) {
			if(posto[i+1] - posto[i] > distanciaIntermediaria) {
				printf("N");
				j = 1;
				break;
			}
		}
	}
	if(j != 1) {
		printf("S");
	}
	return 0;
}
