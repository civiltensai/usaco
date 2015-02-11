/*
ID: civilte1
LANG: C
TASK: ariprog
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

//#define _DEBUG_
#ifdef _DEBUG_
	FILE *fdebug;
	#define debug(str, ...) do{ fprintf(fdebug, str, __VA_ARGS__); printf(str, __VA_ARGS__); }while(0)
#else
	#define debug(str, ...) {;}
#endif

int sequence[25] = {0};
int sCount = 0;
int bisquares[62500] = {0};
int bisquaresDiff[62500] = {0};
int bCount = 0;
int bisquaresEntry[125000] = {0};

int cmp(const void* a, const void* b){
	return (*(int*)a - *(int*)b);
}

#ifdef _DEBUG_
void dump(){
	int i;
	debug("bCount=%d -- ", bCount);
	for(i = 0; i < bCount; i++){
		debug("%d ", bisquares[i]);
	}
	debug("%s", "\n");
}
#else
#define dump() {;}
#endif

int hasArithmeticProgression(int diff, int n, FILE* fout){
	int i, j;
	int ret = 0;
	debug("diff=%d bCount=%d\n", diff, bCount);
	for(i = bisquares[0]; i < diff; i++){
		debug("start from i=%d ---- ", i);
		int length = 0;
		//probe all to find all exist sequence with diff.
		for(j = i; j <= bisquares[bCount-1]; j = j+diff){
			if(bisquaresEntry[j]){
				debug("%d,", j);
				length++;
				if(length >= n){
					int start = j - diff*(n-1);
					fprintf(fout, "%d %d\n", start, diff);
					debug("%d %d\n", start, diff);
					ret = 1;
				}
			}
			else if(length){
				debug("(%d) ", length);
				length = 0;
			}
		}
		debug("%s", "\n");
	}
	return ret;
}


int main(void){
    FILE *fin  = fopen("ariprog.in", "r");
    FILE *fout = fopen("ariprog.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif

	
	int numberN, numberM;
	
	fscanf(fin, "%d\n%d\n", &numberN, &numberM);
	debug("N=%d M=%d\n", numberN, numberM);
	
	
	int i, j;
	for(i = 0; i <= numberM; i++){
		for(j = 0; j <= numberM; j++){
			int bisquare = i*i+j*j;
			if(!bisquaresEntry[bisquare]){
				bisquaresEntry[bisquare] = bCount;
				bisquares[bCount] = bisquare;
				bCount++;
			}
		}
	}
	
	dump();
	qsort(bisquares, bCount, sizeof(int), cmp);
	
	
	for(i = 1; i < bCount; i++){
		bisquaresDiff[i-1] = bisquares[i] - bisquares[i-1];
	}
	
	dump();
	
	int count = 0;
	for(i = 1; i <= bisquares[bCount-1]/numberN; i++){
		if(hasArithmeticProgression(i, numberN, fout))
			count++;
	}
	
	if(!count) fprintf(fout, "NONE\n");
	//debug("%d\n", count);
	
    fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

