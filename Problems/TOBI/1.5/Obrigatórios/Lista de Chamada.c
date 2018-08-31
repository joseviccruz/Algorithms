#include <stdio.h>
#include <string.h>

int bubble(int nomes, int id[nomes], char pessoa[][21]);

int main() {
	int nomes, sorteado, i;
	scanf("%d %d", &nomes, &sorteado);
	char pessoa[nomes][21];
	int id[nomes];
	for(i=0; i < nomes; i++) {
		scanf(" %s", pessoa[i]);
		id[i] = i;
	}
	bubble(nomes, id, pessoa);
	printf("%s", pessoa[id[sorteado-1]]);
	return 0;
}

int bubble(int nomes, int id[nomes], char pessoa[][21]) {
	int troca=1, aux, i;
	while(troca) {
		troca=0;
		for(i=0; i < nomes-1; i++) {
			if(strcmp(pessoa[id[i]], pessoa[id[i+1]]) > 0) {
				aux = id[i];
				id[i] = id[i+1];
				id[i+1] = aux;
				troca=1;
			}
		}
	}
}
