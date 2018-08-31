#include <stdio.h>

int main() {
	int l_cama, h_cama, c_cama, l_porta, h_porta, area_porta;
	scanf("%d %d %d %d %d", &l_cama, &h_cama, &c_cama, &l_porta, &h_porta);
	if (((l_cama <= l_porta && (h_cama <= h_porta || c_cama <= h_porta)) || (h_cama <= l_porta && (l_cama <= h_porta || c_cama <= h_porta)) || (c_cama <= l_porta && (l_cama <= h_porta || h_cama <= h_porta)))) printf("S");
	else printf("N"); 
	return 0;
}



