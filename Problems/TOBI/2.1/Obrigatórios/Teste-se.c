#include <stdio.h>
#include <stdlib.h>

int bubble_cres(int n_predios, int predios[]);
int bubble_decres(int n_predios, int predios[]);

int main() {
	int i, n_predios, n_vendidos, d_total=0;
	scanf("%d %d", &n_predios, &n_vendidos);
	int predios[n_predios], distancias[n_predios-1];
	for(i = 0; i < n_predios; i++) scanf("%d", &predios[i]);
	bubble_cres(n_predios, predios);
	for(i = 0; i < n_predios; i++) printf("%d | ", predios[i]);
	for(i = 0; i < n_predios-1; i++) {
		distancias[i] = abs(predios[i] - predios[i+1]);
		d_total += distancias[i];
	}
	printf("\n");
	bubble_decres((n_predios-1), distancias);
	for(i = 0; i < n_predios-1; i++) printf("%d | ", distancias[i]);
	printf("\n- %d -\n", d_total);
	for(i = 0; i < n_vendidos; i++) {
		d_total -= distancias[i];
	}
	printf("\n-%d-\n", d_total);
	return 0;
}

int bubble_cres(int n_predios, int predios[]) {
	int i, troca = 1, aux;
	while(troca) {
		troca = 0;
		for(i = 0; i < (n_predios-1); i++) {
			if(predios[i] > predios[i+1]) {
				aux = predios[i];
				predios[i] = predios[i+1];
				predios[i+1] = aux;
				troca = 1;
			}
		}
	}
}

int bubble_decres(int n_predios, int predios[]) {
	int i, troca = 1, aux;
	while(troca) {
		troca = 0;
		for(i = 0; i < (n_predios-1); i++) {
			if(predios[i] < predios[i+1]) {
				aux = predios[i];
				predios[i] = predios[i+1];
				predios[i+1] = aux;
				troca = 1;
			}
		}
	}
}
