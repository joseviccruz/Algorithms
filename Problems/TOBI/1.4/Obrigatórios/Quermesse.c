#include <stdio.h>

int main() {
	int participantes, i, a=1;
	do {
		scanf("%d", &participantes);
		if(participantes != 0) {
			int ingresso[participantes];
			for(i = 0; i < participantes; i++) {
				scanf("%d", &ingresso[i]);
				if(ingresso[i] == (i+1)) {
					printf("Teste %d\n%d\n\n", a, (i+1));
				}
			}
			++a;
		}
	} while(participantes != 0);
	return 0;
}
