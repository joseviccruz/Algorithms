#include <stdio.h>

int main() {
	int comprimento, quantidade_paineis=0;
	char painel;
	scanf("%d", &comprimento);
	while(comprimento != 0) {
		scanf(" %c", &painel);
		if(painel == 'P') {
			quantidade_paineis+=2;
		}
		if(painel == 'C') {
			quantidade_paineis+=2;
		}
		if(painel == 'A') {
			quantidade_paineis+=1;
		}
		if(painel == 'D') {
			quantidade_paineis+=0;
		}
	--comprimento;
	}
	printf("%d", quantidade_paineis);
	return 0;
}
