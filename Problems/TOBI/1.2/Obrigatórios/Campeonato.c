#include <stdio.h>

int main() {
	int vitorias_c, empates_c, sg_c, vitorias_f, empates_f, sg_f;
	scanf("%d %d %d %d %d %d", &vitorias_c, &empates_c, &sg_c, &vitorias_f, &empates_f, &sg_f);
	vitorias_c *= 3, vitorias_f *= 3;
	if ((vitorias_c + empates_c) == (vitorias_f + empates_f)) {
		if (sg_c == sg_f) printf("=");
		else {
		if (sg_c > sg_f) printf("C");
		else printf("F");
		}
	} else {
		if ((vitorias_c + empates_c) > (vitorias_f + empates_f)) printf("C");
		else printf("F");	
	}
	return 0;	
}
