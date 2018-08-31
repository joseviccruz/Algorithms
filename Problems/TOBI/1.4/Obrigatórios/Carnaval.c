#include <stdio.h>

int main() {
	int i;
	double nota[5], maior=0, menor=0, soma=0;
	scanf("%lf", &nota[0]);
	menor = nota[0];
	maior = nota[0];
	soma = nota[0];
	for(i = 1; i < 5; ++i) {
		scanf("%lf", &nota[i]);
		if(nota[i] > maior) maior = nota[i];
		if(nota[i] < menor) menor = nota[i];
		soma+=nota[i];
	}
	printf("%.1lf", (soma - maior - menor));
	return 0;
}
