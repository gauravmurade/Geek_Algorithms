#include <iostream>
using namespace std;

void TOH(int n, char from, char to, char spare) {
	if(n == 1) {
		cout << "Move disk from " << from << " to " << to << endl;
		return;
	}

	TOH(n-1, from, spare, to);
	cout << "Move disk from " << from << " to " << to << endl;
	TOH(n-1, spare, to, from);
}

void fastMultiplication(unsigned int n, int multiplier) {

	switch (multiplier) {
	case 2:
		cout << (n << 1) << endl;
		break;
	case 3:
		cout << (n << 1) + n << endl;
		break;
	case 4:
		cout << (n << 2) << endl;
		break;
	case 5:
		cout << (n << 2) + n << endl;
		break;
	case 6:
		cout << (n << 2) + (n << 1) << endl;
		break;
	case 7:
		cout << (n << 3) - n << endl;
		break;
	case 8:
		cout << (n << 3) << endl;
		break;
	case 9:
		cout << (n << 3) + n << endl;
		break;
	case 10:
		cout << (n << 3) + (n << 1) << endl;
		break;
	default:
		break;
	}
}

int power(int base, int exp) {

	if(exp == 0) {
		return 1;
	}

	if(exp == 1) {
		return base;
	}

	int result = base;
	int additionsRequired = base-1;
	int addBy = base;

	while(exp != 1) {
		while(additionsRequired != 0) {
			result += addBy;
			additionsRequired -= 1;
		}
		additionsRequired = base-1;
		addBy  = result;
		exp -= 1;
	}
	return result;
}

int powerRecursive(int base, int exp) {

	if(exp == 0) {
		return 1;
	}

	int temp = powerRecursive(base, exp-1);
	int result = 0;

	while(base != 0) {
		result += temp;
		base -= 1;
	}
	return result;
}

int main() {

/*	TOH(4, 'A', 'B', 'C');
	fastMultiplication(13, 2);
	fastMultiplication(13, 3);
	fastMultiplication(13, 4);
	fastMultiplication(13, 5);
	fastMultiplication(13, 6);
	fastMultiplication(13, 7);
	fastMultiplication(13, 8);
	fastMultiplication(13, 9);
	fastMultiplication(13, 10);
*/
	cout << powerRecursive(3, 10) << endl;	
	cout << power(3, 10) << endl;	
	return 0;
}