/*
ID: civilte1
LANG: C
TASK: nocows
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _DEBUG_
#ifdef _DEBUG_
	FILE *fdebug;
	#define debug(str, ...) do{ fprintf(fdebug, str, __VA_ARGS__); printf(str, __VA_ARGS__); fflush(fdebug);}while(0)
#else
	#define debug(str, ...) {;}
#endif
FILE *fout;

int degree;
int height;

int main(void){
	FILE *fin  = fopen("nocows.in", "r");
	fout = fopen("nocows.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif
	
	fscanf(fin, "%d %d", &degree, &height);
	debug("%d %d\n", degree, height);
	
	
	//print out
	//fprintf(fout, "%d\n", sLength - unmatchedLen[sLength]);
	//debug("%d\n", sLength - unmatchedLen[sLength]);
	
	
	fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

