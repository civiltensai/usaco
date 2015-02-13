/*
ID: civilte1
LANG: C
TASK: sprime
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
int sprime[10000] = {0};
int sprimeIndex = 0;
int prime[MAXNUMBER] = {0};
int primeSquare[MAXNUMBER] = {0};
int sPrimeDigitsIndex[MAXDIGITS+1] = {0};
int sdigits = 0;
int primeCount = 0;
int highdigit[9] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
#define FILTER 11111111
#define ADD_HIGH_DIGITS(lowDigits, N, x) ((((FILTER)%highdigit[N])/highdigit[lowDigits])*highdigit[lowDigits] + (x))

int cmp(const void* a, const void* b){
	return *(int*)a - *(int*)b;
}

int isPrime(int p){
	int i;
	if(p < 3){
		return !(p%2);
	}
	else if( !(p%2) && !(p%3) ){
		return 0;
	}
	for(i = 0; i < primeCount && (primeSquare[i]<=p) ; i++){
		if( !(p%prime[i]) ){
			return 0;
		}
	}
	return 1;
}

//p must be a prime
int isSuperPrime(int p){
	int temp = p/10;
	if(!(p/10)){
		return 1;
	}
	if(bsearch(&temp, sprime, sprimeIndex, sizeof(int), cmp)){
		return 1;
	}
	return 0;
}

void findNDigitsSprime(int n, int* startIndex){
	debug("n=%d ", n);
	if(n < sdigits+1){
		*startIndex = sPrimeDigitsIndex[n-1]; 
		debug("start=%d\n", *startIndex);
	}
	else{
		int startN_1;
		int i, j;
		
		findNDigitsSprime(n-1, &startN_1);
		sPrimeDigitsIndex[n-1] = sprimeIndex;
		debug("n(%d)-1 startN_1=%d sprimeIndex=%d highdigit[n-1]=%d\n", n, startN_1, sprimeIndex, highdigit[n-1] );
		for(i = startN_1; sprime[i] < highdigit[n-1] && i < sprimeIndex; i++){
			//debug("sprime[%d]=%d\n", i, sprime[i]);
			for(j = 1; j < 10; j+=2){ //append 1,3,5,7,9
				int sp = sprime[i]*10 + j;
				//debug("i=%d sp=%d\n", i, sp);
				if(isPrime(sp)){
					sprime[sprimeIndex] = sp;
					debug("sp=%d sprimeIndex=%d\n", sp, sprimeIndex);
					sprimeIndex++;
				}
			}
		}
		sdigits++;
		sPrimeDigitsIndex[n] = sprimeIndex;
		*startIndex = sPrimeDigitsIndex[n-1];
		debug("start=%d sprimeIndex=%d sdigits=%d\n", *startIndex, sprimeIndex, sdigits);
	}
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
	sprime[0] = 2;
	sprimeIndex++;
	sPrimeDigitsIndex[0] = 0; //index=0: 1 digit, index=1: 2 digits, ...
	sdigits = 1;              //sdigits=0: 1 digit, sdigits=1: 2 digits, ...
	
	int i, j, k, l;
	int startIndex = 0;
	int endIndex = 0;
	//find primes with numN digits
	i = 3;
	do{
		if(isPrime(i)){
			prime[primeCount] = i;
			primeSquare[primeCount] = i*i;
			if(isSuperPrime(i)){
				sprime[sprimeIndex] = i;
				debug("%s[%d] ", "superprime:", sprimeIndex);
				if(i >= highdigit[sdigits]){
					sPrimeDigitsIndex[sdigits] = sprimeIndex;
					sdigits++;
				}
				sprimeIndex++;
			}
			primeCount++;
		}
		i += 2;
	}while(primeSquare[primeCount-1] < highdigit[numN] || prime[primeCount-1] < highdigit[numN/2 + 1]);
	
	debug("%s\n", "sprime---------");
	for(i = 0; i < sprimeIndex; i++){
		debug("sprime[%d]=%d ", i, sprime[i]);
	}
	debug("sprimeIndex=%d---------\n", sprimeIndex);
	
	int start, end;
	findNDigitsSprime(numN, &start);
	debug("start=%d\n", start);
	
	for(i = start; sprime[i] < highdigit[numN] && i < sprimeIndex; i++){
		fprintf(fout, "%d\n", sprime[i]);
		debug("%d\n", sprime[i]);
	}
	
	
	/*
	for(i = startIndex; i <= endIndex; i++){
		int p = prime[i];
		//debug("p=%d\n", p);
		do{
			if(!isPrime(p)){
				break;
			}
			p = p/10;
		}while(p);
		
		if(!p){
			fprintf(fout, "%d\n", prime[i]);
			debug("%d ", prime[i]);
		}
	}
	*/
	
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

