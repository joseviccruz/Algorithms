#include <stdio.h>

int main() {
	int x, y, z;
	scanf("%d %d %d", &x, &y, &z);
	if ((x > y && x < z) || (x > z && x < y)) printf("%d", x);
	if ((y > x && y < z) || (y > z && y < x)) printf("%d", y);
	if ((z > x && z < y) || (z > y && z < x)) printf("%d", z);
	return 0;	
}
