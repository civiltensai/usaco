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
int primeCount = 0;
int primeAfterAIndex = 0;

int isPrime(int p){
	int i;
	if( !(p%2) && !(p%3) ){
		return 0;
	}
	for(i = 0; i < primeCount && (prime[i]*prime[i]<=p) ; i++){
		if( !(p%prime[i]) ){
			return 0;
		}
	}
	debug("%d ", p);
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

int main(void){
    FILE *fin  = fopen("pprime.in", "r");
    FILE *fout = fopen("pprime.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif

	int numA, numB;
	fscanf(fin, "%d %d\n", &numA, &numB);
	debug("%d %d\n", numA, numB);
	
	prime[0] = 2;
	prime[1] = 3;
	primeCount = 2;
	int i;
	for(i = 5; i <= numB; i += 2){
		if(isPrime(i)){
			if(!primeAfterAIndex && (i >= numA)){
				primeAfterAIndex = primeCount;
				debug("primeAfterAIndex=%d prime=%d\n", primeAfterAIndex, i);
			}
			prime[primeCount] = i;
			primeCount++;
		}
	}
	debug("%s","\n");
	for(i = 0; i < primeCount; i++){
		debug("%d ", prime[i]);
	}
	
	for(i = primeAfterAIndex; i < primeCount; i++){
		if(isPalindrome(prime[i])){
			//print out
			fprintf(fout, "%d\n", prime[i]);
			debug("%d\n", prime[i]);
		}
	}
	
    fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

