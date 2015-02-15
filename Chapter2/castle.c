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
	int x[MAX*MAX];
	int y[MAX*MAX];
}COM;

COM areas[MAX*MAX];

int cmp(const void* a, const void* b){
	COM* comAPtr = (COM*)a;
	COM* comBPtr = (COM*)b;
	return comBPtr->count - comAPtr->count;
}

void createArea(int x, int y, int* count){
	castle[x][y].visited = 1;
	//areas[castle[x][y].component].x[*count] = x;
	//areas[castle[x][y].component].y[*count] = y;
	*count = *count+1;
	debug("(%d, %d)(%d)%d->", x, y, *count, castle[x][y].wall);
	if(WESTPATH(castle[x][y].wall) && castle[x-1][y].visited == 0){
		debug("%s", "W->");
		castle[x-1][y].component = castle[x][y].component;
		createArea(x-1, y, count);
	}
	if(NORTHPATH(castle[x][y].wall) && castle[x][y-1].visited == 0){
		debug("%s", "N->");
		castle[x][y-1].component = castle[x][y].component;
		createArea(x, y-1, count);
	}
	if(EASTPATH(castle[x][y].wall) && castle[x+1][y].visited == 0){
		debug("%s", "E->");
		castle[x+1][y].component = castle[x][y].component;
		createArea(x+1, y, count);
	}
	if(SOUTHPATH(castle[x][y].wall) && castle[x][y+1].visited == 0){
		debug("%s", "S->");
		castle[x][y+1].component = castle[x][y].component;
		createArea(x, y+1, count);
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

	int componentCount = 0;
	for(j = 0; j < numN; j++){
		for(i = 0; i < numM; i++){
			if(castle[i][j].visited == 0){
				castle[i][j].component = componentCount;
				createArea(i, j, &(castle[i][j].count));
				//createArea(i, j, &areas[componentCount].count);
				componentCount++;
			}
		}
	}
	debug("%s", "\n");

	int maxRoom = 0;
	for(j = 0; j < numN; j++){
		for(i = 0; i < numM; i++){
			//debug("%2d(%2d,%2d) ", castle[i][j].wall, castle[i][j].component, areas[castle[i][j].component].count);
			debug("%2d(%2d,%2d) ", castle[i][j].wall, castle[i][j].component, castle[i][j].count);
			if(maxRoom < castle[i][j].count){
				maxRoom = castle[i][j].count;
			}
		}
		debug("%s", "\n");
	}
	
	/*
	for(i = 0; i < componentCount; i++){
		debug("%2d - Rooms=%d: ", i, areas[i].count);
		for(j = 0; j < areas[i].count; j++){
			debug("(%d, %d) ", areas[i].x[j], areas[i].y[j]);
		}
		debug("%s","\n");
	}
	*/
	
	//print out
	//The number of rooms the castle has.
	fprintf(fout, "%d\n", componentCount);
	debug("Rooms(index) = %d\n", componentCount);
	//The size of the largest room
	fprintf(fout, "%d\n", maxRoom);
	debug("Rooms(index) = %d\n", maxRoom);
	/*
	fprintf(fout, "%d\n", areas[0].count);
	debug("Rooms(index) = %d\n", areas[0].count);
	*/
	//The size of the largest room creatable by removing one wall
	//The single wall to remove to make the largest room possible
	int x = -1, y = -1;
	int wall = 'W';
	int newMax = 0;
	for(j = numN-1; j >= 0; j--){
		for(i = 0; i < numM; i++){
			debug("(%d,%d)\n", i, j);
			if( (j > 0) && !NORTHPATH(castle[i][j].wall) && castle[i][j].component != castle[i][j-1].component && newMax < castle[i][j].count + castle[i][j-1].count){
				debug("%d (%d, %d)%d %d %c->", newMax, i, j, castle[i][j].count, castle[i][j-1].count, wall);
				//debug("%d %d %d %c->", newMax, x, y, wall);
				newMax = castle[i][j].count + castle[i][j-1].count;
				x = i;
				y = j;
				wall = 'N';
				debug("%d %d %d %c\n", newMax, i, j, wall);
			}
			if( (i < 6) && !EASTPATH(castle[i][j].wall) && castle[i][j].component != castle[i+1][j].component && newMax < castle[i][j].count + castle[i+1][j].count){
				debug("%d (%d, %d)%d %d %c->", newMax, i, j, castle[i][j].count, castle[i+1][j].count, wall);
				newMax = castle[i][j].count + castle[i+1][j].count;
				x = i;
				y = j;
				wall = 'E';
				debug("%d %d %d %c\n", newMax, i, j, wall);
			}
			/*
			if( (j > 0) && !NORTHPATH(castle[i][j].wall) && castle[i][j].component != castle[i][j-1].component && newMax < areas[castle[i][j].component].count + areas[castle[i][j-1].component].count){
				debug("%d (%d, %d)%d %d %c->", newMax, i, j, areas[castle[i][j].component].count, areas[castle[i][j-1].component].count, wall);
				//debug("%d %d %d %c->", newMax, x, y, wall);
				newMax = areas[castle[i][j].component].count + areas[castle[i][j-1].component].count;
				x = i;
				y = j;
				wall = 'N';
				debug("%d %d %d %c\n", newMax, i, j, wall);
			}
			if( (i < 6) && !EASTPATH(castle[i][j].wall) && castle[i][j].component != castle[i+1][j].component && newMax < areas[castle[i][j].component].count + areas[castle[i+1][j].component].count){
				debug("%d (%d, %d)%d %d %c->", newMax, i, j, areas[castle[i][j].component].count, areas[castle[i+1][j].component].count, wall);
				newMax = areas[castle[i][j].component].count + areas[castle[i+1][j].component].count;
				x = i;
				y = j;
				wall = 'E';
				debug("%d %d %d %c\n", newMax, i, j, wall);
			}
			*/
		}
	}
	fprintf(fout, "%d\n", newMax);
	debug("newMax = %d\n", newMax);
	fprintf(fout, "%d %d %c\n", x+1, y+1, wall);
	debug("%d %d %c\n", y+1, x+1, wall);

    fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

