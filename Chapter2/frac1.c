/*
ID: civilte1
LANG: C
TASK: frac1
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

#define MAX 160
#define MAXSIZE (MAX*MAX)

typedef struct _frac{
	int numerator;
	int denominator;
	int next;
}FRACTION;

FRACTION fraction[MAXSIZE];
int fracCount = 0;

int sameFraction(FRACTION* f1, FRACTION* f2){
	debug("sameFraction - %d/%d, %d/%d\n", f1->numerator, f1->denominator, f2->numerator, f2->denominator);
	return (f1->numerator*f2->denominator == f2->numerator*f1->denominator);
}

int cmp(const void* a, const void* b){
	int ret;
	FRACTION* aPtr = (FRACTION*)a;
	FRACTION* bPtr = (FRACTION*)b;
	ret = aPtr->numerator*bPtr->denominator - bPtr->numerator*aPtr->denominator;
	if(!ret){
		ret = aPtr->denominator - bPtr->denominator;
	}
	return ret;
}

int main(void){
    FILE *fin  = fopen("frac1.in", "r");
    FILE *fout = fopen("frac1.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif

	int numN;
	fscanf(fin, "%d\n", &numN);
	debug("%d\n\n", numN);
	
	int i, j;
	for(i = 0; i < numN; i++){
		for(j = 0; j <= i+1; j++){
		fraction[fracCount].denominator = i+1;
		fraction[fracCount].numerator = j;
		fracCount++;
		}
	}
	
	qsort(fraction, fracCount, sizeof(FRACTION), cmp);
	
	for(i = 0; i < fracCount; i++){
		debug("%d/%d ", fraction[i].numerator, fraction[i].denominator);
	}
	debug("%s", "\n\n");
	
	i = 0;
	int skip = 1;
	do{
		debug("index:%d ", i);
		if(sameFraction(&fraction[i], &fraction[i+skip])){
			skip++;
		}
		else{
			fprintf(fout, "%d/%d\n", fraction[i].numerator, fraction[i].denominator);
			debug("%d/%d\n", fraction[i].numerator, fraction[i].denominator);
			i = i + skip;
			skip = 1;
		}
	}while( i+skip < fracCount);
	fprintf(fout, "1/1\n");
	debug("%s", "1/1\n");
	debug("%s", "\n");
	//print out
	/*
	fprintf(fout, "%d\n", componentCount);
	debug("Component Count = %d\n", componentCount);
	*/
	
    fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

