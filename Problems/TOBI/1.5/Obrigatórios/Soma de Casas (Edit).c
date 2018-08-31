#include <stdio.h>

int main() {
	int n_casas, casa[100000], valor, aux, i, j;
	scanf("%d", &n_casas);
	for(i = 0; i < n_casas; i++) {
		scanf("%d", &casa[i]);
		
	}
	scanf("%d", &valor);
	for(i = 0; i < (n_casas-1); i++) {
		for(j = (n_casas-1); j > i; j--) {
			if(casa[j] <= valor) {
				if(casa[i] + casa[j] == valor) break;
			}
		}
		if(casa[j] <= valor) {
			if(casa[i] + casa[j] == valor) break;
		}
	}
	printf("%d %d\n", casa[i], casa[j]);
	return 0;
}
