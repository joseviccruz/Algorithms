#include <stdio.h>

int main() {
	int bandejas, i, quebrados=0;
	scanf("%d", &bandejas);
	int latas[bandejas], copos[bandejas];
	for(i = 0; i < bandejas; ++i) {
		scanf("%d %d", &latas[i], &copos[i]);
		if(latas[i] > copos[i]) quebrados += copos[i];
	}
	printf("%d", quebrados);
	return 0;
}
