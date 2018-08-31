#include <stdio.h>
#include <math.h>

int main() {
	int lado, divisoes=0;
	scanf("%d", &lado);
	while (lado >= 2) {
	lado/=2;
	++divisoes;
	}
	printf("%d", (int)pow(4, divisoes));
	return 0;
}
