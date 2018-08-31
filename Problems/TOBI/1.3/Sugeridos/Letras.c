#include <stdio.h>

int main() {
	int i, conta_letra=0, aux1=0, palavras=1;
	char letra, frase[1001];
	scanf(" %c", &letra);
	scanf(" %[^\n]", frase);
	for(i=0; frase[i] != '\0'; i++) {
		if(frase[i] == letra) {
			aux1 = 1;
		}
		if(frase[i] == ' ') {
			palavras++;
		}
		if(((frase[i] == ' '|| frase[i+1] == '\0') && aux1 == 1)) {
			conta_letra++;
			aux1=0;
		}
	}
	printf("%.1f", 100*((float)conta_letra/(float)palavras));
	return 0;
}
