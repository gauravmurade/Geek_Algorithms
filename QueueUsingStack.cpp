#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <stack>
using namespace std;

typedef struct Queue {
	stack<int> s1;
	stack<int> s2;
} Queue;

Queue* createQueue() {
	Queue* queue = new Queue;
	return queue; 
}

bool isEmpty(Queue* queue) {
	return queue->s1.empty() && queue->s2.empty();
}

void enqueue(Queue* queue, int data) {
	queue->s1.push(data);
}

int dequeue(Queue* queue) {
	if (isEmpty(queue)) {
		return INT_MIN;
	}

	int temp;
	if(queue->s2.empty()) {
		while(!queue->s1.empty()) {
			temp = queue->s1.top();
			queue->s2.push(temp);
			queue->s1.pop();			
		}
	}

	temp = queue->s2.top();
	queue->s2.pop();
	return temp;
}

int dequeueImplicitStack(Queue* queue) {
	if (queue->s1.empty()) {
		return INT_MIN;
	}

	int temp;
	temp = queue->s1.top();
	queue->s1.pop();	

	if(queue->s1.empty()) {
		return temp;
	}

	int result = dequeueImplicitStack(queue);	
	queue->s1.push(temp);
	return result;

}

int main() {
	Queue* queue = createQueue();
	enqueue(queue, 20);
	enqueue(queue, 30);
	enqueue(queue, 40);
	cout << dequeueImplicitStack(queue) << endl;
	cout << dequeueImplicitStack(queue) << endl;
	cout << dequeueImplicitStack(queue) << endl;
	cout << dequeueImplicitStack(queue) << endl;
	return 0;
}
