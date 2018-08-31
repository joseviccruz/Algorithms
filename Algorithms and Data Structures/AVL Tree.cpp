/******************************************************************************
* Univesidade Federal de Pernambuco -- UFPE (http://www.ufpe.br)
* Centro de Informatica -- CIn (http://www.cin.ufpe.br)
* Bacharelado em Engenharia da Computacao
* IF672 -- Algoritmos e Estruturas de Dados
*
* Autor:	Jose Victor Silva Cruz
* Email:	jvsc@cin.ufpe.br
* Data:		2017-08-22
*
* Descricao:  Demonstracao  da  implementacao  de  uma  arvore AVL em C/C++.
*
* Licenca: The MIT License (MIT)
*			Copyright(c) 2017 Jose Victor Silva Cruz
*
*******************************************************************************/

#include <bits/stdc++.h>
#define fr(a, b, c) for(int a = b, __ = c; a < __; a++)

using namespace std;

typedef struct dataNode {
	char val;
} DataNode;

typedef struct node {
	DataNode data;
	int height;
	struct node *left;
	struct node *right;
} Node;

typedef struct tree {
	Node *root;
} Tree;

Node *createNode(DataNode data) {
	Node *node = (Node*) malloc(sizeof(Node));
	node->data = data;
	node->height = 1;
	node->left = NULL;
	node->right = NULL;
	return node;
}

int getHeight(Node *node) {return node ? node->height : 0;}

int getBalance(Node *node) {
	if(node) return getHeight(node->right) - getHeight(node->left);
	else return 0;
}

Node *leftRotate(Node *node) {
	//cout << "LR Node: " << node->data.val << endl;
	Node *aux1 = node->right, *aux2 = aux1->left;

	aux1->left = node;
	node->right = aux2;

	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	aux1->height = 1 + max(getHeight(aux1->left), getHeight(aux1->right));

	return aux1;
}

Node *rightRotate(Node *node) {
	//cout << "RR Node: " << node->data.val << endl;
	Node *aux1 = node->left, *aux2 = aux1->right;

	aux1->right = node;
	node->left = aux2;
	
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	aux1->height = 1 + max(getHeight(aux1->left), getHeight(aux1->right));
	
	return aux1;
}

Node *insert(Node *node, DataNode data) {
	if(!node) return createNode(data);
	
	if(data.val != node->data.val) {
		if(data.val > node->data.val) node->right = insert(node->right, data);
		else node->left = insert(node->left, data);
	} else return node;
	
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	
	int balance = getBalance(node);
	
	//cout << node->data.val << " | " << balance << endl;
	
	if(balance > 1) {
		if(getBalance(node->right) < 0) node->right = rightRotate(node->right);//, cout << "Right Left\n"; //Right Left
		return leftRotate(node); //Just Left Rotation
	} else if(balance < -1) {
		if(getBalance(node->right) > 0) node->left = leftRotate(node->left);//, cout << "Left Right\n"; // Left Right
		return rightRotate(node); //Just Right Rotation
	}
	
	return node;
}

void inOrder(Node *node) {
	if(node) {
		inOrder(node->left);
		cout << " " << node->data.val;
		inOrder(node->right);
	}
}

main() {
	//Tree tree;
	Node *root = NULL;
	DataNode data;
	while(cin >> data.val && data.val != '*') {
		root = insert(root, data);
		cout << "In Order:";
		inOrder(root);
		puts("");
		cout << "Root....: " << root->data.val << endl;
		//if(root->left) cout << "Left Son: " << root->left->data.val << endl;
		//if(root->right) cout << "Right S.: " << root->right->data.val << endl;
	}
}
