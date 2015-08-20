#include <iostream>
#include <string>
using namespace std;
int permCount = 0;

void swap(string &str, int temp1, int temp2) {

	int temp = str[temp1];
	str[temp1] = str[temp2];
	str[temp2] = temp;
}

void printAllPermutations(string str, int strLength) {

	if(strLength == 1) {
		permCount++;
		cout << str << endl;
		return;
	}

	for(int i = 0; i < strLength; i++) {
		swap(str, i, strLength - 1);
		printAllPermutations(str, strLength - 1);
		swap(str, i, strLength - 1);
	}
}

int main() {
	string str = "XYZ";
	printAllPermutations(str, str.length());
	cout << "No of perms is: " << permCount << endl;
	return 0;
}