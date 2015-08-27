#include <iostream>
#include <math.h>
#include <limits.h>
using namespace std;
#define INF INT_MAX
#define MINF INT_MIN

int getMid(int left, int right) {
	return (left + (right - left) / 2);
}

int getLeftIndex(int root) {
	return 2*root+1;
}

int getRightIndex(int root) {
	return 2*root+2;	
}

int getParentIndex(int child) {
	return (child-1)/2;	
}

void printArray(int array[], int arrayLength) {
	for(int i=0; i < arrayLength; i++) {
		cout << array[i] << "	";
	}
		cout << endl;
}

void printEverything(int array[], int arrayLength, int* segTree, int* lazyTree) {
	cout << endl;
	printArray(array, arrayLength);
	cout << endl;
	printArray(segTree, 15);
	cout << endl;
	printArray(lazyTree, 15);
	cout << endl;
}

void updateArrayUtil(int* segTree, int* lazyTree, int nodeLeft, int nodeRight, int rangeLeft, int rangeRight, int incrementBy, int nodeIndex) {

	if(lazyTree[nodeIndex] != 0) {
		segTree[nodeIndex] += (nodeRight - nodeLeft + 1)*lazyTree[nodeIndex];
		if(nodeLeft != nodeRight) {
			lazyTree[getLeftIndex(nodeIndex)] += lazyTree[nodeIndex];
			lazyTree[getRightIndex(nodeIndex)] += lazyTree[nodeIndex];
		}
		lazyTree[nodeIndex] = 0;
	}

	if(nodeLeft > rangeRight || nodeRight < rangeLeft) {
		return;
	}

	if(rangeLeft <= nodeLeft && rangeRight >= nodeRight) {
		segTree[nodeIndex] += (nodeRight - nodeLeft + 1)*incrementBy;
		if(nodeLeft != nodeRight) {
			lazyTree[getLeftIndex(nodeIndex)] += incrementBy;
			lazyTree[getRightIndex(nodeIndex)] += incrementBy;
		}
		return;
	}

	int mid = getMid(nodeLeft, nodeRight);
	updateArrayUtil(segTree, lazyTree, nodeLeft, mid, rangeLeft, rangeRight, incrementBy, getLeftIndex(nodeIndex));
	updateArrayUtil(segTree, lazyTree, mid+1, nodeRight, rangeLeft, rangeRight, incrementBy, getRightIndex(nodeIndex));
	segTree[nodeIndex] = segTree[getLeftIndex(nodeIndex)] + segTree[getRightIndex(nodeIndex)];
}

void updateArray(int array[], int arrayLength, int* segTree, int* lazyTree, int rangeLeft, int rangeRight, int incrementBy) {

	if(rangeLeft < 0 || rangeRight >= arrayLength || rangeLeft > rangeRight) {
		cout << "Invalid range" << endl;
		return;
	}
	for(int i=rangeLeft; i <= rangeRight; i++) {
		array[i] += incrementBy;
	}
	updateArrayUtil(segTree, lazyTree, 0, arrayLength-1, rangeLeft, rangeRight, incrementBy, 0);
}

int fetchDataUtil(int* segTree, int* lazyTree, int nodeLeft, int nodeRight, int rangeLeft, int rangeRight, int nodeIndex) {

	if(lazyTree[nodeIndex] != 0) {
		segTree[nodeIndex] += (nodeRight - nodeLeft + 1)*lazyTree[nodeIndex];
		if(nodeLeft != nodeRight) {
			lazyTree[getLeftIndex(nodeIndex)] += lazyTree[nodeIndex];
			lazyTree[getRightIndex(nodeIndex)] += lazyTree[nodeIndex];
		}
		lazyTree[nodeIndex] = 0;
	}

	if(nodeLeft > rangeRight || nodeRight < rangeLeft) {
		return 0;
	}

	if(rangeLeft <= nodeLeft && rangeRight >= nodeRight) {
		return segTree[nodeIndex];
	}

	int mid = getMid(nodeLeft, nodeRight);
	return fetchDataUtil(segTree, lazyTree, nodeLeft, mid, rangeLeft, rangeRight, getLeftIndex(nodeIndex)) + 
		   fetchDataUtil(segTree, lazyTree, mid+1, nodeRight, rangeLeft, rangeRight, getRightIndex(nodeIndex));

}

int fetchData(int* segTree, int* lazyTree, int arrayLength, int left, int right) {

	if(left < 0 || right >= arrayLength || left > right) {
		cout << "Invalid range" << endl;
		return INF;
	}
	return fetchDataUtil(segTree, lazyTree, 0, arrayLength-1, left, right, 0);
}

void createSegTreeUtil(int array[], int nodeLeft, int nodeRight, int* segTree, int* lazyTree, int nodeIndex) {

	if(nodeLeft == nodeRight) {
		segTree[nodeIndex] = array[nodeLeft];
		lazyTree[nodeIndex] = 0;
		return;
	}
	int mid = getMid(nodeLeft, nodeRight);
	createSegTreeUtil(array, nodeLeft, mid, segTree, lazyTree, getLeftIndex(nodeIndex));
	createSegTreeUtil(array, mid+1, nodeRight, segTree, lazyTree, getRightIndex(nodeIndex));
	segTree[nodeIndex] = segTree[getLeftIndex(nodeIndex)] + segTree[getRightIndex(nodeIndex)];
	lazyTree[nodeIndex] = 0;
}

int* createSegTree(int array[], int arrayLength, int*& segTree, int*& lazyTree) {
	int segTreeHeight = int(ceil(log2(arrayLength)));
	int maxNumberOfNodes = int(pow(2, segTreeHeight+1)) - 1;
	segTree = new int[maxNumberOfNodes];
	lazyTree = new int[maxNumberOfNodes];
	createSegTreeUtil(array, 0, arrayLength-1, segTree, lazyTree, 0);
}

int main() {
	ios_base::sync_with_stdio(false);
	int array[] = {-1, 2, 4, 1, 7, 1, 3, 2};
	int arrayLength = sizeof(array) / sizeof(array[0]);
	int* segTree = NULL;
	int* lazyTree = NULL;
	createSegTree(array, arrayLength, segTree, lazyTree);
	printEverything(array, arrayLength, segTree, lazyTree);
	cout << "Sum of values in a given range = " << fetchData(segTree, lazyTree, arrayLength, 1, 3) << endl;
//	printEverything(array, arrayLength, segTree, lazyTree);
	updateArray(array, arrayLength, segTree, lazyTree, 0, 3, 3);
	cout << "Sum of values in a given range = " << fetchData(segTree, lazyTree, arrayLength, 1, 3) << endl;
	updateArray(array, arrayLength, segTree, lazyTree, 0, 3, 1);
	cout << "Sum of values in a given range = " << fetchData(segTree, lazyTree, arrayLength, 1, 3) << endl;
	updateArray(array, arrayLength, segTree, lazyTree, 0, 7, -2);
	cout << "Sum of values in a given range = " << fetchData(segTree, lazyTree, arrayLength, 1, 3) << endl;
	return 0;
}