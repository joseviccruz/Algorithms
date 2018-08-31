#include <stdio.h>

int main() {
	int i;
	char frase[1001];
	scanf(" %[^\n]", frase);
	
	for(i=0; frase[i] != '\0'; i++) {
		if(frase[i] != 'p' && frase[i] != '1') printf("%c", frase[i]);
		if(frase[i] == 'p' && frase[i+1] == 'p') frase[i+1] = '1';
		if(frase[i] == 'p' && frase[i+1] == '1') printf("%c", frase[i]);
	}
	return 0;
}

/********************************************************
*	Nota: É necessário substituir a letra 'p' seguinte,	*
* pois sem realizar a troca, o 'p' posterior também será*
* considerado, por exemplo "pppa", só deveria ser prin- *
* tado: "pa", mas sem substituir, seria "ppa".          *
*********************************************************/
