#include <iostream>
#include <limits.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <vector>
using namespace std;

vector<int>::iterator sP;

typedef struct node {
	int data;
	int verticalLevel;
	node* left;
	node* right;
} node;

typedef struct linkedListNode {
	int data;
	linkedListNode* next;
} linkedListNode;

node* newNode(int data) {
	node* temp = new node;
	temp->data = data;
	temp->left = NULL;
	temp->right = NULL;
	return temp; 
}

linkedListNode* newLinkedListNode(int data) {
	linkedListNode* temp = new linkedListNode;
	temp->data = data;
	temp->next = NULL;
	return temp; 
}

void printList(linkedListNode* HEAD) {

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

void preorder(node* root) {

	if(root == NULL) {
		return;
	}
	cout << root->data << " ";
	preorder(root->left);
	preorder(root->right);
}

void inorder(node* root) {

	if(root == NULL) {
		return;
	}
	inorder(root->left);
	cout << root->data << " ";
	inorder(root->right);
}

void postorder(node* root) {

	if(root == NULL) {
		return;
	}
	postorder(root->left);
	postorder(root->right);
	cout << root->data << " ";
}

void printLevelOrder(node* root) {

	cout << "Level Order Traversal: ";
	if (root == NULL) {
		return;
	}

	queue<node*> holdNodes;
	holdNodes.push(root);

	while(!holdNodes.empty()) {
	
		node* temp = holdNodes.front();	
		holdNodes.pop();

		cout << temp->data << " ";

		if(temp->left) {
			holdNodes.push(temp->left);
		}
		if(temp->right) {
			holdNodes.push(temp->right);
		}
	}
	cout << endl;
}

void printReverseLevelOrder(node* root) {

	cout << "Reverse Level Order Traversal: ";
	if (root == NULL) {
		return;
	}

	node* temp;
	queue<node*> holdNodesToTraverse;
	stack<node*> holdNodesToPrint;
	holdNodesToTraverse.push(root);

	while(!holdNodesToTraverse.empty()) {
	
		temp = holdNodesToTraverse.front();	
		holdNodesToTraverse.pop();
		holdNodesToPrint.push(temp);

		if(temp->right) {
			holdNodesToTraverse.push(temp->right);
		}

		if(temp->left) {
			holdNodesToTraverse.push(temp->left);
		}
	}

	while(!holdNodesToPrint.empty()) {
		temp = holdNodesToPrint.top();	
		holdNodesToPrint.pop();
		cout << temp->data << " ";
	}
	cout << endl;
}

int size(node* root) {
/*
	Returns number of nodes in the binary tree
*/
	if(root == NULL) {
		return 0;
	}
	return 1 + size(root->left) + size(root->right);
}

int height(node* root) {
/*
	Returns height/depth of the binary tree
*/
	if(root == NULL) {
		return 0;
	}
	return max(height(root->left)+1, height(root->right)+1);
}

int maximum(node* root) {
/*
	Returns maximum key in the binary tree
*/
	if(root == NULL) {
		return INT_MIN;
	}
	int temp =  max(maximum(root->left), maximum(root->right));
	return max(temp,root->data);
}

int minimum(node* root) {
/*
	Returns minimum key in the binary tree
*/
	if(root == NULL) {
		return INT_MAX;
	}
	int temp = min(minimum(root->left), minimum(root->right));
	return min(temp,root->data);
}

bool Search(node* root, int data) {
/*
	Checks if a key exists in the binary tree
*/
	if(root == NULL) {
		return false;
	}
	else if(root->data == data) {
		return true;
	}
	return (Search(root->left,data) || Search(root->right,data));
}

int distanceFromRoot(node* root, int data) {
/*
	Returns the distance of a key from the root
	Assumptions: keys unique
	Returns -1 if key not present
*/
	if(root == NULL) {
		return -1;
	}
	
	else if(root->data == data) {
		return 0;
	}

	int temp1 = distanceFromRoot(root->left, data);
//	cout << root->data << "		" << temp << endl;
	if(temp1 == -1) {
		int temp2 = distanceFromRoot(root->right, data);
		if(temp2 == -1) {
			return -1;
		}
		else {
			return 1 + temp2;
		}
	}
	else {
		return 1 + temp1;
	}
}

void printPostOrder(int* in, int* pre, int inLength) {
/*
	Prints postorder traversal from given inorder and preorder traversals!
*/
	int i;
	for(i = 0; i < inLength; i++) {
		if (in[i] == pre[0]) {
			break;
		}
	}

	if (i != 0) {
		printPostOrder(in, pre+1 , i);
	}

	if (i != inLength-1) {
		printPostOrder(in + i + 1, pre + i + 1, inLength - i - 1);
	}
	cout << pre[0] << " ";
}

void printTopView(node* root) {

	cout << "Top view contains the nodes: ";
	if (root == NULL) {
		return;
	}

	map<int, int> topView;
	map<int, int>::iterator tV;
	queue<node*> holdNodes;
	root->verticalLevel = 0;
	holdNodes.push(root);

	while(!holdNodes.empty()) {
	
		node* temp = holdNodes.front();	
		holdNodes.pop();
//		cout << temp->data << " ";
		int verticalLevel = temp->verticalLevel;

		if(temp->left) {
			temp->left->verticalLevel = verticalLevel - 1;
			holdNodes.push(temp->left);
		}
		if(temp->right) {
			temp->right->verticalLevel = verticalLevel + 1;
			holdNodes.push(temp->right);
		}

		tV = topView.find(verticalLevel);
		if (tV == topView.end()) {
			topView[verticalLevel] = temp->data;
		}
	}

//	cout << topView.size() << endl;
	for (tV = topView.begin(); tV != topView.end(); tV++) {
		cout << tV->second << " ";
	}
	cout << endl;
}

void printSpecificLevelOrder(node* root) {
/*
	Prints a specific level order traversal of a perfect binary tree
	The order is described at: 
	http://www.geeksforgeeks.org/perfect-binary-tree-specific-level-order-traversal/
*/
	cout << "Specific Level Order Traversal: ";
	if (root == NULL) {
		return;
	}

	queue<node*> holdNodes;
	if(root->left) {
		holdNodes.push(root->left);
		holdNodes.push(root->right);
	}
	cout << root->data << " ";

	while(!holdNodes.empty()) {
	
		node* tempLeft = holdNodes.front();	
		holdNodes.pop();
		node* tempRight = holdNodes.front();	
		holdNodes.pop();

		cout << tempLeft->data << " ";
		cout << tempRight->data << " ";
		
		if(tempLeft->left) {
			holdNodes.push(tempLeft->left);
			holdNodes.push(tempRight->right);
			holdNodes.push(tempLeft->right);
			holdNodes.push(tempRight->left);
		}
	}
	cout << endl;
}

void mirror(node* root) {
	if (root == NULL) {
		return;
	}
	
	node* temp;
	mirror(root->left);
	mirror(root->right);
	temp = root->left;
	root->left = root->right;
	root->right = temp;
}	

/* WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP WIP

void reverseAlternateLevels(node* root) {
/*
	Mirrors alternate levels of a perfect binary tree
	For a better description: 
	http://www.geeksforgeeks.org/reverse-alternate-levels-binary-tree/
*\/
	if (root == NULL) {
		return;
	}

	queue<node*> holdNodes;
	node* temp;

	if(root->left) {
		holdNodes.push(root->left);
		holdNodes.push(root->right);

		temp = root->left;
		root->left = root->right;
		root->right = temp;
	}

	while(!holdNodes.empty()) {
	
		node* tempLeft = holdNodes.front();	
		holdNodes.pop();
		node* tempRight = holdNodes.front();	
		holdNodes.pop();
		
		if(tempLeft->left) {
			cout << tempLeft->data << " ";
			cout << tempRight->data << "     ";
			cout << tempLeft->left->data << " ";
			cout << tempRight->right->data << " ";
			cout << tempLeft->right->data << " ";
			cout << tempRight->left->data << "     ";

			holdNodes.push(tempLeft->left);
			holdNodes.push(tempRight->right);
			holdNodes.push(tempLeft->right);
			holdNodes.push(tempRight->left);
		
			temp = tempLeft->left;
			tempLeft->left = tempRight->right;
			tempRight->right = temp;

			temp = tempLeft->right;
			tempLeft->right = tempRight->left;
			tempRight->left = temp;

			cout << tempLeft->left->data << " ";
			cout << tempRight->right->data << " ";
			cout << tempLeft->right->data << " ";
			cout << tempRight->left->data << endl;
		}
	}
}	
*/
int checkTheNumberOfKeysUnderThisRoot(node* root, int key1, int key2) {
/*
	Initially written as a helper function to get the LCA of a binary tree but such a top down appraoch is less efficient compared to bottom up approach implemented in the function
	Returns the number of keys in the binary tress that are either key1 or key2

	Function useful under the assumption that the are keys in the binary tree are unique, in which case:

	Returns 0 if none
	Returns 1 if 1
	Returns 2 if both the keys

	The code for this particular case can be implemented using a moderately complicated conditional branching to avoid unnecessary recursive calls, as demonstrated by the commented code in the body of the function.
*/	
	if (root == NULL) {
		return 0;
	}

	if(root->data == key1 || root->data == key2) {
/*		int temp1 = checkTheNumberOfKeysUnderThisRoot(root->left, key1, key2)
		if(temp1 == 0) {
			int temp2 = checkTheNumberOfKeysUnderThisRoot(root->right, key1, key2)
			if(temp2 == 0) {
				return 1;
			}
			else {
				return 2;
			}
		}
		else {
			return 2;
		}
*/	
		return 1 + checkTheNumberOfKeysUnderThisRoot(root->left, key1, key2) + checkTheNumberOfKeysUnderThisRoot(root->right, key1, key2);
	}
	
	return checkTheNumberOfKeysUnderThisRoot(root->left, key1, key2) + checkTheNumberOfKeysUnderThisRoot(root->right, key1, key2);
}

node* lowestCommonAncestor(node* root, int key1, int key2) {
/*
	http://www.geeksforgeeks.org/lowest-common-ancestor-binary-tree-set-1/
	Assumptions: Keys present, all keys unique
*/
	if (root == NULL) {
		return NULL;
	}

	if(root->data == key1 || root->data == key2) {
		return root;
	}

	node* temp1 = lowestCommonAncestor(root->left, key1, key2);
	node* temp2 = lowestCommonAncestor(root->right, key1, key2);

	if(temp1 && temp2) {
		return root;
	}
	return (temp1? temp1 : temp2);
}

void printPathsHelper(node* root, vector<int>& storePaths) {

	if(root == NULL) {
		return;
	}

	storePaths.push_back(root->data);

	if(root->left == NULL && root->right == NULL) {
		for(sP = storePaths.begin(); sP != storePaths.end(); sP++) {
			cout << *sP << " ";
		}	
		cout << endl;
	}

	printPathsHelper(root->left, storePaths);
	printPathsHelper(root->right, storePaths);
	storePaths.pop_back();
}


void printPaths(node* root) {

	vector<int> storePaths;
	printPathsHelper(root, storePaths);
}

int distanceBetweenKeys(node* root, int key1, int key2) {
/*
	http://www.geeksforgeeks.org/find-distance-two-given-nodes/
	Assumptions: Keys present, all keys unique
*/
	if (root == NULL) {
		return -1;
	}

	if(root->data == key1) {
		return distanceFromRoot(root, key2);
	}

	if(root->data == key2) {
		return distanceFromRoot(root, key1);
	}

	int temp1 = distanceBetweenKeys(root->left, key1, key2);
	int temp2 = distanceBetweenKeys(root->right, key1, key2);
	// cout << root->data << " " << temp1 << temp2 << endl;


	if(temp1 < 0 && temp2 < 0) {
		if(Search(root, key1) && Search(root, key2)) {
			return distanceFromRoot(root, key1) + distanceFromRoot(root, key2);
		}
		else {
			return -1;
		}
	}
	return (temp2 < 0? temp1 : temp2);
}

bool areSiblings(node* root, node* a, node* b) {
/*
	Checks if two nodes have the same parent
*/
	if(root == NULL) {
		return false;
	}

	if((root->left == a && root->right == b) || (root->left == b && root->right == a)) {
		return true;
	}

	return (areSiblings(root->left, a, b) || areSiblings(root->right,a, b));
}

bool areCousins(node* root, node* a, node* b) {
/*
	Checks if two nodes have the same level but different parents
	Assumption: Keys are unique, distanceFromRoot can be modified to return node* to allow duplicate keys
*/
	if(root == NULL) {
		return false;
	}

	if((distanceFromRoot(root, a->data) == distanceFromRoot(root, b->data)) && !(areSiblings(root, a, b))) {
		return true;
	}

	return false;
}

void printKDistant(node* root, int level) {

	if(level == 1) {
		cout << root->data << " ";
		return;
	}

	if(root->left != NULL) {
		printKDistant(root->left, level-1);
	}
	if(root->right != NULL) {
		printKDistant(root->right, level-1);
	}

}

void nextRight(node* root, int key) {
/*
 	Method to find next right of given key k, it returns NULL if k is
	not present in tree or k is the rightmost node of its level 
	http://www.geeksforgeeks.org/find-next-right-node-of-a-given-key/
*/
	if (root == NULL) {
		cout << "The tree has 0 nodes! Returning..." << endl;
		return;
	}

	queue<node*> holdNodes;
	queue<int> holdNodeLevels;
	holdNodes.push(root);
	holdNodeLevels.push(1);

	while(!holdNodes.empty()) {
	
		node* temp = holdNodes.front();	
		holdNodes.pop();
		int tempLevel = holdNodeLevels.front();	
		holdNodeLevels.pop();
		
		if(temp->data == key) {
			if(holdNodes.empty() || tempLevel != holdNodeLevels.front()) {
				cout << "This is the rightmost node of its level! Returning..." << endl;
				return;				
			} 
			cout << holdNodes.front()->data << endl;
			return;				
		}
		else {
			if(temp->left) {
				holdNodes.push(temp->left);
				holdNodeLevels.push(tempLevel+1);
			}
			if(temp->right) {
				holdNodes.push(temp->right);
				holdNodeLevels.push(tempLevel+1);
			}
		}
	}
	cout << "The key does not exist in the tree! Returning..." << endl;
}

bool leavesAtSameLevelUtil(node* root, int level, int* leafLevel) {

	if(root == NULL) {
		return true;
	}

	if(root->left == NULL && root->right == NULL) {
		if(*leafLevel == 1) {
			*leafLevel = level;
			return true;
		}
		else if(*leafLevel == level) {
			return true;
		}
		else {
			return false;
		}
	}
	return leavesAtSameLevelUtil(root->left, level+1, leafLevel) && leavesAtSameLevelUtil(root->right, level+1, leafLevel);
}

bool leavesAtSameLevel(node* root) {

	int level = 1;
	int leafLevel = 1;
	return leavesAtSameLevelUtil(root, level, &leafLevel);

}

node* completeBinaryTreeFromLinkedList(linkedListNode* linkedListHEAD) {

	if(linkedListHEAD == NULL) {
		return NULL;
	}

	queue<node*> holdNodes;
	node* root = newNode(linkedListHEAD->data);
	holdNodes.push(root);
	linkedListHEAD = linkedListHEAD->next;
	node* temp;

	while(!holdNodes.empty()) {
		if(linkedListHEAD == NULL) {
			break;
		}
		temp = holdNodes.front();
		holdNodes.pop();
		temp->left = newNode(linkedListHEAD->data);
		holdNodes.push(temp->left);			
		linkedListHEAD = linkedListHEAD->next;
		if(linkedListHEAD == NULL) {
			temp->right = NULL;
			break;
		}
		temp->right = newNode(linkedListHEAD->data);
		holdNodes.push(temp->right);
		linkedListHEAD = linkedListHEAD->next;
	}
	while(!holdNodes.empty()) {
		temp = holdNodes.front();
		holdNodes.pop();		
		temp->left = NULL;
		temp->right = NULL;
	}
	return root;
}

int main() {
	node* temp = NULL;
	node* root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);
	root->left->left = newNode(4);
	root->left->right = newNode(5);
	root->left->right->right = newNode(6);
	root->left->right->right->right = newNode(7);

/*	cout << "Inorder: ";
	inorder(root);
	cout << endl;
	cout << "Preorder: ";
	preorder(root);
	cout << endl;
	cout << "Postorder: ";
	postorder(root);
	cout << endl;

	cout << "Size: ";
	cout << size(root);
	cout << endl;

	cout << "Height: ";
	cout << height(root);
	cout << endl;

	cout << "Max: ";
	cout << maximum(root);
	cout << endl;
	cout << "Min: ";
	cout << minimum(root);
	cout << endl;

	cout << "Search for 1: ";
	(Search(root,1)) ? cout << "Found!" << endl : cout << "Not Found!" << endl;
	cout << "Search for 100: ";
	(Search(root,100)) ? cout << "Found!" << endl : cout << "Not Found!" << endl;

	int in[] = {4, 2, 5, 1, 3};
	int pre[] = {1, 2, 4, 5, 3};
	int inLength = sizeof(in) / sizeof(in[0]);
	cout << "PostOrder from In and Pre: ";
	printPostOrder(in, pre, inLength);
	cout << endl;
	
	printTopView(root);
*/
	node* rootPBT = newNode(1);
	rootPBT->left = newNode(2);
	rootPBT->right = newNode(3);
	rootPBT->left->left = newNode(4);
	rootPBT->left->right = newNode(5);
	rootPBT->right->left = newNode(6);
	rootPBT->right->right = newNode(7);
/*	rootPBT->left->left->left  = newNode(8);
	rootPBT->left->left->right  = newNode(9);
    rootPBT->left->right->left  = newNode(10);
    rootPBT->left->right->right  = newNode(11);
    rootPBT->right->left->left  = newNode(12);
    rootPBT->right->left->right  = newNode(13);
    rootPBT->right->right->left  = newNode(14);
    rootPBT->right->right->right  = newNode(15);
    rootPBT->left->left->left->left  = newNode(16);
    rootPBT->left->left->left->right  = newNode(17);
    rootPBT->left->left->right->left  = newNode(18);
    rootPBT->left->left->right->right  = newNode(19);
    rootPBT->left->right->left->left  = newNode(20);
    rootPBT->left->right->left->right  = newNode(21);
    rootPBT->left->right->right->left  = newNode(22);
    rootPBT->left->right->right->right  = newNode(23);
    rootPBT->right->left->left->left  = newNode(24);
    rootPBT->right->left->left->right  = newNode(25);
    rootPBT->right->left->right->left  = newNode(26);
    rootPBT->right->left->right->right  = newNode(27);
    rootPBT->right->right->left->left  = newNode(28);
    rootPBT->right->right->left->right  = newNode(29);
    rootPBT->right->right->right->left  = newNode(30);
    rootPBT->right->right->right->right  = newNode(31);

	printSpecificLevelOrder(rootPBT);

	printLevelOrder(rootPBT);
	reverseAlternateLevels(rootPBT);
	mirror(rootPBT);
	printLevelOrder(rootPBT);

	cout << "Distance of from the root is: ";
	cout << distanceFromRoot(root, 8);
	cout << endl;

	node* lCA =  lowestCommonAncestor(rootPBT, 4, 5);
    if (lCA != NULL)
       cout << "LCA(4, 5) = " << lCA->data << endl;
    else
       cout << "Keys are not present ";

	lCA =  lowestCommonAncestor(rootPBT, 4, 6);
    if (lCA != NULL)
       cout << "LCA(4, 6) = " << lCA->data << endl;
    else
       cout << "Keys are not present ";

	lCA =  lowestCommonAncestor(rootPBT, 3, 4);
    if (lCA != NULL)
       cout << "LCA(3, 4) = " << lCA->data << endl;
    else
       cout << "Keys are not present ";

	lCA =  lowestCommonAncestor(rootPBT, 2, 4);
    if (lCA != NULL)
       cout << "LCA(2, 4) = " << lCA->data << endl;
    else
       cout << "Keys are not present ";

	lCA =  lowestCommonAncestor(rootPBT, 6, 7);
    if (lCA != NULL)
       cout << "LCA(6, 7) = " << lCA->data << endl;
    else
       cout << "Keys are not present ";

	cout << "Paths from root to leaves: " << endl;
	printPaths(root);
	cout << endl;

	cout << "Dist(4, 5) = " << distanceBetweenKeys(rootPBT, 4, 5) << endl;
    cout << "Dist(4, 6) = " << distanceBetweenKeys(rootPBT, 4, 6) << endl;
    cout << "Dist(3, 4) = " << distanceBetweenKeys(rootPBT, 3, 4) << endl;
    cout << "Dist(2, 4) = " << distanceBetweenKeys(rootPBT, 2, 4) << endl;
    cout << "Dist(8, 5) = " << distanceBetweenKeys(rootPBT, 8, 5) << endl;
    cout << "Dist(2, 3) = " << distanceBetweenKeys(rootPBT, 2, 3) << endl;

    areCousins(rootPBT, rootPBT->left->left, rootPBT->left->right)? 
    cout << "4 and 5 are cousins" << endl: cout << "4 and 5 are not cousins" << endl;

    areCousins(rootPBT, rootPBT->right->right, rootPBT->right->left->right)? 
    cout << "7 and 8 are cousins" << endl: cout << "7 and 8 are not cousins" << endl;

    areCousins(rootPBT, rootPBT->left, rootPBT->right)? 
    cout << "2 and 3 are cousins" << endl: cout << "2 and 3 are not cousins" << endl;

    areCousins(rootPBT, rootPBT->left, rootPBT->right->left)? 
    cout << "4 and 5 are cousins" << endl: cout << "4 and 5 are not cousins" << endl;

    areCousins(rootPBT, rootPBT->left->left, rootPBT->right->left)? 
    cout << "4 and 6 are cousins" << endl: cout << "4 and 6 are not cousins" << endl;

    areCousins(rootPBT, rootPBT->left->right, rootPBT->right->right)? 
    cout << "5 and 7 are cousins" << endl: cout << "5 and 7 are not cousins" << endl;

    printKDistant(rootPBT, 4);

 	nextRight(rootPBT, 1);
 	nextRight(rootPBT, 2);
 	nextRight(rootPBT, 3);
 	nextRight(rootPBT, 4);
 	nextRight(rootPBT, 5);
 	nextRight(rootPBT, 6);
 	nextRight(rootPBT, 7);
 	nextRight(rootPBT, 8);
 	nextRight(rootPBT, 9);
    leavesAtSameLevel(rootPBT)? cout << "Yes :)" << endl: cout << "No :(" << endl;
	printReverseLevelOrder(rootPBT);
 	linkedListNode* linkedListHEAD = newLinkedListNode(10);
 	linkedListHEAD->next = newLinkedListNode(12);
 	linkedListHEAD->next->next = newLinkedListNode(15);
 	linkedListHEAD->next->next->next = newLinkedListNode(25);
 	linkedListHEAD->next->next->next->next = newLinkedListNode(30);
 	linkedListHEAD->next->next->next->next->next = newLinkedListNode(36);
 	printList(linkedListHEAD);
 	
 	temp = completeBinaryTreeFromLinkedList(linkedListHEAD);
	printLevelOrder(temp);
	inorder(temp);
	cout << endl;
	preorder(temp);
	cout << endl;
	postorder(temp);
	cout << endl;
*/

    return 0;
}