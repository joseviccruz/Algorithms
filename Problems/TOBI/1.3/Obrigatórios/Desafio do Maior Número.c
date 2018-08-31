#include <stdio.h>

int main() {
	int inserido, maior=0;
	do {
		scanf("%d", &inserido);
		if(inserido > maior) maior = inserido;
	} while(inserido != 0);
	printf("%d", maior);
	return 0;
}
