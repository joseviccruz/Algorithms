#include <stdio.h>

int bubble(int n_predios, int predios[], int cres_decres);			//Sendo 0: Crescente, e qualquer outro numero: Decrescente

int main() {
	int i, n_predios, n_vendidos, d_total=0;
	scanf("%d %d", &n_predios, &n_vendidos);
	int predios[n_predios], distancias[n_predios-1];
	for(i = 0; i < n_predios; i++) scanf("%d", &predios[i]);
	bubble(n_predios, predios, 0);
	for(i = 0; i < n_predios-1; i++) {
		distancias[i] = predios[i+1] - predios[i];
		d_total += distancias[i];
	}
	bubble((n_predios-1), distancias, 1);
	for(i = 0; i < n_vendidos; i++) {
		d_total -= distancias[i];
	}
	printf("%d", d_total);
	return 0;
}

int bubble(int n_predios, int predios[], int cres_decres) {
	int i, troca = 1, aux;
	while(troca) {
		troca = 0;
		for(i = 0; i < (n_predios-1); i++) {
			if(cres_decres == 0) {
				if(predios[i] > predios[i+1]) {
					aux = predios[i];
					predios[i] = predios[i+1];
					predios[i+1] = aux;
					troca = 1;
				}
			} else {
				if(predios[i] < predios[i+1]) {
					aux = predios[i];
					predios[i] = predios[i+1];
					predios[i+1] = aux;
					troca = 1;
				}
			}
		}
	}
}
