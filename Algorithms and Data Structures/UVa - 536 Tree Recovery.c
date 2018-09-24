#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxn 50

int i, priority[maxn], len;
char stra[maxn], strb[maxn];

typedef struct node {
	char id;
	struct node *left, *right;
} Node;

typedef struct tree {
	Node *root;
} Tree;

Tree *createTree() {
	Tree *tree = (Tree*) malloc(sizeof(Tree));
	tree->root = NULL;
	return tree;
}

Node *insert(Node *root, char value) {
	if(!root) {
		Node *node = (Node*) malloc(sizeof(Node));
		node->id = value;
		node->left = node->right = NULL;
		return node;
	} else {
		if(priority[value-'A'] > priority[root->id-'A']) {
			root->right = insert(root->right, value);
		} else if(priority[value-'A'] < priority[root->id-'A']) {
			root->left = insert(root->left, value);
		}
	}
	return root;
}

void posOrder(Node *node) {
	if(node) {
		posOrder(node->left);
		posOrder(node->right);
		putchar(node->id);
	}
}

int main() {
	while(scanf(" %s %s", stra, strb) != EOF) {
		Tree *tree = createTree();
		len = strlen(strb);
		for(i = 0; i < len; i++) {
			priority[strb[i]-'A'] = i;
		}
		len = strlen(stra);
		for(i = 0; i < len; i++) {
			tree->root = insert(tree->root, stra[i]);
		}
		posOrder(tree->root); putchar('\n');
	}
	return 0;
}
