#include <stdio.h>

int main() {
	int a, b, c, d;
	scanf("%d %d %d %d", &a, &b, &c, &d);
	if(a*b >= c*d) {
		if(a*b == c*d) printf("0");
		else printf("-1");
	} else printf("1");
	return 0;
}
