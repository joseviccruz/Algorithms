#include <stdio.h>

int main() {
	int n_questoes, i, acertos=0;
	scanf("%d", &n_questoes);
	char gabarito[n_questoes+1], resposta[n_questoes+1];
	scanf(" %s", gabarito);
	scanf(" %s", resposta);
	for(i = 0; i < n_questoes; ++i) {
		if(gabarito[i] == resposta[i]) ++acertos;
	}
	printf("%d", acertos);
	return 0;
}
