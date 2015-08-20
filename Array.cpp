#include <iostream>
#include <climits>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
using namespace std;

void printArray(int arr[], int arrLength) {
	for(int i = 0; i < arrLength; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void reverseArray(int arr[], int start, int end) {

	int i = start;
	int j = end;
	int temp;

	while(i < j) {
		temp = arr[i];
		arr[i++] = arr[j];
		arr[j--] = temp;
	}
}

void rotateArray(int arr[], int arrLength, int rotateLeftBy) {
/*
	Left rotation of array
	Jumbling algorithm
*/
	if(rotateLeftBy >= arrLength) {
		rotateLeftBy %= arrLength;
	}

	int i = arrLength - 1 - rotateLeftBy;
	int backupStartIndex = i;
	int backupData;
	int backupCopyIndex = arrLength - 1;
	int copyData = arr[backupCopyIndex];

	for(int k = 0; k < arrLength; k++) {
		backupData = arr[i];
		arr[i] = copyData;
		copyData = backupData;
		i -= rotateLeftBy;

		if(i < 0) {
			i = arrLength + i;
		}
		if(i == backupStartIndex) {
			i -= 1;
			backupStartIndex = i;
			backupCopyIndex -= 1;
			copyData = arr[backupCopyIndex];
		}
	}
}

void rotateArraySmart(int arr[], int arrLength, int rotateLeftBy) {

	reverseArray(arr, 0, rotateLeftBy - 1);
	reverseArray(arr, rotateLeftBy, arrLength-1);
	reverseArray(arr, 0, arrLength - 1);
}

bool doesPairExistSuchThatSumX(int arr[], int arrLength, int sum) {
/*
	Three ways of using the map :
	1. Initialize it to 0
	2. Use try catch
	3. Declare an iterator and use the find function
*/
	unordered_map<int, bool> binMap;
	int temp;

	for(int i = 0; i < arrLength; i++) {
		temp = sum - arr[i];
		try{
			if(binMap.at(temp) == true) {
				return true;
			}
		}
		catch(exception& e) {
			binMap.insert(pair<int, bool>(arr[i], true));
		}
	}
	return false;
}

void printLeaders(int arr[], int arrLength) {
/*
	An element is a leader if it is greater than all the elements to it's right
	The rightmost element is always a leader

	Traverse an array from right to left and keep track of the maximum element found!
*/
	int max = INT_MIN;

	cout << "The leaders are: ";
	for(int i = arrLength-1; i >= 0; i--) {

		if(arr[i] > max) {
			max = arr[i];
			cout << max << " ";
		}
	}
	cout << endl;
}

void printUniqueElements(int arr[], int arrLength) {
/*
	Duplicate elements are not printed
*/
	unordered_map<int, int> countMap;
	unordered_map<int, int> :: iterator cM;

	for(int i = 0; i < arrLength; i++) {
		countMap[arr[i]] += 1;
	}

	cout << "The unique elements are: ";
	for(cM = countMap.begin(); cM != countMap.end(); cM++) {
		if(cM->second == 1) {
			cout << cM->first << " ";
		}
	}
	cout << endl;
}

void printUniqueElements2(int arr[], int arrLength) {
/*
	Duplicate elements are not printed
*/
	unordered_set<int> distinctElementSet;
	unordered_set<int>:: iterator dES;

	for(int i = 0; i < arrLength; i++) {
		dES = distinctElementSet.find(arr[i]);
		if (dES == distinctElementSet.end()) {
			distinctElementSet.insert(arr[i]);
		}
		else {
			distinctElementSet.erase(arr[i]);
		}
	}

	cout << "The unique elements are: ";
	for(dES = distinctElementSet.begin(); dES != distinctElementSet.end(); dES++) {
		cout << *dES << " ";
	}
	cout << endl;
}

void printDistinctElements(int arr[], int arrLength) {
/*
	Duplicate elements are printed only once
*/
	unordered_set<int> distinctElementSet;
	unordered_set<int>:: iterator dES;

	for(int i = 0; i < arrLength; i++) {
		dES = distinctElementSet.find(arr[i]);
		if (dES == distinctElementSet.end()) {
			distinctElementSet.insert(arr[i]);
		}
	}

	cout << "The distinct elements are: ";
	for(dES = distinctElementSet.begin(); dES != distinctElementSet.end(); dES++) {
		cout << *dES << " ";
	}
	cout << endl;
}

void printTheOnlyUniqueElement(int arr[], int arrLength) {

	int XOR = arr[0];
	for(int i = 1; i < arrLength; i++) {
		XOR = XOR ^ arr[i];
	}
	cout << "The unique element is: ";
	cout << XOR << endl;
}

void productArray(int arr[], int arrLength) {
/*
	http://www.geeksforgeeks.org/a-product-array-puzzle/
*/
	int prod[arrLength];
	for(int i = 0; i < arrLength; i++) {
		prod[i] = 1;
	}
	int temp = 1;

	for(int i = 0; i < arrLength; i++) {
		prod[i] *= temp;
		temp *= arr[i];
	}

	printArray(prod, arrLength);
	temp = 1;
	for(int i = arrLength-1; i >= 0; i--) {
		prod[i] *= temp;
		temp *= arr[i];
	}

	printArray(prod, arrLength);
}

void maxDifference(int arr[], int arrLength) {
/*
	http://www.geeksforgeeks.org/maximum-difference-between-two-elements/
*/
	int diff = INT_MIN;
	int min = arr[0];
	int temp;

	for(int i = 1; i < arrLength; i++) {
		temp = arr[i] - min;
		if(temp > diff) {
			diff = temp;
		}
		if(arr[i] < min) {
			min = arr[i];
		}
	}
	cout << "The max difference is: " << diff << endl;
}

int fixedPoint(int arr[], int arrLength) {
/*
	http://www.geeksforgeeks.org/find-a-fixed-point-in-a-given-array/
*/
	int low = 0;
	int high = arrLength-1;
	int mid;

	while(low <= high) {
		mid = low + (high - low)/2;
		if(arr[mid] == mid) {
			return mid;	
		}
		else if(arr[mid] < mid) {
			low = mid + 1;
		}
		else if(arr[mid] > mid) {
			high = mid - 1;
		}
	}
	return -1;
}

bool isMajorityElement(int arr[], int arrLength, int lookFor) {
/*
	http://www.geeksforgeeks.org/check-for-majority-element-in-a-sorted-array/
*/
	int low = 0;
	int high = arrLength-1;
	int mid = low + (high - low)/2;

	if(arr[mid] != lookFor) {
		return false;
	}

	int count = 1;
	int i = mid+1;
	int j = mid-1;

	while(arr[i] == lookFor) {
		count++;
		i++;
	}
	while(arr[j] == lookFor) {
		count++;
		j--;
	}
	return count > arrLength/2;
}

int main() {
	int arr[] = {1, 2, 3, 4, 4, 4, 4};
	int arrLength = sizeof(arr)/sizeof(arr[0]);
	cout << "Array is: ";
	printArray(arr, arrLength);
/*
	reverseArray(arr, 0, arrLength-1);
	cout << "Reversed array is: ";
	printArray(arr, arrLength);

	rotateArray(arr, arrLength, 2);
	rotateArraySmart(arr, arrLength, 4);
	cout << "Rotated array is: ";
	printArray(arr, arrLength);

	cout << "Pair exists?: ";
	(doesPairExistSuchThatSumX(arr, arrLength, 12)? cout << "Yes!" << endl : cout << "No!" << endl);
	(doesPairExistSuchThatSumX(arr, arrLength, 115)? cout << "Yes!" << endl : cout << "No!" << endl);

	printLeaders(arr, arrLength);

	printUniqueElements(arr, arrLength);
	printUniqueElements2(arr, arrLength);
	printTheOnlyUniqueElement(arr, arrLength);
	printDistinctElements(arr, arrLength);
	productArray(arr, arrLength);
	maxDifference(arr, arrLength);
	cout << "The fixed point is: " << fixedPoint(arr, arrLength) << endl;
*/
	(isMajorityElement(arr, arrLength, 4)? cout << "Yes! Majority Element" << endl : cout << "No! Not a Majority Element" << endl);
	return 0;
}