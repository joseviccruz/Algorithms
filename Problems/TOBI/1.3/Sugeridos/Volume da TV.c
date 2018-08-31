#include <stdio.h>

int main() {
	int volume, trocas, i, vol;
	scanf("%d %d", &volume, &trocas);
	for(i = 0; i < trocas; i++) {
		scanf("%d", &vol);
		volume += vol;
		if(volume > 100) volume = 100;
		if(volume < 0) volume = 0;
	}
	printf("%d", volume);
	return 0;
}
