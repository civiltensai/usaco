/*
ID: civilte1
LANG: C
TASK: ariprog
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define _DEBUG_
#ifdef _DEBUG_
	FILE *fdebug;
	#define debug(str, ...) do{ fprintf(fdebug, str, __VA_ARGS__); printf(str, __VA_ARGS__); }while(0)
#else
	#define debug(str, ...) {;}
#endif

int sequence[25] = {0};
int sCount = 0;
int bisquares[62500] = {0};
int bCount = 0;

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
	//int maxA = bisquares[bCount - 1] - diff*n;
	debug("diff=%d bCount=%d\n", diff, bCount);
	for(i = 0; i <= bCount; i++){
		debug("start from bisquares[%d]=%d ---- \n", i, bisquares[i]);
		sCount = 0;
		sequence[sCount] = bisquares[i];
		debug("sequence[%d]=%d->", sCount, sequence[sCount]);
		sCount++;
		for(j = 1; j < n; j++){
			int nextValue = bisquares[i]+diff*j;
			int* nextPtr = bsearch(&nextValue, bisquares, bCount, sizeof(int), cmp);
			if(!nextPtr){
				debug("%s\n", "X");
				break;
			}
			else{
				sequence[sCount] = *nextPtr;
				debug("sequence[%d]=%d->", sCount, sequence[sCount]);
				sCount++;
			}
		}
		if(sCount == n){
			debug("\nsCount=%d j=%d: ", sCount, j);
			fprintf(fout, "%d %d\n", sequence[0], diff);
			int k;
			for(k = 0; k < sCount; k++){
				debug("%2d ", sequence[k]); 
			}
			debug("%s", "\n");
			ret = 1;
		}
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
			
			bisquares[bCount] = i*i+j*j;
			bCount++;
		}
	}
	
	dump();
	qsort(bisquares, bCount, sizeof(int), cmp);
	
	dump();
	j = 0;
	i = 1;
	do{
		if(bisquares[i]==bisquares[j]){
			i++;
		}
		else{
			bisquares[j+1] = bisquares[i];
			i++;
			j++;
		}
	}while(i < bCount);
	bCount = j+1;
	dump();
	
	int count = 0;
	for(i = 1; i < bisquares[bCount-1]; i++){
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

