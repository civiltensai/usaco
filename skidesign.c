/*
ID: civilte1
LANG: C
TASK: skidesign
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

#define MAX_ELEVATION 100
#define MAX_HEIGHT 17

int hills[MAX_ELEVATION];

int main(void){
    FILE *fin  = fopen("skidesign.in", "r");
    FILE *fout = fopen("skidesign.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif

	
	int i, j, number, height; 
	int min = 100;
	int max = 0;
	int cost = 0;
	int minCost = INT_MAX;
	
	fscanf(fin, "%d\n", &number);
	debug("%d\n", number);
	
	for(i = 0;i < number; i++){
		fscanf(fin, "%d\n", &height);
		hills[height]++;
		if(min > height){
			min = height;
		}
		if(max < height){
			max = height;
		}
	}
	
	for(i = min; i <= max-MAX_HEIGHT; i++){
		int newMin = i;
		int newMAx = i+MAX_HEIGHT;
		cost = 0;
		for(j = min; j <= max; j++){
			if(hills[j]){
				int newCost = 0;
				if(j < newMin){
					newCost = newMin - j;
				}
				else if(j > newMAx){
					newCost = j - newMAx;
				}
				cost += newCost*newCost*hills[j];
				debug("cost=%d newCost=%d hills[%d]=%d (%d, %d)\n", cost, newCost, j, hills[j], newMin, newMAx);
			}
		}
		if(minCost > cost){
			minCost = cost;
		}
	debug("%s", "\n");
	}
	
	fprintf(fout, "%d\n", minCost);
	debug("%d\n", minCost);
	
    fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

