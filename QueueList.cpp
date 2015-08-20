#include <iostream>
#include <stdlib.h>
#include <limits.h>
using namespace std;

typedef struct QueueNode {
	int data;
	QueueNode* next;
} QueueNode;

typedef struct Queue {
	QueueNode* HEAD;
	QueueNode* TAIL;
} Queue;

QueueNode* newNode(int data) {
	QueueNode* queueNode = new QueueNode;
	queueNode->data = data;
	queueNode->next = NULL;
	return queueNode; 
}

Queue* createQueue() {
	Queue* queue = new Queue;
	queue->HEAD = NULL;
	queue->TAIL = NULL;
	return queue; 
}

int isEmpty(Queue* queue) {
	return queue->HEAD == NULL && queue->TAIL == NULL;
}

void enqueue(Queue* queue, int data) {

	QueueNode* queueNode = newNode(data);
	if (isEmpty(queue)) {
		queue->HEAD = queueNode;
		queue->TAIL = queueNode;
	}
	else {
		queue->TAIL->next = queueNode;
		queue->TAIL = queueNode;
	}
}

int dequeue(Queue* queue) {
	if (isEmpty(queue)) {
		return INT_MIN;
	}

	QueueNode* temp = queue->HEAD;
	int dequeued = temp->data;
	queue->HEAD = temp->next;
	if(queue->HEAD == NULL) {
		queue->TAIL = NULL;
	}
	free(temp);
	return dequeued;
}

int front(Queue* queue) {
	if (isEmpty(queue)) {
		return INT_MIN;
	}
	return queue->HEAD->data;
}

int back(Queue* queue) {
	if (isEmpty(queue)) {
		return INT_MIN;
	}
	return queue->TAIL->data;
}

int main() {
	Queue* queue = createQueue();
	enqueue(queue, 20);
	enqueue(queue, 30);
	enqueue(queue, 40);
	cout << front(queue) << endl;
	cout << back(queue) << endl;

	cout << dequeue(queue) << endl;
	cout << front(queue) << endl;
	cout << back(queue) << endl;
	cout << dequeue(queue) << endl;
	cout << front(queue) << endl;
	cout << back(queue) << endl;
	cout << dequeue(queue) << endl;
	cout << front(queue) << endl;
	cout << back(queue) << endl;
	return 0;
}
