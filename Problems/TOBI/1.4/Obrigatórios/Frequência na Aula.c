#include <stdio.h>

int main() {
	int n_alunos, numero, hash[1000001] = { }, aux1, aux2=0;
	hash[0] = -1;
	scanf("%d", &n_alunos);
	aux1 = n_alunos;
	while(n_alunos != 0) {
		scanf("%d", &numero);
		if(numero == 0) {
			if (numero == hash[numero] || hash[numero] != -1) ++aux2;
		} else {
				if(numero == hash[numero] || hash[numero] != -0) ++aux2;
		}
		hash[numero] = numero;
		--n_alunos;
	}
	printf("%d", aux1 - aux2);
	return 0;
}
