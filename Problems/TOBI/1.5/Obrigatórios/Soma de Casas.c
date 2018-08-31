#include <stdio.h>

int binSearch(int vetor[], int menor, int maior, int valor);

int main() {
	int n_casas, casa[100000], valor, aux, i, j;
	scanf("%d", &n_casas);
	for(i = 0; i < n_casas; i++) {
		scanf("%d", &casa[i]);

	}
	scanf("%d", &valor);
	for(i = 0; i < (n_casas-1); i++) {
		aux = binSearch(casa, i+1, n_casas, (valor-casa[i]));
		if(aux != -1) break;
	}
	printf("%d %d\n", casa[i], casa[aux]);
	return 0;
}

int binSearch(int vetor[], int menor, int maior, int valor) {
	int meio = (maior+menor)/2;
	if(vetor[meio] == valor) return meio;
	if(menor >= maior) return -1;
	else {
		if (vetor[meio] > valor) binSearch(vetor, menor, meio-1, valor);
		else binSearch(vetor, meio+1, maior, valor);
	}
}
