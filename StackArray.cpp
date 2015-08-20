#include <iostream>
#include <limits.h>
using namespace std;

typedef struct Stack {
	int top;
	unsigned int capacity;
	int* array;
} Stack;

Stack* createStack(unsigned int capacity) {
	Stack* stack = new Stack;
	stack->capacity = capacity;
	stack->top = -1;
	stack->array = new int[capacity];
	return stack; 
}

int isFull(Stack* stack) {
	return stack->top == stack->capacity - 1;
}

int isEmpty(Stack* stack) {
	return stack->top == -1;
}

void push(Stack* stack, int item) {
	if (isFull(stack)) {
		return;
	}
	stack->array[++stack->top] = item;
}

int pop(Stack* stack) {
	if (isEmpty(stack)) {
		return INT_MIN;
	}
	return stack->array[stack->top--];
}

int peek(Stack* stack) {
	if (isEmpty(stack)) {
		return INT_MIN;
	}
	return stack->array[stack->top];
}

int main() {
	Stack* stack = createStack(5);
//	push(stack, 10);
//	push(stack, 20);
//	push(stack, 30);
//	push(stack, 40);
//	push(stack, 50);
//	push(stack, 60);
	cout << pop(stack) << endl;
	cout << peek(stack) << endl;
	
	return 0;
}
