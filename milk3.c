/*
ID: civilte1
LANG: C
TASK: milk3
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

typedef struct _state{
	int remain[3];
	int childCount;
	int childPtrIndex[6]; //the indexes of children.
}STATE;

STATE states[10000];
int stateCount = 0;
int literA, literB, literC;

void addState(int remainA, int remainB, int remainC){
	states[stateCount].remain[0] = remainA;
	states[stateCount].remain[1] = remainB;
	states[stateCount].remain[2] = remainC;
	
	int i, j;
	for(i = 0)
}

void probe(int* remains, ,int length){
	int i, j;
	//find if there is a same state
	for(i = 0; i < stateCount; i++){
		if(remainA == states[i]..remain[0] &&
		remainB == states[i]..remain[1] &&
		remainC == states[i]..remain[2]){
			//same state, skip probe
			return;
		}
		for(j = 0; j < length; j++){
			if(remains[j] != states[i]..remain[j]){
				return;
			}
		}
	}
	
	//no same state, add it into states
	
}

int main(void){
    FILE *fin  = fopen("milk3.in", "r");
    FILE *fout = fopen("milk3.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif

	
	//int remainA = 0, remainB = 0, remainC;
	
	fscanf(fin, "%d %d %d\n", &literA, &literB, &literC);
	remainC = literC;
	debug("%d %d %d\n", literA, literB, literC);
	
	//probe all possible states
	probe(0, 0, literC);
	
	if(!count) fprintf(fout, "NONE\n");
	//debug("%d\n", count);
	
    fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

