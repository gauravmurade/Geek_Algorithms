#include <stdio.h>
#include <string.h>
using namespace std;

void naiveSearch(const char* text, const char* pattern) {

	int textLength = strlen(text);
	int patternLength = strlen(pattern);
	int i;
	int j;
	int k;

	for(i=0; i <= textLength-patternLength; i++) {
		k = i;
		for(j=0; j < patternLength; j++) {
			if(text[k] == pattern[j]) {
				k++;
			}
			else {
				break;
			}
		}
		if(j == patternLength) {
			printf("Pattern found at index %d\n", i);
		}
	}
}

int main() {
	const char* text = "AABAACAADAABAAABAA";
	const char* pattern = "AABA";
	naiveSearch(text, pattern);	
	return 0;
}