#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct node {
	int data;
	node* left;
	node* right;
}node;

void inOrder(node* root) {
	if (root->left != NULL) {
		inOrder(root->left);
	}
	cout << root->data << " ";
	if (root->right != NULL) {
		inOrder(root->right);
	}
}

node* createBST(int data){

	node* root = new node;
	root->data = data;
	root->left = NULL;
	root->right = NULL;
	return root;
}

void insert(node* root, int data){

	if(data == root->data) {
		cout << "Data to be inserted already exists in the BST. Returning ..." << endl;
		return;
	}

	if(data < root->data) {
		if(root->left == NULL) {
			root->left = createBST(data);
		}
		else {
			insert(root->left, data);
		}
	}
	else {
		if(root->right == NULL) {
			root->right = createBST(data);
		}
		else {
			insert(root->right, data);
		}
	}
}

node* search(node* root, int key) {

	if(root == NULL) {
		cout << "The key does not exist. Returning NULL..." << endl;
		return NULL;
	}

	if(key == root->data) {
		cout << "Printing from the node and returning..." << root->data << endl;
		return root;
	}

	if(key < root->data) {
			return search(root->left, key);
	}
	else {
			return search(root->right, key);
	}	
}

node* deleteNode(node* root, int key) {

	if(root == NULL) {
		return NULL;
	}

	if(key == root->data) {
		if(root->left == NULL) {

			node* temp = root->right;
			free(root);
			return temp;
			
		} else if(root->right == NULL){

			node* temp = root->left;
			free(root);
			return temp;
		}

		node* temp = root->right;
		while(temp->left != NULL) {
			temp = temp->left;
		}
		root->data = temp->data;
		root->right = deleteNode(root->right, temp->data);
	}

	if(key < root->data) {
			root->left = deleteNode(root->left, key);
	}
	else {
			root->right = deleteNode(root->right, key);
	}

	return root;
}

node* minValue(node* root) {
	if(root ==NULL) {
		cout << "The tree contains 0 nodes. Returning NULL..." << endl;
		return NULL;		
	}
	while(root->left != NULL) {
		root = root->left;
	}
	cout << "Printing from the node and returning..." << root->data << endl;
	return root;
}

void addGreaterValuesToEveryNode(node* root) {

	if(root == NULL) {
		return;
	}

	addGreaterValuesToEveryNode(root->right);
	node* inOrderSuccessor = root->right;
}

int main() {
	node* root;
	node* temp;
	root = createBST(50);
	insert(root, 30);
	insert(root, 20);
	insert(root, 40);
	insert(root, 70);
	insert(root, 60);
	insert(root, 80);
	inOrder(root);
	cout << endl;
/*
	temp = search(root, 50);
	temp = search(root, 10);
	temp = search(root, 90);
	temp = search(root, 55);

	root = deleteNode(root, 20);
	inOrder(root);
	cout << endl;
	root = deleteNode(root, 30);
	inOrder(root);
	cout << endl;
	root = deleteNode(root, 50);
	inOrder(root);
	cout << endl;

	temp = minValue(root);
*/
	addGreaterValuesToEveryNode(root);
	inOrder(root);
	cout << endl;
	return 0;
}