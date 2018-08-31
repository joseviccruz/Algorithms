#include <stdio.h>

int main() {
	int n_dias, saldo, i;
	scanf("%d %d", &n_dias, &saldo);
	int mov[n_dias], menor = saldo;
	for(i = 0; i < n_dias; i++) {
		scanf("%d", &mov[i]);
		saldo += mov[i];
		if(saldo < menor) menor = saldo;
	}
	printf("%d", menor);
	return 0;
}
