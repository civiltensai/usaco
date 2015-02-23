/*
ID: civilte1
LANG: C
TASK: castle
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

#define WESTPATH(x) (!((x) & 0x1))
#define NORTHPATH(x) (!((x) & 0x2))
#define EASTPATH(x) (!((x) & 0x4))
#define SOUTHPATH(x) (!((x) & 0x8))

typedef struct _node{
	int x;
	int y;
	int component;
	int visited;
	int count;
	int wall; //W: 0x1; N: 0x2; E: 0x4; S: 0x8
}NODE;

#define MAX 50
NODE castle[MAX][MAX];

typedef struct _component{
	int count;
}COM;

COM areas[MAX*MAX];
int componentCount = 0;

int cmp(const void* a, const void* b){
	COM* comAPtr = (COM*)a;
	COM* comBPtr = (COM*)b;
	return comBPtr->count - comAPtr->count;
}

void createArea(int x, int y){
	castle[x][y].visited = 1;
	//areas[castle[x][y].component].x[*count] = x;
	//areas[castle[x][y].component].y[*count] = y;
	areas[componentCount].count++;
	debug("(%d, %d)(%d)%d->", x, y, areas[componentCount].count, castle[x][y].wall);
	if(WESTPATH(castle[x][y].wall) && castle[x-1][y].visited == 0){
		debug("%s", "W->");
		castle[x-1][y].component = castle[x][y].component;
		createArea(x-1, y);
	}
	if(NORTHPATH(castle[x][y].wall) && castle[x][y-1].visited == 0){
		debug("%s", "N->");
		castle[x][y-1].component = castle[x][y].component;
		createArea(x, y-1);
	}
	if(EASTPATH(castle[x][y].wall) && castle[x+1][y].visited == 0){
		debug("%s", "E->");
		castle[x+1][y].component = castle[x][y].component;
		createArea(x+1, y);
	}
	if(SOUTHPATH(castle[x][y].wall) && castle[x][y+1].visited == 0){
		debug("%s", "S->");
		castle[x][y+1].component = castle[x][y].component;
		createArea(x, y+1);
	}
}

int main(void){
    FILE *fin  = fopen("castle.in", "r");
    FILE *fout = fopen("castle.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif

	int numM, numN;
	fscanf(fin, "%d %d\n", &numM, &numN);
	debug("%d %d\n\n", numM, numN);
	
	int i, j;
	
	for(j = 0; j < numN; j++){
		for(i = 0; i < numM; i++){
			fscanf(fin, "%d", &(castle[i][j].wall));
			castle[i][j].visited = 0;
			castle[i][j].component = -1;
			castle[i][j].x = i;
			castle[i][j].y = j;
			debug("%2d ", castle[i][j].wall);
		}
		debug("%s", "\n");
	}
	debug("%s", "\n");
	debug("%s", "\n");
	
	debug("%s", "  ");
	for(i = 0; i < numM; i++){
		debug("%2d", i+1);
	}
	debug("%s", "\n");
	for(j = 0; j < numN*2; j++){
		if(!(j%2)){
			debug("%2d ", j/2+1);
		}
		else{
			debug("%s", "   ");
		}
		for(i = 0; i < numM; i++){
			int x = i, y = j/2;
			if(!(j%2)){
				debug("%s","o");
				if(EASTPATH(castle[x][y].wall)){
					debug("%s", "-");
				}
				else{
					debug("%s", " ");
				}
			}
			else{
				if(SOUTHPATH(castle[x][y].wall)){
					debug("%s", "| ");
				}
				else{
					debug("%s", "  ");
				}
			}
		}
		debug("%s", "\n");
	}

	int maxRoom = 0;
	for(j = 0; j < numN; j++){
		for(i = 0; i < numM; i++){
			if(castle[i][j].visited == 0){
				castle[i][j].component = componentCount;
				createArea(i, j);
				debug("Component %2d Count=%d\n", castle[i][j].component, areas[castle[i][j].component].count);
				if(maxRoom < areas[castle[i][j].component].count){
					maxRoom = areas[castle[i][j].component].count;
				}
				componentCount++;
			}
		}
	}
	debug("%s", "\n");
	
	//print out
	//The number of rooms the castle has.
	fprintf(fout, "%d\n", componentCount);
	debug("Component Count = %d\n", componentCount);
	//The size of the largest room
	fprintf(fout, "%d\n", maxRoom);
	debug("Max Rooms = %d\n", maxRoom);
	
	//The size of the largest room creatable by removing one wall
	//The single wall to remove to make the largest room possible
	int x = -1, y = -1;
	int wall = 'W';
	int newMax = 0;
	for(i = 0; i < numM; i++){
		for(j = numN-1; j >= 0; j--){
			debug("(%d,%d)\n", i, j);
			if( (j > 0) && !NORTHPATH(castle[i][j].wall) && castle[i][j].component != castle[i][j-1].component && newMax < areas[castle[i][j].component].count + areas[castle[i][j-1].component].count){
				debug("%d (%d, %d)%d %d %c->", newMax, i, j, areas[castle[i][j].component].count, areas[castle[i][j-1].component].count, wall);
				//debug("%d %d %d %c->", newMax, x, y, wall);
				newMax = areas[castle[i][j].component].count + areas[castle[i][j-1].component].count;
				x = i;
				y = j;
				wall = 'N';
				debug("%d %d %d %c\n", newMax, i, j, wall);
			}
			// i < numM-1 to avoid last column 
			if( (i < numM-1) && !EASTPATH(castle[i][j].wall) && castle[i][j].component != castle[i+1][j].component && newMax < areas[castle[i][j].component].count + areas[castle[i+1][j].component].count){
				debug("%d (%d, %d)%d %d %c->", newMax, i, j, areas[castle[i][j].component].count, areas[castle[i+1][j].component].count, wall);
				newMax = areas[castle[i][j].component].count + areas[castle[i+1][j].component].count;
				x = i;
				y = j;
				wall = 'E';
				debug("%d %d %d %c\n", newMax, i, j, wall);
			}
		}
	}
	fprintf(fout, "%d\n", newMax);
	debug("newMax = %d\n", newMax);
	fprintf(fout, "%d %d %c\n", y+1, x+1, wall);
	debug("%d %d %c\n", y+1, x+1, wall);

    fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

