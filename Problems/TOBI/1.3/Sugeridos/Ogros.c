#include <stdio.h>

int main() {
	int n_faixas, n_ogros, i, j;
	scanf("%d %d", &n_faixas, &n_ogros);
	int forcas[n_faixas-1], valor_premiacao[n_faixas], pont_ogro[n_ogros];
	for(i = 0; i < (n_faixas-1); i++) {
		scanf("%d", &forcas[i]);
	}
	for(i = 0; i < (n_faixas); i++) {
		scanf("%d", &valor_premiacao[i]);
	}
	for(i = 0; i < (n_ogros); i++) {
		scanf("%d", &pont_ogro[i]);
		for(j = 0; j < (n_faixas-1); j++) {
			if(j == 0) {
				if(pont_ogro[i] < forcas[j]) {
					pont_ogro[i] = valor_premiacao[j];
					break;
				}
			}
			if(pont_ogro[i] >= forcas[j-1] && pont_ogro[i] < forcas[j]) {
				pont_ogro[i] = valor_premiacao[j];
				break;
			}
			if(j == n_faixas-2) {	//"A n-ésima pontuação é composta das forças >= An-1" Devemos lembrar que, por a contagem começar do 0, n-1 equivale a n-2
				if(pont_ogro[i] >= forcas[j]) {
					pont_ogro[i] = valor_premiacao[j+1];
					break;
				}
			}
		}
	}
	for(i = 0; i < (n_ogros); i++) {
		if((i + 1) != n_ogros) printf("%d ", pont_ogro[i]);
		else printf("%d", pont_ogro[i]);
	}
	return 0;
}
