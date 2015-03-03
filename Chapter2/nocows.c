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

#define MIN(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

//#define MOD %9901
#define MOD ;
int nodeCount;	//3 <= N <= 200
int height;		//1 < K < 100
unsigned long long pedigrees[200][100]; //pedigrees[n][k]: n nodes with height = k.

int main(void){
	FILE *fin  = fopen("nocows.in", "r");
	fout = fopen("nocows.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif
	
	fscanf(fin, "%d %d", &nodeCount, &height);
	debug("%d %d\n", nodeCount, height);
	
	int i, j;
	for(i = 0; i < nodeCount; i++){
		for(j = 0; j < nodeCount; j++){
			pedigrees[i][j] = 0;
		}
	}
	int n, k;
	for(k = 1; k <= height ; k++){
		pedigrees[1][k] = 1;
	}
	
	//pedigrees[3][2] = 1;
	
	for(n = 3; n <= nodeCount; n=n+2){									// number of nodes
		for(k = 1; k <= height ; k++){									// height
			for(i = 1 ; i < n-1; i=i+2){		// numbder of nodes in left subtree
				pedigrees[n][k] = (pedigrees[n][k]+pedigrees[i][k-1]*pedigrees[n-1-i][k-1]) MOD;
				//pedigrees[n][k] = (pedigrees[n][k] + pedigrees[i][k-1]*right*2) MOD;
				///debug("pedigrees[%d][%d]=%d pedigrees[%d][%d]=%d right=%d\n", n, k, pedigrees[n][k], i, k-1, pedigrees[i][k-1], right);
				debug("pedigrees[%d][%d]=%lld pedigrees[%d][%d]=%lld pedigrees[%d][%d]=%lld\n", n, k, pedigrees[n][k], i, k-1, pedigrees[i][k-1], n-1-i, k-1, pedigrees[n-1-i][k-1]);
			}
			if(((n-1)/2)%2 == 1){
				pedigrees[n][k] = pedigrees[n][k] - pedigrees[(n-2)/2][k-1]*pedigrees[(n-2)/2][k-1];
			}
			//debug("n=%d k=%d => %d\n", n, k, pedigrees[n][k]);
			debug("n=%d k=%d => %lld\n", n, k, pedigrees[n][k]);
		}
	}
	
	//print out
	fprintf(fout, "%d\n", pedigrees[nodeCount][height]);
	debug("%d\n", pedigrees[nodeCount][height]);
	debug("%d\n", pedigrees[nodeCount][height] % 9901);
	
	
	fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

