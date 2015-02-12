/*
ID: civilte1
LANG: C
TASK: pprime
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define _DEBUG_
#ifdef _DEBUG_
	FILE *fdebug;
	#define debug(str, ...) do{ fprintf(fdebug, str, __VA_ARGS__); printf(str, __VA_ARGS__); }while(0)
#else
	#define debug(str, ...) {;}
#endif

#define MAXDIGITS 8
#define MAXNUMBER 1000000
int prime[MAXNUMBER] = {0};
int primeSquare[MAXNUMBER] = {0};
int primeCount = 0;
int primeAfterAIndex = 0;
int primePalindrome[MAXNUMBER] = {0};
int ppIndex = 0;

int isPrime(int p){
	int i;
	if( !(p%2) && !(p%3) ){
		return 0;
	}
	for(i = 0; i < primeCount && (primeSquare[i]<=p) ; i++){
		if( !(p%prime[i]) ){
			return 0;
		}
	}
	return 1;
}

int isPalindrome(int p){
	int i, j, digitCount = 0;
	int digits[MAXDIGITS];
	for(digitCount = 0; digitCount < MAXDIGITS && p; digitCount++){
		digits[digitCount] = p%10;
		p = p/10;
	}
	
	for(i = 0; i < digitCount/2; i++){
		if(digits[i] != digits[digitCount-i-1]){
			return 0;
		}
	}
	return 1;
}

int createPalindrome(int coreDigits, int core){
	int i;
	if(coreDigits == 0){
		for(i = 1; i < 4; i++){
			
		}
	}
}

int highdigit[8] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};
#define HIGHEST_DIGIT(x, d) ((x)/highdigit[(d)-1])
#define HALF(x, d) ((x)/highdigit[((d)/2)])
//update palindrome to next palindrome and return its digits
//palindromePtr: point to palindrome
//digits digits of current palindrome
//ex: palindrome=99; getPalindrome(&palindrome, 2); -> palindrome=101 and return 3
int getNextPalindrome(int* palindromePtr, int digits){
	int i;
	int palin = 0;
	int halfP = HALF(*palindromePtr, digits);
	int halfPDigits = (digits+1)/2;
	int nextHalfP = halfP+1;
	int nextHalfPDigits = 0;
	do{
		nextHalfP = nextHalfP/10;
		nextHalfPDigits++;
	}while(nextHalfP);
	
	//restore nextHalfP
	nextHalfP = halfP+1;
	
	//Check if carry
	if(nextHalfPDigits > halfPDigits){
		// 999(99) -> 1001(10) or 9999(99) -> 10001(100)
		digits++;
		if(!(digits%2)){
			nextHalfPDigits = halfPDigits;
			nextHalfP = nextHalfP/10;
		}
	}
	int temp = nextHalfP;
	for(i = 0; i < nextHalfPDigits; i++){
		palin = palin*10 + temp%10;
		temp = temp/10;
	}
	if(digits > 1){
		if(digits%2)
			nextHalfP = nextHalfP - nextHalfP%10;
		palin = palin + nextHalfP*highdigit[digits/2];
	}
	*palindromePtr = palin;
	return digits;
}

int main(void){
    FILE *fin  = fopen("pprime.in", "r");
    FILE *fout = fopen("pprime.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif

	int numA, numB;
	int digitsA = 0;
	fscanf(fin, "%d %d\n", &numA, &numB);
	debug("%d %d\n", numA, numB);
	
	
	prime[0] = 2;
	prime[1] = 3;
	primeCount = 2;
	int i;
	for(i = 5; i*i <= numB; i += 2){
		if(isPrime(i)){
			prime[primeCount] = i;
			primeSquare[primeCount] = i*i;
			primeCount++;
		}
	}
	
	//Create Palindrome
	int tempA = numA;
	int firstDigitA;
	int palindrome = 0;
	do{
		firstDigitA = tempA;
		palindrome = palindrome*10+tempA%10;
		tempA = tempA/10;
		digitsA++;
	}while(tempA);
	palindrome = (numA/highdigit[(digitsA+1)/2])*highdigit[(digitsA+1)/2] + palindrome%highdigit[(digitsA+1)/2];
	debug("palindrome=%d\n", palindrome);
	
	int digitsP = digitsA;
	//Check if this palindrome is larger than or equal to number A
	if(palindrome < numA){
		digitsP = getNextPalindrome(&palindrome, digitsP);
	}
	
	//Start to check if it is prime
	do{
		debug("palindrome=%d digitsP=%d\n", palindrome, digitsP);
		if(isPrime(palindrome)){ //prime
			//print out
			fprintf(fout, "%d\n", palindrome);
			debug("%d\n", palindrome);
		}
		
		//next palindrome
		digitsP = getNextPalindrome(&palindrome, digitsP);
	}while(digitsP < MAXDIGITS+1 && palindrome <= numB);
	

    fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

