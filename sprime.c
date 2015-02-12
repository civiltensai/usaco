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
int sprime[MAXNUMBER] = {0};
int sprimeIndex = 0;
int prime[MAXNUMBER] = {0};
int primeSquare[MAXNUMBER] = {0};
int primeDigitsIndex[MAXDIGITS+1] = {0};
int digits = 0;
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

void findNDigitsSprime(int n, int* startIndex, int* endIndex){
	debug("n=%d ", n);
	if(n <= sdigits){
		*startIndex = sPrimeDigitsIndex[n-1]; 
		*endIndex = sPrimeDigitsIndex[n];
		debug("start=%d end=%d\n", *startIndex, *endIndex);
	}
	else{
		int startN_1, endN_1;
		int i, j;
		
		findNDigitsSprime(n-1, &startN_1, &endN_1);
		debug("n(%d)-1 %d %d\n", n, startN_1, endN_1);
		for(i = startN_1; i <= endN_1; i++){
			for(j = 1; j < 10; j+=2){ //append 1,3,5,7,9
				int sp = sprime[i]*10 + j;
				if(isPrime(sp)){
					sprime[sprimeIndex] = sp;
					if(sp > highdigit[sdigits]){
						sPrimeDigitsIndex[sdigits] = sprimeIndex;
						sdigits++;
					}
					else{
						sPrimeDigitsIndex[sdigits] = sprimeIndex+1;
					}
					debug("sp=%d sprimeIndex=%d sdigits=%d\n", sp, sprimeIndex, sdigits);
					sprimeIndex++;
				}
			}
		}
		*startIndex = endN_1+1;
		*endIndex = sprimeIndex-1;
		debug("start=%d end=%d\n", *startIndex, *endIndex);
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
	primeDigitsIndex[digits] = 0;
	sprime[0] = 2;
	sprimeIndex++;
	digits++;
	sPrimeDigitsIndex[sdigits] = -1;
	sPrimeDigitsIndex[sdigits+1] = 0;
	sdigits++;
	
	int i, j, k, l;
	int startIndex = 0;
	int endIndex = 0;
	//find primes with numN digits
	i = 3;
	do{
		if(isPrime(i)){
			prime[primeCount] = i;
			primeSquare[primeCount] = i*i;
			if(i > highdigit[digits]){
				primeDigitsIndex[digits] = primeCount;
				digits++;
			}
			if(isSuperPrime(i)){
				sprime[sprimeIndex] = i;
				debug("%s[%d] ", "superprime:", sprimeIndex);
				if(i > highdigit[sdigits]){
					sPrimeDigitsIndex[sdigits] = sprimeIndex;
					debug("-sdigits=%d sprimeIndex=%d(%d)-", sdigits, sPrimeDigitsIndex[sdigits], sPrimeDigitsIndex[sdigits+1]);
					sdigits++;
				}
				else{
					sPrimeDigitsIndex[sdigits] = sprimeIndex+1;
				}
				sprimeIndex++;
			}
			debug("%d %d %d sdigits=%d %d(%d) %d\n", prime[primeCount], primeSquare[primeCount], digits, sdigits, sPrimeDigitsIndex[sdigits-1], sPrimeDigitsIndex[sdigits], sprime[sPrimeDigitsIndex[sdigits-1]]);
			primeCount++;
		}
		i += 2;
	}while(primeSquare[primeCount-1] < highdigit[numN]);
	
	debug("%s", "---------");
	for(i = 0; i < sdigits+1; i++){
		debug("%dsprime[%d]=%d ", i, sPrimeDigitsIndex[i], sprime[sPrimeDigitsIndex[i]]);
	}
	debug("%s", "\n");
	
	
	int start, end;
	findNDigitsSprime(numN, &start, &end);
	debug("start=%d end=%d\n", start, end);
	
	for(i = start; i <= end; i++){
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

