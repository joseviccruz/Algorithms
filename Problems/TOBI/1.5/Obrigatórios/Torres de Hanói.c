#include <stdio.h>
#include <math.h>

int main() {
	long int teste, i=1;
	do {
	scanf("%ld", &teste);
	if(teste != 0) {
		printf("Teste %ld\n%ld\n\n", i, ((long int)pow(2, teste) - 1));
		++i;
	}
	} while(teste != 0);
}
