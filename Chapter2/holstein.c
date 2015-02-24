/*
ID: civilte1
LANG: C
TASK: holstein
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

int cmp(const void* a, const void* b){
	return *(int*)a - *(int*)b;
}

int vitaminNeed[25];
int vitaminCount = 0;
int feedArray[25][15];
int feedCount = 0;
int queue[25];
int qCount = 25;
int queueTemp[25];
int qtCount = 0;
int vitaminRemain[25];

int findFeed(int startIndex){
	int i, j;
	int remain = 0;
	debug("findFeed - startIndex=%d\n", startIndex);
	for(j = 0; j < vitaminCount; j++){
		if(vitaminRemain[j] > 0){
			remain = 1;
		}
	}
	if(remain == 0){
		debug("findFeed - No vitamin left. %s", "\n");
		return 0;
	}
	else if(startIndex >= feedCount){
		debug("findFeed - No more feeds but still need vitamin... %s", "\n");
		return -1;
	}
	
	int min = -1;
	int types = feedCount;
	int temp;
	for(i = startIndex; i < feedCount; i++){
		
		for(j = 0; j < vitaminCount; j++){
			vitaminRemain[j] = vitaminRemain[j] - feedArray[j][i];
		}
		queueTemp[qtCount] = i;
		qtCount++;
		temp = findFeed(i+1);
		if(temp >= 0 && types > temp){
			types = temp;
			min = i;
			if(temp == 0 && qCount > qtCount){
				memcpy(queue, queueTemp, sizeof(int)*qtCount);
				qCount = qtCount;
			}
			debug("min=%d types=%d ", min, types);
		}
		for(j = 0; j < vitaminCount; j++){
			vitaminRemain[j] = vitaminRemain[j] + feedArray[j][i];
		}
		qtCount--;
	}
	if(min == -1){
		return -1;
	}
	else{
		debug("findFeed - startIndex=%d min %d, qCount %d\n", startIndex, min, qCount);
		return types+1;
	}
}


int main(void){
    FILE *fin  = fopen("holstein.in", "r");
    FILE *fout = fopen("holstein.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif

	

	fscanf(fin, "%d\n", &vitaminCount);
	debug("%d\n", vitaminCount);
	
	int i, j;
	for(i = 0; i < vitaminCount; i++){
		fscanf(fin, "%d\n", &vitaminNeed[i]);
		debug("%d ", vitaminNeed[i]);
		vitaminRemain[i] = vitaminNeed[i];
	}
	debug("%s","\n\n");
	
	
	fscanf(fin, "%d\n", &feedCount);
	debug("%d\n", feedCount);
	for(i = 0; i < feedCount; i++){
		for(j = 0; j < vitaminCount; j++){
			fscanf(fin, "%d", &feedArray[j][i]);
			debug("%d ", feedArray[j][i]);
		}
		debug("%s","\n");
	}
	debug("%s","\n");
	
	findFeed(0);
	//print out
	fprintf(fout, "%d", qCount);
	debug("%d", qCount);
	
	for(i = 0; i < qCount; i++){
		fprintf(fout, " %d", queue[i]+1);
		debug(" %d", queue[i]+1);
	}
	fprintf(fout, "\n");
	debug("%s","\n");
	
	fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

