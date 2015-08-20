#include "iostream"
using namespace std;

void printArray(int arr[], int arrLength) {
	for(int i = 0; i < arrLength; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void bubbleSort(int intArray[], int arrLength) {
	int temp;
	for(int i = arrLength-1; i >= 1; i--) {
		for(int j = i-1; j >= 0; j--) {
			if(intArray[i] < intArray[j]) {
				temp = intArray[i];
				intArray[i] = intArray[j];
				intArray[j] = temp;
			}
		}
	}
	cout << "The bubble sorted array is: ";
	printArray(intArray, arrLength);
}

void insertionSort(int intArray[], int arrLength) {
	int temp;
	for(int i = 1; i < arrLength; i++) {
		while(i >= 1) {
			if(intArray[i] < intArray[i-1]) {
				temp = intArray[i];
				intArray[i] = intArray[i-1];
				intArray[i-1] = temp;
				i -= 1;
			}
			else {
				break;
			}
		}
	}
	cout << "The insertion sorted array is: ";
	printArray(intArray, arrLength);
}

void selectionSort(int intArray[], int arrLength) {
	int temp;
	int shortestElem;
	int shortestElemIndex;
	for(int i = 0; i < arrLength-1; i++) {
		shortestElem = intArray[i];
		shortestElemIndex = i;
		for(int j = i+1; j < arrLength; j++) {
			if(intArray[j] < shortestElem) {
				shortestElem = intArray[j];
				shortestElemIndex = j;
			}
		}
		temp = intArray[i];
		intArray[i] = intArray[shortestElemIndex];
		intArray[shortestElemIndex]= temp;	
	}
	cout << "The selection sorted array is: ";
	printArray(intArray, arrLength);
}

void quickSort(int intArray[], int start, int end) {
	int mid = (start + end) / 2;
	int i = start;
	int j = end;
	int temp;
	cout << "Median: " << intArray[mid] << endl;

	while(i < j) {
		while(intArray[i] < intArray[mid]) {
			i += 1;
		}
		while(intArray[j] > intArray[mid]) {
			j -= 1;
		}
		if(i < j) {
			cout << "Swapping: " << intArray[i] << " and " << intArray[j] << endl;
			temp = intArray[i];
			intArray[i] = intArray[j];
			intArray[j] = temp;
			i += 1;
			j -= 1;
		}
		printArray(intArray, 6);
	}


	if(start < (j-1)) {
		quickSort(intArray, start, j-1);
	}
	if((j+1) < end) {
		quickSort(intArray, j+1, end);
	}
}

void merge(int* intArray, int start, int mid, int end) {

	int i = 0;
	int j = 0;
	int k = start;

	int firstHalfSize = mid-start+1;
	int secondHalfSize = end-mid;
	int firstHalf[firstHalfSize];
	int secondHalf[secondHalfSize];

	int temp = 0;
	for(int i = start; i <= mid; i++) {
		firstHalf[temp] = intArray[i];
		temp++;
	}

	temp = 0;
	for(int i = (mid+1); i <= end; i++) {
		secondHalf[temp] = intArray[i];
		temp++;
	}

	while(i != firstHalfSize && j!= secondHalfSize) {
		if(firstHalf[i] <= secondHalf[j]) {
			intArray[k] = firstHalf[i];
			i++;
		}
		else {
			intArray[k] = secondHalf[j];
			j++;
		}
		k++;
	}

	while(i != firstHalfSize) {
		intArray[k] = firstHalf[i];
		i++;
		k++;
	}

	while(j != secondHalfSize) {
		intArray[k] = secondHalf[j];
		j++;
		k++;
	}
	}

void mergeSort(int intArray[], int start, int end) {

	if(((end - start + 1) == 0) || ((end - start + 1) == 1)) {
		return;
	}

	int mid = start + (end - start)/2;
	mergeSort(intArray, start, mid);
	mergeSort(intArray, mid+1, end);
	merge(intArray, start, mid, end);
}

int main() {
	int intArray[] = {3, 5, 2, 7, 9, 1};
	int arrLength = 6;

//	cout << "Pls enter the lenth of the array" << endl;
/*
	for(int i = 0; i < arrLength; i++) {
		cout << "Pls enter an element" << endl;
		cin >> intArray[i];
	}
*/
	cout << "The array entered is: ";
	printArray(intArray, arrLength);

//	bubbleSort(intArray, arrLength);
//	insertionSort(intArray, arrLength);
//	selectionSort(intArray, arrLength);
//  quickSort(intArray, 0, arrLength-1);
//	cout << "The quick sorted array is: ";
//	printArray(intArray, arrLength);
	mergeSort(intArray, 0, arrLength-1);
	cout << "The merge sorted array is: ";
	printArray(intArray, arrLength);

	return 0;
}