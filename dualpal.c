/*
ID: civilte1
LANG: C
TASK: dualpal
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define _DEBUG_
#ifdef _DEBUG_
	FILE *fdebug;
	#define debug(str, ...) do{ fprintf(fdebug, str, __VA_ARGS__); fflush(fdebug); printf(str, __VA_ARGS__); }while(0)
#else
	#define debug(str, ...) {;}
#endif

#define MAX 300
#define MAXLEN 32

int numbaseB[32] = {0};
int result[10000] = {0};

int transBase(int number, int base, int* intArray){
	int index;
	debug("number=%d base=%d\n", number, base);
	for(index = 0; index < 32 && number!=0; index++){
		intArray[index] = number%base;
		number = number/base;
		debug("intArray[%d]=%d ", index, intArray[index]);
	}
	debug("%s", "\n");
	return index;
}

void printintArray(int* intArray, int len){
	int j;
	for(j = len-1; j >= 0; j--){
		debug("%d", intArray[j]);
	}
	debug("%s", "\n");
}

/* return 1 if Palindrome */
int checkPalindrome(int* intArray, int len){
	int j;
	int isNotPalindrome = 0;
	for(j = 0; j < len/2; j++){
		if(intArray[j] != intArray[len-1-j]){
			isNotPalindrome = 1;
			break;
		}
	}
	return (isNotPalindrome==0);
}

int main(void){
    FILE *fin  = fopen("dualpal.in", "r");
    FILE *fout = fopen("dualpal.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif
    
    int numN, numS, base, number;
    int i = 0, j = 0;
    fscanf(fin, "%d %d\n", &numN, &numS);
    debug("%d %d\n", numN, numS);
    numS++;
    while(i < numN){
    	j = 0;
    	for(base = 2; (base <= 10) && (j < 2); base++){
    		int len = transBase(numS, base, numbaseB);
    		if(checkPalindrome(numbaseB, len)){
#ifdef _DEBUG_
    			printintArray(numbaseB, len);
#endif
    			j++;
    			//fprintf(fout, "%d\n", numS);
			}
		}
		if(j == 2){
			result[i] = numS;
			debug("result[%d]=%d ", i, result[i]);
			i++;
		}
		numS++;
	}
	
	for(j = 0; j < i; j++){
		fprintf(fout, "%d\n", result[j]);
	}
    
    fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

