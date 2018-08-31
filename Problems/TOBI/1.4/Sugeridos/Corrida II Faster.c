#include <stdio.h>
#define INT_MAX 100000001
void main() {
	unsigned short int carros, voltas, i, j, posicao[3];
	unsigned int primeiro = INT_MAX, segundo = INT_MAX, terceiro = INT_MAX, tempo[100], aux;
	scanf("%hu %hu", &carros, &voltas);
	for(i = 0; i < carros; i++) {
		aux = 0;
		for(j = 0; j < voltas; j++) scanf("%u", &tempo[j]), aux += tempo[j];
		if(aux < primeiro) terceiro = segundo, posicao[2] = posicao[1], segundo = primeiro, posicao[1] = posicao[0], primeiro = aux, posicao[0] = i+1;
		else if(aux < segundo) terceiro = segundo, posicao[2] = posicao[1], segundo = aux, posicao[1] = i+1;
			else if(aux < terceiro) terceiro = aux, posicao[2] = i+1;
	}
	printf("%hu\n%hu\n%hu", posicao[0], posicao[1], posicao[2]);
}
