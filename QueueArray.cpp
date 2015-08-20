#include <iostream>
#include <limits.h>
using namespace std;

typedef struct Queue {
	int front;
	int back;
	int size;
	unsigned int capacity;
	int* array;
} Queue;

Queue* createQueue(unsigned int capacity) {
	Queue* queue = new Queue;
	queue->capacity = capacity;
	queue->front = 0;
	queue->size = 0;
	queue->back = -1;
	queue->array = new int[capacity];
	return queue; 
}

int isFull(Queue* queue) {
	return queue->size == queue->capacity;
}

int isEmpty(Queue* queue) {
	return queue->size == 0;
}

void enqueue(Queue* queue, int item) {
	if (isFull(queue)) {
		return;
	}
	++queue->back;
	if (queue->back == queue->capacity) {
		queue->back = 0;
	}
	queue->size++;
	queue->array[queue->back] = item;
}

int dequeue(Queue* queue) {
	if (isEmpty(queue)) {
		return INT_MIN;
	}
	int temp = queue->array[queue->front];
	queue->front++;
	if (queue->front == queue->capacity) {
		queue->front = 0;
	}
	queue->size--;
	return temp;
}

int front(Queue* queue) {
	if (isEmpty(queue)) {
		return INT_MIN;
	}
	return queue->array[queue->front];
}

int back(Queue* queue) {
	if (isEmpty(queue)) {
		return INT_MIN;
	}
	return queue->array[queue->back];
}

int main() {
	Queue* queue = createQueue(5);
	enqueue(queue, 10);
	enqueue(queue, 20);
	enqueue(queue, 30);
	enqueue(queue, 40);
	enqueue(queue, 50);
	cout << front(queue) << endl;
	cout << back(queue) << endl;

	cout << dequeue(queue) << endl;
	cout << front(queue) << endl;
	cout << back(queue) << endl;
	return 0;
}
