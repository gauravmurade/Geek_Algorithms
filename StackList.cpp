#include <iostream>
#include <stdlib.h>
#include <limits.h>
using namespace std;

typedef struct StackNode {
	int data;
	StackNode* next;
} StackNode;

StackNode* newNode(int data) {
	StackNode* stackNode = new StackNode;
	stackNode->data = data;
	stackNode->next = NULL;
	return stackNode; 
}

int isEmpty(StackNode* root) {
	return root == NULL;
}

StackNode* push(StackNode* root, int data) {
	StackNode* stackNode = newNode(data);	
//	cout << stackNode << endl;
//	cout << root << endl;
	stackNode->next = root;
	root = stackNode;
//	cout << root << endl;
	return root;
}

int pop(StackNode*& root) {
	if (isEmpty(root)) {
		return INT_MIN;
	}
	StackNode* temp = root;
	root = root->next;
	int popped = temp->data;
	free(temp);
	return popped;
}

int peek(StackNode* root) {
	if (isEmpty(root)) {
		return INT_MIN;
	}
	return root->data;
}

int main() {
	StackNode* root = NULL;
	root = push(root, 10);
	root = push(root, 20);
	root = push(root, 30);
	cout << pop(root) << endl;
	cout << peek(root) << endl;
	return 0;
}
