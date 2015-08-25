#include <stdio.h>
#include <unordered_map>
using namespace std;


void printPrimes(int num1, int num2) {

  int i = 2;
  int temp;
  int currentDivisor;
  int multiplier;
  int primeCounter = 0;
  unordered_map<int, bool> isPrime;

  do {
    currentDivisor = i;
    multiplier = 2;
    temp = currentDivisor*multiplier;

    while(temp <= num2) {
      isPrime[temp] = true;
      multiplier += 1;
      temp = currentDivisor*multiplier;
    }

    for(i = currentDivisor+1; i <= 100001; i++) {
      if(isPrime[i] == false) {
        break;
      }
    }

  } while (i <= 100001);

  for(i = (num1==1 ? 2 : num1); i <= num2; i++) {
    if(isPrime[i] == false) {
      primeCounter += 1;
//      printf("%d\n", i);
    }
  }
  printf("%d\n", primeCounter);
}


int main()
{
  int num1;
  int num2;
  int numberOfInputs;

  scanf("%d", &numberOfInputs);
  for(int i = 0; i < numberOfInputs; i++)
  {
    scanf("%d", &num1);
    scanf("%d", &num2);
    printPrimes(num1, num2);
  }
  return 0;
}
