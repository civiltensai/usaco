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

int nodeCount;	//3 <= N <= 200
int height;		//1 < K < 100
int pedigrees[200][100]; //pedigrees[n][k]: n nodes with height <= k.

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
	pedigrees[1][1] = 1;
	pedigrees[3][2] = 1;
	
	int n, k;
	for(n = 5; n <= nodeCount; n=n+2){							// number of nodes
		for(k = 2; k <= height ; k++){							// height
			for(i = 0 ; i <= n-1; i++){		// numbder of nodes in left subtree
				pedigrees[n][k] += pedigrees[i][k-1]*pedigrees[n-1-i][k-1];
				debug("pedigrees[%d][%d]=%d pedigrees[%d][%d]=%d pedigrees[%d][%d]=%d\n", n, k, pedigrees[n][k], i, k-1, pedigrees[i][k-1], n-1-i, k-1, pedigrees[n-1-i][k-1]);
			}
			debug("n=%d k=%d => %d\n", n, k, pedigrees[n][k]);
		}
	}
	
	//print out
	fprintf(fout, "%d\n", pedigrees[nodeCount][height] - pedigrees[nodeCount][height-1]);
	debug("%d\n", pedigrees[nodeCount][height] - pedigrees[nodeCount][height-1]);
	
	
	fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

