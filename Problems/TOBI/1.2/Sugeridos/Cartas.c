#include <stdio.h>

int main() {
	int a, b, c, d, e;
	scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
	if((a > b && b > c && c > d && d > e) || (a < b && b < c && c < d && d < e)) {
		if(a < b && b < c && c < d && d < e) printf("C");
		else printf("D");
	} else printf("N");
	
	return 0;
}
