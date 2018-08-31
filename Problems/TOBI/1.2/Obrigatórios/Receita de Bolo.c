#include <stdio.h>

int main() {
	int farinha, ovos, leite, quantidade;
	scanf("%d %d %d", &farinha, &ovos, &leite);
	(farinha /= 2), (ovos /= 3), (leite /= 5);
	if (farinha <= ovos && farinha <= leite) quantidade = farinha;
	if (ovos <= farinha && ovos <= leite) quantidade = ovos;
	if (leite <= ovos && leite <= farinha) quantidade = leite;
	printf("%d", quantidade);
	return 0;
}
