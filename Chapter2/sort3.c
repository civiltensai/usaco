/*
ID: civilte1
LANG: C
TASK: sort3
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

int array[1000];
int sortedArray[1000];
int count = 0;

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
		debug("%d\n", array[i]);
		sortedArray[i] = array[i];
	}
	debug("%s","\n");
	
	qsort(sortedArray, count, sizeof(int), cmp);
	
	
	for(i = 0; i < count; i++){
		debug("%d\n", sortedArray[i]);
	}
	
	//print out
	//fprintf(fout, "1/1\n");
	//debug("%s", "1/1\n");
	
	fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

