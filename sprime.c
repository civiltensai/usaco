/*
ID: civilte1
LANG: C
TASK: sprime
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _DEBUG_
#ifdef _DEBUG_
	FILE *fdebug;
	#define debug(str, ...) do{ fprintf(fdebug, str, __VA_ARGS__); printf(str, __VA_ARGS__); }while(0)
#else
	#define debug(str, ...) {;}
#endif

#define MAXDIGITS 8
#define MAXNUMBER 10000000
#define FILTER 11111111
int prime[MAXNUMBER] = {0};
int primeSquare[MAXNUMBER] = {0};
int primeCount = 0;
int digits[5] = {1, 2, 3, 5, 7};
int highdigit[9] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
#define ADD_HIGH_DIGITS(lowDigits, N, x) ((((FILTER)%highdigit[N])/highdigit[lowDigits])*highdigit[lowDigits] + (x))

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

int main(void){
    FILE *fin  = fopen("sprime.in", "r");
    FILE *fout = fopen("sprime.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif

	int numN;
	fscanf(fin, "%d\n", &numN);
	debug("%d\n\n", numN);
	
	
	prime[0] = 2;
	primeCount = 1;
	int i, j, k, l;
	//find primes with numN digits
	i = 3;
	do{
		if(isPrime(i)){
			prime[primeCount] = i;
			primeSquare[primeCount] = i*i;
			primeCount++;
		}
		i += 2;
	}while(primeSquare[primeCount-1] < highdigit[numN + 1]);
	
	int superprime = 0;
	int intbasefive = 0;
	int temp = 0;
	int tempDigits = 0;
	do{
		temp = 0;
		tempDigits = 0;
		do{
			temp = temp*10 + digits[intbasefive%5];
			tempDigits++;
			intbasefive = intbasefive/5;
		}while(intbasefive);
		superprime = ADD_HIGH_DIGITS(tempDigits, numN, temp);
		debug("intbasefive=%d superprime=%d\n", intbasefive, superprime);
		intbasefive++;
	}while(tempDigits <= numN);
	
	//print out
	//fprintf(fout, "%d\n", palindrome);
	//debug("%d\n", palindrome);
	

    fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

