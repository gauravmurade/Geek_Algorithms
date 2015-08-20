#include <iostream>
#include <limits.h>
#include <stdlib.h>
using namespace std;

typedef struct node {

	int data;
	node* next;
}node;

void append(node*& HEAD, int data) {

	node* newNode = new node;
	newNode->data = data;
	newNode->next = NULL;

	if(HEAD == NULL) {
		HEAD = newNode;
		return;
	}
	node* temp = HEAD;
	while(temp->next) {
		temp = temp->next;
	}
	temp->next = newNode;
}

void push(node*& HEAD, int data) {

	node* newNode = new node;
	newNode->data = data;

	if(HEAD == NULL) {
		newNode->next = NULL;
		HEAD = newNode;
		return;
	}
	newNode->next = HEAD;
	HEAD = newNode;
}

void insertAfter(node*& HEAD, int data) {

	if(HEAD == NULL) {
		push(HEAD, data);
		return;
	}

	node* newNode = new node;
	newNode->data = data;
	newNode->next = HEAD->next;
	HEAD->next = newNode;
}

void printList(node* HEAD) {

	if(HEAD == NULL) {
		cout << "The List does not contain any node! Returning..." << endl;
		return;
	}

	while(HEAD != NULL) {
		cout << HEAD->data << " ";
		HEAD = HEAD->next;
	}
	cout << endl;
}

void deleteNode(node*& HEAD, int data) {

	if(HEAD == NULL) {
		return;
	}

	if(HEAD->data == data) {
		node* temp = HEAD;
		HEAD = temp->next;
		temp->next = NULL;
		free(temp);
		return;
	}

	node* beforeTemp = HEAD;
	node* temp = HEAD->next;

	while(temp != NULL && temp->data != data) {
		temp = temp->next;
		beforeTemp = beforeTemp->next;
	}

	if(temp != NULL) {
		beforeTemp->next = temp->next;
		temp->next = NULL;
		free(temp);
	}	
}

void deleteAltNode(node*& HEAD) {

	if(HEAD == NULL) {
		return;
	}

	node* beforeTemp = HEAD;
	node* temp = HEAD->next;

	if(temp != NULL) {
		beforeTemp->next = temp->next;
		temp->next = NULL;
		free(temp);
		if(beforeTemp->next != NULL) {
			deleteAltNode(beforeTemp->next);
		}
	}	
}

void deleteAltNodeIterative(node*& HEAD) {

	if(HEAD == NULL) {
		return;
	}

	node* beforeTemp = HEAD;
	node* temp = HEAD->next;

	while(temp != NULL) {
		beforeTemp->next = temp->next;
		temp->next = NULL;
		free(temp);
		temp = NULL;
		if(beforeTemp->next != NULL) {
			beforeTemp = beforeTemp->next;
			temp = beforeTemp->next;
		}
	}	
}

int lengthList(node* HEAD) {

	int count = 0;
	while(HEAD != NULL) {
		HEAD = HEAD->next;
		count++;
	}
	return count;
}

int lengthListRecursive(node* HEAD) {

	if(HEAD == NULL) {
		return 0;
	}
	return 1 + lengthListRecursive(HEAD->next);
}

bool search(node* HEAD, int key) {

	while(HEAD != NULL) {
		if(HEAD->data == key) {
			return true;
		}
		HEAD = HEAD->next;
	}
	return false;
}

bool searchRecursive(node* HEAD, int key) {

	if(HEAD == NULL) {
		return false;
	}

	if(HEAD->data == key) {
		return true;
	}
	return searchRecursive(HEAD->next, key);
}

int nthNode(node* HEAD, int index) {

	while(HEAD != NULL) {
		if(index == 1) {
			return HEAD->data;
		}
		HEAD = HEAD->next;
		index -= 1;
	}
	return INT_MIN;
}

int nthNodeRecursive(node* HEAD, int index) {

	if(HEAD == NULL) {
		return INT_MIN;
	}

	if(index == 1) {
		return HEAD->data;
	}
	return nthNodeRecursive(HEAD->next, index-1);
}

