#include <stdio.h>

int main() {
	float precoAlcool, precoGasolina, rendAlcool, rendGasolina, a, g;
	scanf("%f %f %f %f", &precoAlcool, &precoGasolina, &rendAlcool, &rendGasolina);
	a = rendAlcool/precoAlcool, g = rendGasolina/precoGasolina;
	if(g >= a) printf("G");
	else printf("A");
	return 0;
}
