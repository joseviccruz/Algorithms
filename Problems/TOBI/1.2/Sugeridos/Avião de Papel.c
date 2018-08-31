#include <stdio.h>

int main() {
	int competidores, folhasDir, folhasRec;
	scanf("%d %d %d", &competidores, &folhasDir, &folhasRec);
	if(folhasDir/competidores >= folhasRec) printf("S");
	else printf("N");
	return 0;
}
