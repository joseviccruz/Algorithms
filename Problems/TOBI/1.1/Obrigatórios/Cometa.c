#include <stdio.h>

int main() {
	int inserido, ano_final;
	scanf("%d", &inserido);
	if((inserido == 104) || ((inserido - 104)%76 == 58)) {
		ano_final = inserido + 76;
		printf("%d\n", ano_final);
	} else {
		for(ano_final = inserido; ((ano_final - 104) == 58) || ((ano_final - 104)%76 != 58); ano_final++);
		printf("%d\n", ano_final);
	}
	return 0;
}
