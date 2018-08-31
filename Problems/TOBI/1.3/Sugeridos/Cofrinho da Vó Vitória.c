#include <stdio.h>
#include <stdlib.h>

int main() {
	int n_depositos, j, z, jTotal, zTotal, i, a=1;
	while(scanf("%d", &n_depositos) && n_depositos != 0) {
		jTotal = 0, zTotal = 0;
		printf("Teste %d\n", a);
		for(i=0; i < n_depositos; i++) {
			scanf("%d %d", &j, &z);
			jTotal += j, zTotal += z;
			if(jTotal < zTotal) {
				printf("%d\n", jTotal - zTotal);
			} else {
				printf("%d\n", abs(jTotal - zTotal));
			}
		}
		a++;
		printf("\n");
	}
	return 0;
}
