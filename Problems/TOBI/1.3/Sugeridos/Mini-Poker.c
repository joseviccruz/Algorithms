#include <stdio.h>

int quickSort(int vetor[], int min, int max);
int pontuacao(int qnt, int cartas[]);

int main() {
	int n_casos, cartas[5], i, score, teste=0;
	scanf("%d", &n_casos);
	while(n_casos != 0) {
		teste++;
		for(i = 0; i < 5; i++) {
			scanf("%d", &cartas[i]);
		}
		quickSort(cartas, 0, (5-1));
/*		for(i = 0; i < 5; i++) {
			printf("%d, ", cartas[i]);
		}
		putchar('\n');*/
		score = pontuacao(5, cartas);
		printf("Teste %d\n%d\n\n", teste, score);
		n_casos--;
	}
	return 0;
}

int quickSort(int vetor[], int min, int max) {
	int i, j, pivo, aux;
	i = min, j = max, pivo = vetor[(max+min)/2];
	while(i <= j) {
		while(vetor[i] < pivo && i < max) i++;
        while(vetor[j] > pivo && j > min) j--;
        if(i <= j) {
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            i++;
            j--;
        }
    }
    if(j > min) quickSort(vetor, min, j);
    if(i < max) quickSort(vetor, i, max);
}

int pontuacao(int qnt, int cartas[]) {
	int i, pontuacao=0, num=0, par1=-1, par2=-2, contSeq=0;
	for(i = 0; i < qnt-1; i++) {
		if(cartas[i] == cartas[i+1]-1) contSeq++;
	}
	if(contSeq == 4) pontuacao = 200 + cartas[0];
	else if((cartas[0] == cartas[1] && cartas[1] == cartas[2] && cartas[2] == cartas[3]) ||
			(cartas[1] == cartas[2] && cartas[2] == cartas[3] && cartas[3] == cartas[4])) pontuacao = 180 + cartas[2];
		else if((cartas[0] == cartas[1] && cartas[1] == cartas[2]) ||
				(cartas[2] == cartas[3] && cartas[3] == cartas[4]) ||
				(cartas[1] == cartas[2] && cartas[2] == cartas[3])) {
				if(cartas[0] != cartas[1] || cartas[3] != cartas[4]) pontuacao = 140 + cartas[2];
				else pontuacao = 160 + cartas[2];
			} else { 
				for(i=0; i < qnt; i++) {
					if(cartas[i] == cartas[i+1]) {
						if(par1 == -1) par1 = cartas[i];
						else par2 = cartas[i];
						num++;
					}
				}
				if(num == 1) pontuacao = par1;
				if(num == 2) pontuacao = (par2*3 + par1*2 + 20);
			}
	return pontuacao;
}
