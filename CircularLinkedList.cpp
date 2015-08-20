#include <stdlib.h>
#include <iostream>
using namespace std;

typedef struct node {

	int data;
	node* next;
} node;

typedef struct CLL {

	node* TAIL;
} CLL;


node* newNode(int data) {
	node* temp = new node;
	temp->data = data;
	temp->next = NULL;
	return temp;
}

CLL* createCLL() {
	CLL* temp = new CLL;
	temp->TAIL = NULL;
	return temp;
}

void insert(CLL* cLL, int data) {

	node* temp = newNode(data);

	if(cLL->TAIL == NULL) {
		temp->next = temp;
		cLL->TAIL = temp;
	}
	else {
		temp->next = cLL->TAIL->next;
		cLL->TAIL->next = temp;
		cLL->TAIL = temp;
	}
}

void sortedInsert(CLL* cLL, int data) {

	node* temp = newNode(data);

	if(cLL->TAIL == NULL) {
		temp->next = temp;
		cLL->TAIL = temp;
		return;
	}

	node* iterate = cLL->TAIL;

	if(cLL->TAIL->data < data) {
		temp->next = iterate->next;
		iterate->next = temp;
		cLL->TAIL = temp;
		return;
	}

	while(iterate->next->data < data) {
		iterate = iterate->next;
	}

	temp->next = iterate->next;
	iterate->next = temp;
}

void printList(CLL* cLL) {

	if(cLL->TAIL == NULL) {
		cout << "No nodes in the list! Returning..." << endl;
		return;
	}

	node* temp = cLL->TAIL->next;
	while(temp != cLL->TAIL) {
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << temp->data << endl;
}

void splitList(CLL* cLL, CLL* cLL1, CLL* cLL2) {

	if(cLL->TAIL == NULL || cLL->TAIL->next == cLL->TAIL) {
		cout << "Less than 2 nodes in the list! Returning..." << endl;
		return;
	}

	node* fastPtr = cLL->TAIL->next;
	node* slowPtr = cLL->TAIL->next;
	node* head = cLL->TAIL->next;
	node* tail = cLL->TAIL;

	while(fastPtr != tail && fastPtr->next != tail) {

		fastPtr = fastPtr->next->next;
		slowPtr = slowPtr->next;					
	}

	cLL2->TAIL = tail;
	cLL1->TAIL = slowPtr;
	cLL2->TAIL->next = slowPtr->next;
	cLL1->TAIL->next = head;
}

int main() {

	CLL* cLL = createCLL();
	CLL* cLL1 = createCLL();
	CLL* cLL2 = createCLL();

	insert(cLL, 5);
	insert(cLL, 6);
	insert(cLL, 7);
	insert(cLL, 8);
	insert(cLL, 9);
	insert(cLL, 10);
	printList(cLL);
/*	sortedInsert(cLL, 7);
	sortedInsert(cLL, 10);
	sortedInsert(cLL, 19);
	sortedInsert(cLL, 20);
	printList(cLL);
*/	splitList(cLL, cLL1, cLL2);
	printList(cLL1);
	printList(cLL2);
	return 0;
}