void deleteThisNode(node* nodePtr) {

	if(nodePtr == NULL) {
		return;
	}

	node* nextNode = nodePtr->next;
	if(nextNode != NULL) {
		nodePtr->data = nextNode->data;
		nodePtr->next = nextNode->next;	
		nextNode->next = NULL;
		free(nextNode);
	}
}

node* middleElementOfList(node* HEAD) {

	if(HEAD == NULL) {
		cout << "The List does not contain any node! Returning..." << endl;
		return NULL;
	}

	if(HEAD->next == NULL) {
		cout << HEAD->data << endl;
		return NULL;
	}

	node* fastPtr = HEAD;
	node* slowPtr = HEAD;
	while(fastPtr != NULL) {
		if(fastPtr->next != NULL) {
			fastPtr = fastPtr->next->next;
			slowPtr = slowPtr->next;
		}
		else {
			fastPtr = fastPtr->next;	
		}
	}
	cout << slowPtr->data << endl;
	return slowPtr;
}

int nthNodeFromTheEnd(node* HEAD, int n) {

	if(n <= 0) {
		cout << "Enter a valid n! Returning..." << endl;
		return INT_MIN;
	}

	node* temp = HEAD;
	while(n != 0 && temp != NULL) {
		temp = temp->next;
		n -= 1;
	}

	if(n > 0) {
		cout << "n greater than length of the list! Returning..." << endl;
		return INT_MIN;
	}

	while(temp != NULL) {
		temp = temp->next;
		HEAD = HEAD->next;		
	}
	return HEAD->data;
}

void deleteList(node*& HEAD) {

	if(HEAD == NULL) {
		cout << "The List does not contain any node! Returning..." << endl;
		return;
	}

	node* temp = HEAD;
	while(HEAD != NULL) {
		HEAD = HEAD->next;
		temp->next = NULL;
		free(temp);
		temp = HEAD;
	}
}

int count(node* HEAD, int key) {

	int count = 0;
	while(HEAD != NULL) {
		if(HEAD->data == key) {
			count += 1;
		}		
		HEAD = HEAD->next;
	}
	return count;
}

void reverse(node*& current) {

	node* prev = NULL;
	node* next;


	while(current != NULL) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next; 
	}

	current = prev;
}

void removeLoop(node* slowPtr, node* current) {				

	cout << "Pointers met at: " << slowPtr->data << endl;
	node* findIntersectionPtr = current;
	node* dupSlowPtr = slowPtr;
	node* fastPtr = slowPtr;
	int loopLength = 0;

	do {
		fastPtr = fastPtr->next->next;
		slowPtr = slowPtr->next;
		loopLength += 1;
	} while(fastPtr != slowPtr);

	cout << "Loop Length is: " << loopLength << endl;

	while(findIntersectionPtr != dupSlowPtr) {
		dupSlowPtr = dupSlowPtr->next;
		findIntersectionPtr = findIntersectionPtr->next;
	}
	cout << "Cycle starts at: " << findIntersectionPtr->data << endl;
	return;
}

void detectLoop(node* current) {

	node* fastPtr = current;
	node* slowPtr = current;

	while(fastPtr != NULL) {
		if(fastPtr->next != NULL) {
			fastPtr = fastPtr->next->next;
			slowPtr = slowPtr->next;
			if(fastPtr == slowPtr) {
				removeLoop(slowPtr, current);
				return;
			}
		}
		else {
			fastPtr = fastPtr->next;	
		}
	}
	cout << "The list ended!" << endl;
}

