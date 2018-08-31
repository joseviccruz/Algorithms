#include <stdio.h>

int main() {
	int diametro, altura, largura, profundidade;
	scanf("%d %d %d %d", &diametro, &altura, &largura, &profundidade);
	if(diametro <= altura && diametro <= largura && diametro <= profundidade) printf("S");
	else printf("N");
	return 0;
}
