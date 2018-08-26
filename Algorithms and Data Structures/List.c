#include <iostream>
#include <cstdlib>
#define loop(a, b, c) for(int a = b; a < c; a++)

using namespace std;

// Estruturas Necessárias

typedef struct dataNode {
	int id;
} DataNode;

typedef struct node {
	DataNode data;
	struct node *next;
} Node;

typedef struct list {
	int size;
	Node *head;
} List;

//

// Funções Necessárias

List *createList() {
	List *list = (List*) malloc(sizeof(List));
	list->head= NULL;
	list->size = 0;
	return list;
}

void push(List *list, DataNode data) {
	Node *node = (Node*) malloc(sizeof(Node));
	node->data = data;
	node->next = list->head;
	list->head = node;
	++list->size;
}

void push_back(List *list, DataNode data) {
	if(!list->size) push(list, data);
	else {
		Node *pointer = list->head, *node = (Node*) malloc(sizeof(Node));
		node->data = data;
		while(pointer->next != NULL) pointer = pointer->next;
		pointer->next = node;
		node->next = NULL;
		++list->size;
	}
}

void pop(List *list) {
	if(list->size) {
		Node *pointer = list->head;
		list->head = pointer->next;
		free(pointer);
		--list->size;
	}
}

void pop_back(List *list) {
	if(list->size <= 1) pop(list);
	else {
		Node *pointer = list->head, *tofree;
		while(pointer->next->next != NULL) pointer = pointer->next;
		tofree = pointer->next;
		free(tofree);
		pointer->next = NULL;
		--list->size;
	}
}

Node *atPos(List *list, int index) {
	if(!(index >= list->size || index < 0)) {
		Node *pointer = list->head;
		int i = 0;
		while(i++ != index) pointer = pointer->next;
		return pointer;
	} else return NULL;
}

int indexOf(List *list, DataNode data) {
	if(list->size) {
		int index = 0;
		Node *pointer = list->head;
		while(pointer != NULL && pointer->data.id != data.id) {
			++index;
			pointer = pointer->next;
		}
		if(pointer != NULL) return index;
	}
	return -1;
}

void erase(List *list, int index) {
	if(index >= 0 && index < list->size) {
		if(!index) pop(list);
		else {
			Node *p_free = atPos(list, index), *p_before = atPos(list, index-1);
			p_before->next = p_free->next;
			free(p_free);
			--list->size;
		}
	}
}

void insert(List *list, DataNode data, int index) {
	if(!index) push(list, data);
	else if(index >= 0 && index < list->size) {
		Node *p_add = (Node*) malloc(sizeof(Node)), *p_before = atPos(list, index-1), *p_after = atPos(list, index);
		p_add->data = data;
		p_before->next = p_add;
		p_add->next = p_after;
		++list->size;
	}
}

void xchgNodes(List *list, Node *nodeA, Node *nodeB) {
	if(nodeA != nodeB) {
		int indexA = indexOf(list, nodeA);
		int indexB = indexOf(list, nodeB);
		if(indexA != -1 && indexB != -1) {
			if(indexA > indexB) {
				nodeA = nodeB;
				indexA = indexB;
				nodeB = atPos(list, indexA);
				indexB = indexOf(list, nodeB);
			}
			Node *pB = atPos(list, indexB-1);
			if(nodeA == list->head) list->head = nodeB; 
			else {
				Node *pA = atPos(list, indexA-1);
				pA->next = nodeB;
			}
			pB->next = nodeA;
			Node *aux = nodeA->next;
			nodeA->next = nodeB->next;
			nodeB->next = aux;
		}
	}
}

//

int main() {
	List *list = createList();
	DataNode aux;
	aux.id = 1;
	push_back(list, aux);
	aux.id = 2;
	push_back(list, aux);
	aux.id = 3;
	push_back(list, aux);
	aux.id = 4;
	push_back(list, aux);
	aux.id = 5;
	push_back(list, aux);
	aux.id = 10;
	insert(list, aux, (list->size)/2);
	Node *pointer = list->head;
	loop(i, 0, list->size) cout << pointer->data.id << endl, pointer = pointer->next;
	cout << endl;
	pop(list), pop_back(list);
	pointer = list->head;
	loop(i, 0, list->size) cout << pointer->data.id << endl, pointer = pointer->next;
	cout << endl;
	aux.id = 3;
	erase(list, indexOf(list, aux));
	pointer = list->head;
	loop(i, 0, list->size) cout << pointer->data.id << endl, pointer = pointer->next;
	return 0;
}
