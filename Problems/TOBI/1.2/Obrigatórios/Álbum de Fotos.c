#include <stdio.h>

int main() {
	int l_pagina, h_pagina, troca_pagina;
	int l_foto1, h_foto1, l_foto2, h_foto2, troca_foto1, troca_foto2;
	scanf ("%d %d %d %d %d %d", &l_pagina, &h_pagina, &l_foto1, &h_foto1, &l_foto2, &h_foto2);
	if(l_pagina < h_pagina) {
		troca_pagina = l_pagina;
		l_pagina = h_pagina;
		h_pagina = troca_pagina;
	}
	if(l_foto1 > h_foto1) {
		troca_foto1 = l_foto1;
		l_foto1 = h_foto1;
		h_foto1 = troca_foto1;
	}
	if(l_foto2 > h_foto2) {
		troca_foto2 = l_foto2;
		l_foto2 = h_foto2;
		h_foto2 = troca_foto2;
	}
	if ((((l_foto1 + l_foto2) <= l_pagina) && h_foto1 <= h_pagina && h_foto2 <= h_pagina) || (((h_foto1 + h_foto2) <= l_pagina) && l_foto1 <= h_pagina && l_foto2 <= h_pagina) || (((h_foto1 + l_foto2) <= l_pagina) && l_foto1 <= h_pagina && h_foto2 <= h_pagina) || (((l_foto1 + h_foto2) <= l_pagina) && h_foto1 <= h_pagina && l_foto2 <= h_pagina)) {
	printf("S");
	} else {
	printf("N");
	}
	return 0;
}
