#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef struct aluno {
	char nome[21];
} Aluno;

bool condition(Aluno a, Aluno b) {
	return (strcmp(a.nome, b.nome) <= 0);
}

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	Aluno aluno[n];
	for(int i = 0; i < n; i++) {
		scanf(" %s", aluno[i].nome);
	}
	sort(aluno, aluno+n, condition);
	printf("%s", aluno[k-1].nome);
	return 0;
}
