#include <stdio.h>

int main() {
	int i, balas, resposta;
	scanf("%d", &balas);
	int embalagens[balas];
	for(i = 0; i < balas; i++) {
		scanf("%d", &embalagens[i]);
		if(i == 0) resposta = embalagens[i];
		if(embalagens[i] < resposta) resposta = embalagens[i];
	}
	printf("%d", resposta);
	return 0;
}
