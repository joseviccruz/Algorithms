#include <stdio.h>

int main() {
	int metros/*22*/, comprimento/*12*/;
	scanf("%d %d", &metros, &comprimento);
	printf("%d\n", metros - (metros/comprimento)*comprimento);
	return 0;
}
