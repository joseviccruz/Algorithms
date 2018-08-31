#include <stdio.h>

int main() {
	unsigned short int n_celulas, minas[50], resposta[50], i;
	scanf("%hu", &n_celulas);
	for(i = 0; i < 50; i++) resposta[i] = 0;
	for(i = 0; i < n_celulas; i++) {
		scanf("%hu", &minas[i]);
	}
	if(n_celulas == 1) {
		if(minas[0] == 1) resposta[0]++;
		printf("%hu\n", resposta[0]);
	} else {
		for(i = 0; i < n_celulas; i++) {
			if(i == 0) {
				if(minas[i] == 1) resposta[i]++;
				if(minas[i+1] == 1) resposta[i]++;
			}
			if(i != 0 && i != n_celulas-1) {
				if(minas[i-1] == 1) resposta[i]++;
				if(minas[i] == 1) resposta[i]++;
				if(minas[i+1] == 1) resposta[i]++;
			}

			if(i == n_celulas-1) {
				if(minas[i-1] == 1) resposta[i]++;
				if(minas[i] == 1) resposta[i]++;
			}
			printf("%hu\n", resposta[i]);
		}
	}
	return 0;
}