void rotate(node*& current, int rotateBy) {

	node* HEAD = current;
	if(rotateBy <= 0) {
		cout << "Enter a valid rotateBy! Returning..." << endl;
		return;
	}
	node* temp = current;
	while(rotateBy != 1 && current != NULL) {
		current = current->next;
		rotateBy -= 1;
	}

	if(rotateBy > 1 || current == NULL || current->next == NULL) {
		current = HEAD;
		cout << "The value of rotateBy specified is too big! Returning..." << endl;
		return;
	}
	node* lastNode = current;
	current = current->next;
	lastNode->next = NULL;
	lastNode = current;
	while(lastNode->next != NULL) {
		lastNode = lastNode->next;
	}
	lastNode->next = temp;
}

void printReverse(node* current) {

	if(current->next != NULL) {
		printReverse(current->next);
	}
	cout << current->data << " ";
}

void insertSorted(node*& current, int value) {

	node* newNode = new node;
	newNode->data = value;

	if(current == NULL || current->data > value) {
		newNode->next = current;
		current = newNode;
		return;
	}

	node* temp = current->next;
	node* prev = current;
	while(temp != NULL && temp->data < value) {
		temp = temp->next;
		prev = prev->next;
	}

	newNode->next = prev->next;
	prev->next = newNode;
}

void segregateEvenOdd(node*& current) {

	if(current == NULL) {
		cout << "The List does not contain any node! Returning..." << endl;
		return;
	}

	node* HEAD = current;	
	node* evenLast = NULL;	
	node* oddLast = NULL;
	node* oddFirst = NULL;

	if(HEAD->data % 2 == 0) {
		evenLast = HEAD;		
	}
	else {
		oddLast = HEAD;
		oddFirst = HEAD;		
	}

	while(HEAD != NULL) {

		while(HEAD != NULL && HEAD->next != NULL && HEAD->next->data % 2 == 0) {
			HEAD = HEAD->next;
			if(current->data % 2 != 0) {				
				current = HEAD;
			}
		}
		if(HEAD != NULL && HEAD->data % 2 == 0) {

			evenLast = HEAD;
			HEAD = HEAD->next;
			if(oddLast != NULL && HEAD != NULL) {
				oddLast->next = HEAD;
				oddLast = oddLast->next;
			}
			if(oddFirst == NULL) {
				oddFirst = HEAD;
			}
		}
		while(HEAD != NULL && HEAD->next != NULL && HEAD->next->data % 2 != 0) {
			HEAD = HEAD->next;
		}
		if(HEAD != NULL && HEAD->data % 2 != 0) {

			oddLast = HEAD;
			HEAD = HEAD->next;
			if(current->data % 2 != 0 && HEAD != NULL) {
				current = HEAD;
			}
			if(evenLast != NULL && HEAD != NULL) {
				evenLast->next = HEAD;
				evenLast = evenLast->next;
			}
		}
	}
	if(oddLast != NULL) {
		oddLast->next = NULL;
	}
	if(oddFirst != NULL && evenLast != NULL) {
		evenLast->next = oddFirst;
	}
}

node* addTwoLists(node* HEAD1, node* HEAD2) {

	if( HEAD1 == NULL && HEAD2 == NULL ) {
		return NULL;
	}
	if( HEAD1 == NULL ) {
		return HEAD2;
	}
	if( HEAD2 == NULL ) {
		return HEAD1;
	}

	int sum;
	int reminder;
	int carry = 0;
	node* res = NULL;
	while(HEAD1 != NULL && HEAD2 != NULL) {

		sum = HEAD1->data + HEAD2->data + carry;
		reminder = sum % 10;
		carry = sum / 10;
		append(res, reminder);
		HEAD1 = HEAD1->next;
		HEAD2 = HEAD2->next;
	}
	while(HEAD1 != NULL) {

		sum = HEAD1->data + carry;
		reminder = sum % 10;
		carry = sum / 10;
		append(res, reminder);
		HEAD1 = HEAD1->next;
	}
	while(HEAD2 != NULL) {

		sum = HEAD2->data + carry;
		reminder = sum % 10;
		carry = sum / 10;
		append(res, reminder);
		HEAD2 = HEAD2->next;
	}
	return res;
}

