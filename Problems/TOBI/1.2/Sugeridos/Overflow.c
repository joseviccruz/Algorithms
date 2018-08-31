#include <stdio.h>
#include <stdlib.h>

int main() {
	int maior_numero, p, q;
	char espaco1, sinal, espaco2;
	scanf("%d", &maior_numero);
	scanf("%d%c%c%c%d", &p, &espaco1, &sinal, &espaco2, &q);
	if(sinal == '+') {
		if(abs(p+q) <= maior_numero) printf("OK");
		else printf("OVERFLOW");
	}
	if(sinal == '*') {
		if(abs(p*q) <= maior_numero) printf("OK");
		else printf("OVERFLOW");
	}
	return 0;
}
