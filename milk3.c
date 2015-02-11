/*
ID: civilte1
LANG: C
TASK: milk3
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

typedef struct _state{
	int remain[3];
	int childCount;
	int childPtrIndex[6]; //the indexes of children.
}STATE;

STATE states[10000];
int stateCount = 0;
int liter[3];
int resultC[20];
int resultCount = 0;

//probe this state and further deeper (if new)
//return this state index
int probe(int* remain){
	int i, j;
	//find if there is a same state
	for(i = 0; i < stateCount; i++){
		for(j = 0; j < 3; j++){
			if(states[i].remain[j] != remain[j]){
				break;
			}
		}
		if(j == 3){
			return i;
		}
	}
	
	//no same state, add it into states
	int newStateIndex = stateCount;
	stateCount++;
	for(j = 0; j < 3; j++){
		states[newStateIndex].remain[j] = remain[j];
	}
	
	int childCount = 0;
	//pour bucket i to bucket j, for all i,j combinations
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			int diff = 0;
			if(i != j){
				//if there is milk in bucket i and space in bucket j
				if(remain[i] && (liter[j] - remain[j])){
					//if milk in bucket i is more than space in bucket j
					if(remain[i] > (liter[j] - remain[j])){
						diff = liter[j] - remain[j];
					}
					//if milk in bucket i is less than or equal to space in bucket j
					else{
						diff = remain[i];
					}
					remain[i] -= diff;
					remain[j] += diff;
					states[newStateIndex].childPtrIndex[childCount] = probe(remain);
					remain[i] += diff;
					remain[j] -= diff;
					childCount++;
				}
			}
		}
	}
	
	states[newStateIndex].childCount = childCount;
	return newStateIndex;
}

int cmp(const void*a, const void* b){
	return *(int*)a - *(int*)b;
}

int main(void){
    FILE *fin  = fopen("milk3.in", "r");
    FILE *fout = fopen("milk3.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif

	
	fscanf(fin, "%d %d %d\n", &liter[0], &liter[1], &liter[2]);
	debug("%d %d %d\n", liter[0], liter[1], liter[2]);
	
	//probe all possible states
	int remain[3] = {0, 0, liter[2]};
	probe(remain);
	
	int i, j;
	for(i = 0; i < stateCount; i++){
		debug("%2d:", i);
		for(j = 0; j < 3; j++){
			debug(" %2d", states[i].remain[j]);
		}
		debug(", child count=%d - ", states[i].childCount);
		for(j = 0; j < states[i].childCount; j++){
			debug("%d ", states[i].childPtrIndex[j]);
		}
		debug("%s", "\n");
		if(!states[i].remain[0]){
			resultC[resultCount] = states[i].remain[2];
			resultCount++;
		}
	}
	
	qsort(resultC, resultCount, sizeof(int), cmp);
	
	for(i = 0; i < resultCount; i++){
		fprintf(fout, "%d ", resultC[i]);
		debug("%d ", resultC[i]);
	}
	
    fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

