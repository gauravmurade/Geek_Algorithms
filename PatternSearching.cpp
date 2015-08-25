#include <stdio.h>
#include <string.h>
#include <limits.h>
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
	printf("\n");
}

void rabinKarp(const char* text, const char* pattern, int primeNumber, int radix) {

	int textLength = strlen(text);
	int patternLength = strlen(pattern);
	int textHash = 0;
	int patternHash = 0;
	int i;
	int j;
	int h = 1;

	for(i=0; i < patternLength-1; i++) {
		h = (h*radix) % primeNumber;
	}

	for(i=0; i < patternLength; i++) {
		textHash 	= (textHash*radix + text[i]) % primeNumber;
		patternHash = (patternHash*radix + pattern[i]) % primeNumber;
	}

	for(i=0; i <= (textLength-patternLength); i++) {
		if(textHash == patternHash) {
			for(j=0; j < patternLength; j++) {
				if(text[i+j] != pattern[j]) {
					break;
				}
			}
			if(j == patternLength) {
				printf("Pattern found at index %d \n", i);
			}
		}
		if(i < (textLength-patternLength)) {
			textHash = (radix*(textHash - text[i]*h) + text[i+patternLength]) % primeNumber;			

		}
		if(textHash < 0) {
			textHash += primeNumber;
		}
	}
	printf("\n");
}

void knuthMorrisPrattPreProcessArray(int* preArray, const char* pattern, int patternLength) {
/*
	a b c d a b c e a b a b c d
	0 0 0 0 1 2 3 0 1 2 1 2 3 4
*/

	int matchUpto = 0;
	int patternRunner = 1;
	preArray[0] = 0;
	while(patternRunner < patternLength) {
		if(pattern[matchUpto] == pattern[patternRunner]) {
			preArray[patternRunner] = matchUpto + 1;
			matchUpto++;
			patternRunner++;
		}
		else {
			if(matchUpto == 0) {
 				preArray[patternRunner] = 0;
				patternRunner++;
			}
			else {
				matchUpto = preArray[matchUpto-1];
			}
		}
	}
/*
	for(i=0; i < patternLength; i++) {
		printf("%d ", preArray[i]);
	}
	printf("\n");
*/
}



void knuthMorrisPratt(const char* text, const char* pattern) {
	int textLength = strlen(text);
	int patternLength = strlen(pattern);
	int* preArray = new int[patternLength];
	knuthMorrisPrattPreProcessArray(preArray, pattern, patternLength);

	int textRunner = 0;
	int matchUpto = 0;
	while(textRunner < textLength) {
		if(pattern[matchUpto] == text[textRunner]) {
			textRunner++;
			matchUpto++;
			if(matchUpto == patternLength) {
				printf("Pattern found at index %d \n", textRunner-patternLength);
				matchUpto = preArray[matchUpto-1];
			}
		}
		else {
			if(matchUpto == 0) {
				textRunner++;
			}
			else {
				matchUpto = preArray[matchUpto-1];
			}			
		}
	}
	printf("\n");
}

int main() {
	const char* text = "AABAACAADAABAAABAA";
	const char* pattern = "AABA";
	naiveSearch(text, pattern);
	rabinKarp(text, pattern, 101, 256);
	knuthMorrisPratt(text, pattern);
	return 0;
}