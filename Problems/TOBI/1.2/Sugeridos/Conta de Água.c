#include <stdio.h>

int main() {
	int consumo, valor=7;
	scanf("%d", &consumo);
	if(consumo <= 10) printf("%d", valor);
	if(consumo > 10 && consumo <= 30) printf("%d", valor + (consumo-10));
	if(consumo > 30 && consumo <= 100) printf("%d", valor + 2*(consumo-30) + (20));
	if(consumo > 100) printf("%d", valor + 5*(consumo-100) + 2*(70) + (20));
	return 0;
}
