#include <stdio.h>

int main() {
	int n, val, val_ant=0, seq1=0, seq2=0;
	scanf("%d", &n);
	while(n != 0) {
		scanf("%d", &val);
		if(val == val_ant) {
			++seq1;
			if (seq1 > seq2) seq2 = seq1;
		}
		if(val != val_ant) seq1 = 0;
		val_ant = val;
		--n;
	}
	printf("%d", seq2+1);
	return 0;
}
