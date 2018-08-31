#include <stdio.h>

int main() {
	int nota;
	scanf("%d", &nota);
	if(nota == 0) printf("E");
	if(nota >= 1 && nota <= 35) printf("D");
	if(nota >= 36 && nota <= 60) printf("C");
	if(nota >= 61 && nota <= 85) printf("B");
	if(nota >= 86 && nota <= 100) printf("A");
	return 0;
}
