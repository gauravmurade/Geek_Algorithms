#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

int holdLCSLength[10][10];
char holdLCS[10][10];

int holdLPSLength[10][10];
char holdLPS[10][10];

int LCS(char* X, char* Y, int m, int n) {

	int temp;
	if(holdLCSLength[m][n] != -1) {
		return holdLCSLength[m][n];
	}

	if(m < 0 || n < 0) {
		temp = 0;
	}
	else if(X[m] == Y[n]) {
		temp = 1 + LCS(X, Y, m-1, n-1);
		holdLCS[m][n] = X[m];
	}
	else {
		int temp1 = LCS(X, Y, m, n-1);
		int temp2 = LCS(X, Y, m-1, n);
		if (temp1 >= temp2) {
			temp = temp1;
		}
		else {
			temp = temp2;
		}
	}
	holdLCSLength[m][n] = temp;
	return temp;
}

int LPS(char* X, int m, int n) {

	int temp;
	if(holdLPSLength[m][n] != -1) {
		return holdLPSLength[m][n];
	}

	if(m >= strlen(X) || n < 0) {
		temp = 0;
	}
	else if(X[m] == X[n]) {
		temp = 1 + LPS(X, m+1, n-1);
		holdLPS[m][n] = X[m];
	}
	else {
		int temp1 = LPS(X, m+1, n);
		int temp2 = LPS(X, m, n-1);
		if (temp1 >= temp2) {
			temp = temp1;
		}
		else {
			temp = temp2;
		}
	}
	holdLPSLength[m][n] = temp;
	return temp;
}

void maxSubarraySum(int arr[], int arrLength) {

	int curr, max = 0;
	int maxStart;
	int maxStop;

	for(int i = 0; i < arrLength; i++) {
		if(arr[i] <= 0) {
			if(curr + arr[i] <= 0) {
				curr = 0;
				maxStart = -1;
				maxStop = -1;
			}
			else {
				curr += arr[i];
			}
		}
		else {
			if(curr > 0) {
				curr += arr[i];
				max = curr;
				maxStop = i;
			}
			else {
				curr = arr[i];
				maxStart = i;
				maxStop = i;
			}
		}
	}
	cout << max << "   " << maxStart << "   " << maxStop << endl;	
}

int main() {
/*
	for(int i=0; i<10; i++) {
		for(int j=0; j<10; j++) {
			holdLCSLength[i][j] = -1;
		}
	}

	for(int i=0; i<10; i++) {
		for(int j=0; j<10; j++) {
			holdLPSLength[i][j] = -1;
		}
	}

	char X[] = "BAGGTABT";
	char Y[] = "GXTXAYB";

	int m = strlen(X);
	int n = strlen(Y);

	cout << "Length of longest common subsequence is: " << LCS(X, Y, m-1, n-1) << endl;
	cout << "Length of longest palindromic subsequence is: " << LPS(X, 0, m-1) << endl;

	for(int i = 0; i < 7; i++) {
		for(int j = 0; j < 7; j++) {
			cout << holdLCSLength[i][j] << "    ";
		}
		cout << endl;
	}

	for(int i = 0; i < 7; i++) {
		for(int j = 0; j < 7; j++) {
			cout << holdLCS[i][j] << "    ";
		}
		cout << endl;
	}

		for(int i = 0; i < 7; i++) {
		for(int j = 0; j < 7; j++) {
			cout << holdLPSLength[i][j] << "    ";
		}
		cout << endl;
	}

	for(int i = 0; i < 7; i++) {
		for(int j = 0; j < 7; j++) {
			cout << holdLPS[i][j] << "    ";
		}
		cout << endl;
	}
*/
	int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
	int arrLength = sizeof(arr)/sizeof(arr[0]);
	maxSubarraySum(arr, arrLength);	
	return 0;
}
