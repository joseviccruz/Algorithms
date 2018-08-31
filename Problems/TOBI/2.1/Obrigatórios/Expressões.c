#include <stdio.h>
#define MAXX 100001

int main() {
	char inserido, anterior, proximo, resposta = 'N';
	int i, linhas, a=0, b=0, c=0, a1=0, b1=0, c1=0;
	scanf("%d", &linhas);
	scanf("%c", &inserido);
	for(i = 0; i < linhas; i++) {
		while(scanf("%c", &inserido) && inserido != '\n') {
			if(inserido == '(') a++;
			if(inserido == '[') b++;
			if(inserido == '{') c++;

			if(inserido == ')') a1++;
			if(inserido == ']') b1++;
			if(inserido == '}') c1++;

			if(inserido == '(' || inserido == '{' || inserido == '[') anterior = inserido;
			if(inserido == ')' || inserido == '}' || inserido == ']') proximo = inserido;

			if((anterior == '(' || anterior == '[' || anterior == '{') && (proximo == ')' || proximo == ']' || proximo == '}')) {
				if(anterior == '(' && proximo != ')') a1 = MAXX;
				if(anterior == '[' && proximo != ']') b1 = MAXX;
				if(anterior == '{' && proximo != '}') c1 = MAXX;
			}
			
			if(a1 != 0 && a == 0) a1 = MAXX;
			if(b1 != 0 && a == 0) b1 = MAXX;
			if(c1 != 0 && a == 0) c1 = MAXX;
		}
		if((a - a1 == 0) && (b - b1 == 0) && (c - c1 == 0)) resposta = 'S';
		printf("%c\n", resposta);
	}
	return 0;
}
