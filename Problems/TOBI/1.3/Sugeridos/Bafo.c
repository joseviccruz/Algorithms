#include <stdio.h>

int main() {
	int rodadas, aldo, beto, viradas_a, viradas_b, a=1, i;
	while(scanf("%d", &rodadas) && rodadas != 0) {
		viradas_a=0, viradas_b=0;
		for(i = 0; i < rodadas; i++) {
			scanf("%d %d", &aldo, &beto);
			viradas_a += aldo, viradas_b += beto;
		}
		printf("Teste %d\n", a);
		if(viradas_a > viradas_b) printf("Aldo\n\n");
		else printf("Beto\n\n");
		a++;
	}
	return 0;
}
