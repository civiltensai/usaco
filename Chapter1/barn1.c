/*
ID: civilte1
LANG: C
TASK: barn1
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

int minfirstcmp(const void *a, const void *b)
{
	return (*(int*)a - *(int*)b);
}

int maxfirstcmp(const void *a, const void *b)
{
	return (*(int*)b - *(int*)a);
}

int stallNum[200] = {0};
int diff[200] = {0};

int main(void){
    FILE *fin  = fopen("barn1.in", "r");
    FILE *fout = fopen("barn1.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif

	int maxBoards, stallCount, occupiedCount;
	int i;
	int minLength = 0;

	fscanf(fin, "%d %d %d\n", &maxBoards, &stallCount, &occupiedCount);
	debug("%d %d %d\n", maxBoards, stallCount, occupiedCount);
	
	if(maxBoards >= occupiedCount){
		fprintf(fout, "%d\n", occupiedCount);
		debug("%d\n", minLength);
	}
	else{
		debug("stallNum%s", "\n");
		for(i = 0; i < occupiedCount; i++){
			fscanf(fin, "%d\n", &stallNum[i]);
			debug("%d ", stallNum[i]);
		}
		debug("%s", "\n");
		qsort(stallNum, occupiedCount , sizeof(stallNum[0]), minfirstcmp);
		debug("stallNum%s", "\n");
		for(i = 0; i < occupiedCount; i++){
			debug("%d ", stallNum[i]);
		}
		debug("%s", "\n");
		debug("diff%s", "\n");
		for(i = 0; i < occupiedCount; i++){
			if(i > 0){
				diff[i-1] = stallNum[i] - stallNum[i-1];
				minLength += diff[i-1];
				debug("%d ", diff[i-1]);
			}
		}
		debug("%s", "\n");
		qsort(diff, occupiedCount - 1 , sizeof(diff[0]), maxfirstcmp);
		debug("diff%s", "\n");
		for(i = 0; i < occupiedCount - 1; i++){
			debug("%d ", diff[i]);
		}
		debug("%s", "\n");
		
		for(i = 0; i < maxBoards - 1; i++){
			debug("minLength=%d -%d ", minLength, diff[i]);
	    	minLength -= diff[i];
			debug("minLength=%d -%d\n", minLength, diff[i]);
		}
		minLength += maxBoards; 
		
		fprintf(fout, "%d\n", minLength);
		debug("%d\n", minLength);
	}
	
    fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

