/*
ID: civilte1
LANG: C
TASK: hamming
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

int numbers[64];
int count = 0;

int hammingDistance(int a, int b){
	int aXORb = a ^ b;
	int dist = 0;
	debug("hammingDistance - a=0x%08X b=0x%08X, a XOR b =0x%08X, ", a, b, aXORb);
	while(aXORb > 0){
		dist += (aXORb & 0x1);
		aXORb >>= 1;
	}
	debug("dist=%d\n", dist);
	return dist;
}

int isHDLarger(int interger, int minDist){
	int i, dist;
	for(i = 0; i < count; i++){
		dist = hammingDistance(numbers[i], interger);
		if(dist < minDist){
			debug("isHDLarger - numbers[%d]=%d interger=%d dist=%d\n", i, numbers[i], interger, dist);
			return 0;
		}
	}
	return 1;
}

int main(void){
    FILE *fin  = fopen("hamming.in", "r");
    FILE *fout = fopen("hamming.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif

	int numN, numB, numD;

	fscanf(fin, "%d %d %d\n", &numN, &numB, &numD);
	debug("%d %d %d\n", numN, numB, numD);
	
	numbers[0] = 0;
	count++;
	
	int i = 1;
	do{
		if(isHDLarger(i, numD)){
			numbers[count] = i;
			count++;
		}
		i++;
	}while(count < numN);
	
	//print out
	for(i = 0; i < count; i++){
		if(!((i)%10) && i){
			fprintf(fout, "\n");
			debug("%s", "\n");
		}
		else if(i){
			fprintf(fout, " ");
			debug("%s", " ");
		}
		fprintf(fout, "%d", numbers[i]);
		debug("%d", numbers[i]);
	}
	
	fprintf(fout, "\n");
	debug("%s", "\n");
	
	fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

