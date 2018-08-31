#include <stdio.h>

int main() {
	int altura1, largura1, altura2, largura2, altura_ideal, largura_ideal, troca;
	scanf("%d %d", &altura1, &largura1);
	scanf("%d %d", &altura2, &largura2);
	scanf("%d %d", &altura_ideal, &largura_ideal);

	if(altura_ideal > largura_ideal) {
		troca = altura_ideal;
		altura_ideal = largura_ideal;
		largura_ideal = troca;
	}
	if(altura1 > largura1) {
		troca = altura1;
		altura1 = largura1;
		largura1 = troca;
	}
	if(altura2 > largura2) {
		troca = altura2;
		altura2 = largura2;
		largura2 = troca;
	}
	troca=0;
	//printf("altura1 = %d | largura1 = %d\naltura2 = %d | largura2 = %d\nalturaI = %d | larguraI = %d\n", altura1, largura1, altura2, largura2, altura_ideal, largura_ideal);

	if(altura1 >= altura_ideal && largura1 >= largura_ideal) {																														//Ok! Caso a area de um unico lençol já for maior que a área do lençol que deseja-se criar, já é o suficiente.
		printf("S");
		troca++;
	}
	if(troca == 0 && altura2 >= altura_ideal && largura2 >= largura_ideal) {																							//Ok! Caso a area de um unico lençol já for maior que a área do lençol que deseja-se criar, já é o suficiente.
		printf("S");
		troca++;
	}

	if(troca == 0 && (altura1 + altura2 >= largura_ideal) && largura1 >= altura_ideal && largura2 >= altura_ideal) {			//Ok! Foi escolhido como o maior lado a largura, e o menor, a altura. Sendo assim, deve-se atentar ao caso em que, a soma dos menores lados dos leçóis sejam >= ao maior lado do lençol definitivo.
		printf("S");
		troca++;
	}

	if(troca == 0 && (largura1 + largura2 >= largura_ideal) && altura1 >= altura_ideal && altura2 >= altura_ideal) {			//Ok!Esse é o caso, em que, a soma dos maiores lados dos leçóis sejam >= ao maior lado do lençol definitivo.
		printf("S");
		troca++;
	}
	if(troca == 0 && (altura1 + largura2 >= largura_ideal) && largura1 >= altura_ideal && altura2 >= altura_ideal) {			//Ok! PRESTAR BASTANTE ATENÇÃO!!! A SOMA DOS LADOS ALTERNADOS TAMBÉM É UM POSSÍVEL CASO, E ELA SEVE SER MAIOR QUE O MAIOR LADO!
		printf("S");
		troca++;
	}
	if(troca == 0 && (largura1 + altura2 >= largura_ideal) && altura1 >= altura_ideal && largura2 >= altura_ideal) {			//Ok! PRESTAR BASTANTE ATENÇÃO!!! A SOMA DOS LADOS ALTERNADOS TAMBÉM É UM POSSÍVEL CASO, E ELA SEVE SER MAIOR QUE O MAIOR LADO!
		printf("S");
		troca++;
	}
	if(troca == 0) printf("N");
	return 0;
}
