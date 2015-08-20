#include <stdio.h>
#include <limits.h>
using namespace std;
#define INF INT_MAX
#define MINF INT_MIN

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

class Heap {
  public :
	int* array;
	int capacity;
	int size;
  	Heap(int );
  	Heap(int*, int );
  	int parent(int );
  	int left(int );
 	int right(int );
	void printHeap();
};

Heap::Heap(int capacity) {
	this->capacity = capacity;
	this->size = 0;
	this->array = new int[capacity];
}

Heap::Heap(int array[], int arrLength) {
	this->capacity = arrLength;
	this->size = arrLength;
	this->array = new int[arrLength];
	this->array = array;
}

int Heap::parent(int index) {
	return (index - 1)/2;	
}

int Heap::left(int index) {
	return 2*index + 1;
}

int Heap::right(int index) {
	return 2*index + 2;
}

void Heap::printHeap() {
	for(int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

class MinHeap : public Heap {
  public :
	MinHeap(int capacity) : Heap(capacity) {
	}
	MinHeap(int array[], int arrLength) : Heap(array, arrLength) {
	}
 	int getMin();
  	void heapify(int );
  	int extractMin();
 	void decreaseKey(int, int);
  	void deleteKey(int );
  	void insertKey(int );	  	
};

int MinHeap::getMin() {
	return array[0];
}

void MinHeap::heapify(int index) {
	int smallest;
	int leftChild = left(index);
	int rightChild = right(index);
	if(leftChild < size && array[leftChild] < array[index]) {
		smallest = leftChild;
	}
	else {
		smallest = index;		
	}
	if(rightChild < size && array[rightChild] < array[smallest]) {
		smallest = rightChild;
	}
	if(smallest != index) {
		swap(&array[smallest], &array[index]);
		heapify(smallest);
	}
}

int MinHeap::extractMin() {
	if(size < 1) {
		printf("Heap underflow\n");
		return INF;
	}

	if(size == 1) {
		size -= 1;
		return array[0];
	}

	int minElement = array[0];
	array[0] = array[size-1];
	size -= 1;
	heapify(0);
	return minElement;
}

void MinHeap::decreaseKey(int index, int key) {

	if(key > array[index]) {
		printf("Key is larger than current key at index i\n");
		return;
	}
	array[index] = key;
	while(index > 0 && array[parent(index)] > array[index]) {
		swap(&array[parent(index)], &array[index]);	
		index = parent(index);
	}
}

void MinHeap::insertKey(int key) {
	if(size == capacity) {
		printf("Heap Underflow\n");
		return;
	}
	size += 1;
	array[size-1] = INF;
	decreaseKey(size-1, key);
}

void MinHeap::deleteKey(int index) {
	decreaseKey(index, MINF);
	extractMin();
}

MinHeap buildMinHeap(int array[], int arrLength) {
    MinHeap h(array, arrLength);
	for(int i = arrLength-1; i >= 0; i--) {
		h.heapify(i);
	}
	return h;
}

void heapSortDesc(int array[], int arrLength) {

	MinHeap h = buildMinHeap(array, arrLength);
	int temp = h.size;
	for(int i = arrLength-1; i > 0; i--) {
		swap(&array[0], &array[i]);
		h.size -= 1;
		h.heapify(0);
	}
	h.size = temp;
	h.printHeap();
}

class MaxHeap : public Heap  {
  public :
	MaxHeap(int capacity) : Heap(capacity) {
	}
	MaxHeap(int array[], int arrLength) : Heap(array, arrLength) {
	}
 	int getMax();
  	void heapify(int );
  	int extractMax();
 	void increaseKey(int, int);
  	void deleteKey(int );
  	void insertKey(int );
};


int MaxHeap::getMax() {
	return array[0];
}

void MaxHeap::heapify(int index) {
	int largest;
	int leftChild = left(index);
	int rightChild = right(index);
	if(leftChild < size && array[leftChild] > array[index]) {
		largest = leftChild;
	}
	else {
		largest = index;		
	}
	if(rightChild < size && array[rightChild] > array[largest]) {
		largest = rightChild;
	}
	if(largest != index) {
		swap(&array[largest], &array[index]);
		heapify(largest);
	}
}

int MaxHeap::extractMax() {
	if(size < 1) {
		printf("Heap underflow\n");
		return MINF;
	}

	if(size == 1) {
		size -= 1;
		return array[0];
	}

	int maxElement = array[0];
	array[0] = array[size-1];
	size -= 1;
	heapify(0);
	return maxElement;
}

void MaxHeap::increaseKey(int index, int key) {

	if(key < array[index]) {
		printf("Key is smaller than current key at index\n");
		return;
	}
	array[index] = key;
	while(index > 0 && array[parent(index)] < array[index]) {
		swap(&array[parent(index)], &array[index]);	
		index = parent(index);	
	}
}

void MaxHeap::insertKey(int key) {
	if(this->size == capacity) {
		printf("Heap overflow\n");
		return;
	}
	size += 1;
	array[size-1] = MINF;
	increaseKey(size-1, key);
}

void MaxHeap::deleteKey(int index) {
	increaseKey(index, INF);
	extractMax();
}

MaxHeap buildMaxHeap(int array[], int arrLength) {
    MaxHeap h(array, arrLength);
	for(int i = arrLength-1; i >= 0; i--) {
		h.heapify(i);
	}
	return h;
}

void heapSortAsc(int array[], int arrLength) {

	MaxHeap h = buildMaxHeap(array, arrLength);
	int temp = h.size;
	for(int i = arrLength-1; i > 0; i--) {
		swap(&array[0], &array[i]);
		h.size -= 1;
		h.heapify(0);
	}
	h.size = temp;
	h.printHeap();
}

int main()
{
    MinHeap minHeap(11);
    minHeap.insertKey(3);
    minHeap.insertKey(2);
    minHeap.insertKey(15);
    minHeap.insertKey(5);
    minHeap.insertKey(4);
    minHeap.insertKey(45);
    minHeap.deleteKey(1);
//    printf("%d removed\n", minHeap.extractMin());
//    printf("Min Value : %d\n", minHeap.getMin());
    minHeap.printHeap();
    minHeap.decreaseKey(2, 1);
    minHeap.printHeap();
    printf("Min Value : %d\n", minHeap.getMin());


    MaxHeap maxHeap(11);
    maxHeap.insertKey(3);
    maxHeap.insertKey(2);
    maxHeap.insertKey(15);
    maxHeap.insertKey(5);
    maxHeap.insertKey(4);
    maxHeap.insertKey(45);
    maxHeap.deleteKey(1);
//    printf("%d removed\n", maxHeap.extractMax());
//    printf("Max Value : %d\n", maxHeap.getMax());
    maxHeap.printHeap();
    maxHeap.increaseKey(2, 100);
    maxHeap.printHeap();
    printf("Max Value : %d\n", maxHeap.getMax());

    int array[] = {-1, 234, 1, 78, 3, 90, 7, 1};
    heapSortAsc(array, 8);    
    heapSortDesc(array, 8);
    return 0;
}