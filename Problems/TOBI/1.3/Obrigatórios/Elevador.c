#include <stdio.h>

int main() {
	int quantidade, capacidade, entraram, sairam, total=0, maior=0;
	scanf("%d %d", &quantidade, &capacidade);
	while(quantidade != 0) {
		scanf("%d %d", &sairam, &entraram);
		total += (entraram - sairam);
		if(total < 0) total = 0;
		if(total > maior) {
		maior = total;
		}
		--quantidade;
	}
	if(maior > capacidade) printf("S");
	else printf("N");
	return 0;
}
