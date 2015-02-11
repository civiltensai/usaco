/*
ID: civilte1
LANG: C
TASK: numtri
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

#define MAXROWS 1000

typedef struct _node{
	int wight;
	int sum;
}NODE;

NODE nodes[MAXROWS][MAXROWS];
int baseRow = 0;

int traverse(int x, int y){
	debug("traverse (%d, %d)=>%d\n", x, y, nodes[x][y].sum);
	if(x == baseRow-1 && nodes[x][y].sum == -1){
		nodes[x][y].sum = nodes[x][y].wight;
		debug("(%d, %d)=>%d\n", x, y, nodes[x][y].sum);
	}
	else if(nodes[x][y].sum == -1){
		int leftSum = traverse(x+1, y);
		int rightSum = traverse(x+1, y+1);
		int sum;
		if(leftSum > rightSum){
			sum = leftSum;
		}
		else{
			sum = rightSum;
		}
		nodes[x][y].sum = sum + nodes[x][y].wight;
		debug("(%d, %d)=>%d\n", x, y, nodes[x][y].sum);
	}
	return nodes[x][y].sum;
}

int main(void){
    FILE *fin  = fopen("numtri.in", "r");
    FILE *fout = fopen("numtri.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif


	fscanf(fin, "%d\n", &baseRow);
	debug("%d\n", baseRow);
	
	int i = 0;
	int j = 0;
	for(i = 0; i < baseRow; i++){
		for(j = 0; j <= i; j++){
			fscanf(fin, "%d", &(nodes[i][j].wight));
			nodes[i][j].sum = -1;
			debug("(%d,%d) %d %d\n", i, j, nodes[i][j].wight, nodes[i][j].sum);
		}
	}
	debug("%s","\n");
	for(i = 0; i <= baseRow; i++){
		for(j = 0; j < i; j++){
			debug("(%d,%d) %d %d\n", i, j, nodes[i][j].wight, nodes[i][j].sum);
		}
	}
	
	
	int sumPath = traverse(0, 0);
	fprintf(fout, "%d\n", sumPath);
	debug("%d\n", sumPath);
	
	
    fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