node* mergeSortedLists(node*& HEAD1, node*& HEAD2) {

	node* sortedHEAD = NULL;

	while(HEAD1 != NULL && HEAD2 != NULL) {
		if(HEAD1->data <= HEAD2->data) {
			append(sortedHEAD, HEAD1->data);
			HEAD1 = HEAD1->next;		
		}
		else {
			append(sortedHEAD, HEAD2->data);
			HEAD2 = HEAD2->next;
		}
	}

	while(HEAD1 != NULL) {
			append(sortedHEAD, HEAD1->data);
			HEAD1 = HEAD1->next;		
	}

	while(HEAD2 != NULL) {
			append(sortedHEAD, HEAD2->data);
			HEAD2 = HEAD2->next;
	}
	return sortedHEAD;
}

node* mergeSort(node*& HEAD) {

	if(HEAD == NULL) {
		return NULL; 
	}

	if(HEAD->next == NULL) {
		return HEAD; 
	}

	node* slowPtr = NULL;
	node* fastPtr = HEAD;

	while(fastPtr != NULL && fastPtr->next != NULL) {
		if(slowPtr == NULL) {
			slowPtr = HEAD;
		}
		else {
			slowPtr = slowPtr->next;			
		}
		fastPtr = fastPtr->next->next;
	}

/*
	if(fastPtr != NULL) {
		cout << fastPtr->data << endl;
	}
	cout << slowPtr->data << endl;
*/

	node* HEAD1 = HEAD;
	node* HEAD2 = slowPtr->next;
	slowPtr->next = NULL;
/*
	printList(HEAD1);
	printList(HEAD2);
*/
	HEAD1 = mergeSort(HEAD1);
	HEAD2 = mergeSort(HEAD2);
	node* sortedHEAD = mergeSortedLists(HEAD1, HEAD2);	
	return sortedHEAD;
}

int main() {

	node* HEAD = NULL;
/*
//	insertAfter(HEAD, 3);
//	push(HEAD, 1);
	append(HEAD, 1);
	append(HEAD, 10);
	append(HEAD, 3);
	append(HEAD, 20);
	append(HEAD, 5);
	append(HEAD, 7);
	append(HEAD, 30);
	append(HEAD, 35);
	printList(HEAD);
	deleteNode(HEAD, 30);
	printList(HEAD);
	deleteAltNodeIterative(HEAD);
	printList(HEAD);
	cout << lengthList(HEAD) << endl;
	cout << lengthListRecursive(HEAD) << endl;
	cout << search(HEAD, 30) << endl;
	cout << searchRecursive(HEAD, 30) << endl;
	cout << search(HEAD, 23) << endl;
	cout << searchRecursive(HEAD, 23) << endl;
	cout << nthNode(HEAD, 7) << endl;
	cout << nthNodeRecursive(HEAD, -1) << endl;	
	deleteThisNode(HEAD->next->next->next);
	printList(HEAD);	
	middleElementOfList(HEAD);
	cout << nthNodeFromTheEnd(HEAD, 8) << endl;
	deleteList(HEAD);
	printList(HEAD);
	cout << count(HEAD, 23) << endl;
	reverse(HEAD);
	printList(HEAD);
	HEAD->next->next->next->next->next->next->next = HEAD->next;
	detectLoop(HEAD);
	rotate(HEAD, 4);
	printList(HEAD);
	printReverse(HEAD);
	cout << endl;
	insertSorted(HEAD, -10);
	printList(HEAD);
	segregateEvenOdd(HEAD);
	node* res = addTwoLists(HEAD1, HEAD2);
	printList(res);
	HEAD = mergeSort(HEAD);
	printList(HEAD);
*/
	node* HEAD1 = NULL;
	append(HEAD1, 20);
	append(HEAD1, 4);
	append(HEAD1, 15);
	append(HEAD1, 10);
	printList(HEAD1);
	node* HEAD2 = NULL;
	append(HEAD2, 10);
	append(HEAD2, 2);
	append(HEAD2, 4);
	append(HEAD2, 8);
	printList(HEAD2);
	return 0;
}