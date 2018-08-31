/*
Possíveis dúvidas em relação ao código:
	- height não armazena a real altura do nó, mas sim a altura máxima da subárvore daquele nó.
		* Desse modo, sempre ao inserir um novo valor, a altura correnspondente àquele nó será igual a 1;
	- Uma rotação dupla nada mais é do que duas rotações simples. A primeira ocorre para possibilitar a segunda rotação;
	- Uma rotação nada mais é do que uma série de atribuições;
	
	Exemplo de rotação simples:
	1 - Passo:
		A -- height == 3, balance == 2 (Condição necessária para acontecer uma rotação)
		  \
		    B -- height == 2, balance == 1
		      \
		        C -- height == 1, balance == 0
	2 - Passo:
		* Sendo: node == A, node->left == NULL, node->right == B, aux2 == aux1->left
		leftRotation(node);
		* Temos que B (aux1) deverá ser a nova raiz:
			aux1->left = node // A esqueda de B recebe A
			node->right = aux2 // A direita da antiga raiz deve receber a esquerda da nova raiz
			
			// Atualiza as alturas...
			// Returna aux1, a nova raiz;
			
				   B
				/     \
			   A	   C
	
	Exemplo de um caso de rotação dupla:
		B	-- height == 3, balance == 2
		  \
		    D -- height == 2, balance == 1
		  /
		C -- height == 1, balance == 0
		
		* A seguinte condição agora será obedecida:
			getBalance(node->right) < 0;
		* Logo, uma rotação a direita irá ocorrer em D, e a nova configuração será:
		   		   B
				     \
			    	   C
			    	   	 \
			    	   	   D
		* E por fim, uma rotação normal a esqueda:			
				   C
				/     \
			   B	   D
*/

#include <bits/stdc++.h>

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
	Node *aux1 = node->right, *aux2 = aux1->left;

	aux1->left = node;
	node->right = aux2;

	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	aux1->height = 1 + max(getHeight(aux1->left), getHeight(aux1->right));

	return aux1;
}

Node *rightRotate(Node *node) {
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
	
	if(balance > 1) {
		if(getBalance(node->right) < 0) node->right = rightRotate(node->right);// Dual rotation -- Right Left
		return leftRotate(node); //Just Left Rotation
	} else if(balance < -1) {
		if(getBalance(node->right) > 0) node->left = leftRotate(node->left);// Dual rotation -- Left Right
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

int main() {
	Node *root = NULL; //Tree tree;
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
	return 0;
}
