/*
ID: civilte1
LANG: C
TASK: sort3
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

int array[1000];
int sortedArray[1000];
int One[1000];
int Two[1000];
int Three[1000];
int count = 0;
int OneCount = 0;
int TwoCount = 0;
int ThreeCount = 0;

int cmp(const void* a, const void* b){
	return *(int*)a - *(int*)b;
}

int main(void){
    FILE *fin  = fopen("sort3.in", "r");
    FILE *fout = fopen("sort3.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif

	fscanf(fin, "%d\n", &count);
	debug("%d\n\n", count);
	
	int i;
	for(i = 0; i < count; i++){
		fscanf(fin, "%d\n", &array[i]);
		debug("%d ", array[i]);
		sortedArray[i] = array[i];
		switch(array[i]){
			case 1:
				One[OneCount] = i;
				OneCount++;
				break;
			case 2:
				Two[TwoCount] = i;
				TwoCount++;
				break;
			case 3:
				Three[ThreeCount] = i;
				ThreeCount++;
				break;
			default:
				break;
		}
	}
	debug("%s","\n");
	
	qsort(sortedArray, count, sizeof(int), cmp);
	
	
	for(i = 0; i < count; i++){
		debug("%d ", sortedArray[i]);
	}
	debug("%s","\n");
	for(i = 0; i < OneCount; i++){
		debug("%d ", One[i]);
	}
	debug("%s","\n");
	for(i = 0; i < TwoCount; i++){
		debug("%d ", Two[i]);
	}
	debug("%s","\n");
	for(i = 0; i < ThreeCount; i++){
		debug("%d ", Three[i]);
	}
	debug("%s","\n");
	
	int step = 0;
	int j;
	
	for(i = 0; i < count; i++){
		if(array[i] != sortedArray[i]){
			for(j = i+1; j < count; j++){
				if(sortedArray[i] == array[j] && array[i] == sortedArray[j]){
					array[i] = sortedArray[i];
					array[j] = sortedArray[j];
					step++;
					break;
				}
			}
		}
	}
	
	int remain = 0;
	for(i = 0; i < count; i++){
		debug("%d ", array[i]);
		if(array[i] != sortedArray[i]){
			remain++;
		}
	}
	debug("%s","\n");
	debug("step=%d\n",step);
	
	//print out
	fprintf(fout, "%d\n", step+remain*2/3);
	debug("%d\n", step+remain*2/3);
	
	fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

