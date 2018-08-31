#include <stdio.h>

int main() {
	int fileiras, posicoes, primFileira, local;
	scanf("%d %d %d %d", &fileiras, &posicoes, &primFileira, &local);
	if(local > (fileiras - (primFileira-1))*posicoes) {
		printf("PROXIMO VOO");
	} else {
		printf("%d %c", primFileira + (local-1)/posicoes, (char)((local-1)%posicoes) + 'A');
	}
	return 0;
}
