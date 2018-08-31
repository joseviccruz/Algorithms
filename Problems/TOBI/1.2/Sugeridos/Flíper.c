#include <stdio.h>

int main() {
	int p, r;
	scanf("%d %d", &p, &r);
	if(p == r) {
		if(p == 0) printf("C");
		else printf("A");
	} else {
		if(p == 1 && r == 0) printf("B");
		else printf("C");
	}
	return 0;
}
