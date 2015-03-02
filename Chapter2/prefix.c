/*
ID: civilte1
LANG: C
TASK: prefix
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define _DEBUG_
#ifdef _DEBUG_
	FILE *fdebug;
	#define debug(str, ...) do{ fprintf(fdebug, str, __VA_ARGS__); printf(str, __VA_ARGS__); fflush(fdebug);}while(0)
#else
	#define debug(str, ...) {;}
#endif
FILE *fout;

#define MAXLENGTH 200001
char primitives[201][11];
int primitiveCount = 0;
char sequence[MAXLENGTH];
int unmatchedLen[MAXLENGTH];
int sLength = 0;

#define MIN(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })


int main(void){
	FILE *fin  = fopen("prefix.in", "r");
	fout = fopen("prefix.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif
	
	
	do{
		fscanf(fin, "%s", primitives[primitiveCount]);
		debug("%s\n", primitives[primitiveCount]);
		primitiveCount++;
	}while(primitives[primitiveCount-1][0] != '.');
	primitiveCount--;
	debug("primitiveCount=%d\n", primitiveCount);
	
	char* sStart = sequence;
	debug("-----------------------------%s", "\n");
	while(fscanf(fin, "%s", sStart) != EOF){
		//debug("%s\n", sStart);
		sStart = sStart+strlen(sStart);
	}
	debug("-----------------------------%s", "\n");
	sLength = strlen(sequence);
	debug("%d\n%s\n-----------------------------\n", sLength, sequence);
	
	//init unmatchedLen[]
	int i, j;
	for(i = 0; i <= sLength; i++){
		unmatchedLen[i] = i;
	}
	
	for(j = 1; j <= sLength; j++){
		for(i = 0; i < primitiveCount; i++){
			int len = strlen(primitives[i]);
			if(len <= strlen(&(sequence[sLength - j])) && strncmp(&(sequence[sLength - j]), primitives[i], len) == 0){
				unmatchedLen[j] = MIN(unmatchedLen[j], unmatchedLen[j - len]);
			}
		}
		debug("%d - %d\n", j, unmatchedLen[j]);
	}
	
	//print out
	fprintf(fout, "%d\n", sLength - unmatchedLen[sLength]);
	debug("%d\n", sLength - unmatchedLen[sLength]);
	
	
	fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

