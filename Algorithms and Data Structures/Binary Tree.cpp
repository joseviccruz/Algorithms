/******************************************************************************
* Univesidade Federal de Pernambuco -- UFPE (http://www.ufpe.br)
* Centro de Informatica -- CIn (http://www.cin.ufpe.br)
* Bacharelado em Engenharia da Computacao
* IF672 -- Algoritmos e Estruturas de Dados
*
* Autor:	Jose Victor Silva Cruz
* Email:	jvsc@cin.ufpe.br
* Data:		2017-08-15
*
* Descricao:  Demonstracao  da  implementacao  de  uma  arvore binaria de busca
* em C/C++. Insercao e caminhamentos em pre-ordem, in-ordem, e pos-ordem.
*
* Licenca: The MIT License (MIT)
*			Copyright(c) 2017 Jose Victor Silva Cruz
*
*******************************************************************************/
#include <bits/stdc++.h>

using namespace std;

typedef struct dataNode {
	int id;
} DataNode;

typedef struct node {
	DataNode data;
	struct node *father;
	struct node *left;
	struct node *right;
} Node;

typedef struct tree {
	Node *root;
} Tree;

Node *createNode(Node *father, DataNode data) {
	Node *node = (Node*) malloc(sizeof(Node));
	node->data = data;
	node->father = father;
	node->left = NULL;
	node->right = NULL;
	return node;
}

Tree *createTree(DataNode data) {
	Tree *tree = (Tree*) malloc(sizeof(Tree));
	tree->root = createNode(NULL, data);
	return tree;
}

void insert(Node *node, DataNode data) {
	if(data.id < node->data.id) {
		if(node->left == NULL) node->left = createNode(node, data);
		else insert(node->left, data);
	} else {
		if(node->right == NULL) node->right = createNode(node, data);
		else insert(node->right, data);
	}
}

void preOrder(Node *node) {
	if(node != NULL) {
		cout << node->data.id << endl;
		preOrder(node->left);
		preOrder(node->right);
	}
}

void inOrder(Node *node) {
	if(node != NULL) {
		inOrder(node->left);
		cout << node->data.id << endl;
		inOrder(node->right);
	}
}

void posOrder(Node *node) {
	if(node != NULL) {
		posOrder(node->left);
		posOrder(node->right);
		cout << node->data.id << endl;
	}
}

int main() {
	DataNode data;
	Tree *tree = NULL;
	puts("Insira os valores. Digite um numero negativo para encerrar");
	while(cin >> data.id, data.id >= 0) {
		if(tree == NULL) tree = createTree(data);
		else insert(tree->root, data);
	}
	preOrder(tree->root);
	cout << endl;
	inOrder(tree->root);
	cout << endl;
	posOrder(tree->root);
}
