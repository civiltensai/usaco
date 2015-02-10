/*
ID: civilte1
LANG: C
TASK: wormhole
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


typedef struct _pos{
	int x;
	int y;
	int warmholeIndex;
	int nextXIndex;
	int next;
	int pre;
}POS;
POS pos[12];

int count = 0;
int all = 0;

int isInfinit(int number){
	int i;
	for(i = 0; i < number; i++){
		if(pos[i].nextXIndex != -1){
			int next = pos[i].nextXIndex;
			do{
				next = pos[next].warmholeIndex;
				if(next == i){
					return 1;
				}
				next = pos[next].nextXIndex;
			}while(next != -1);
		}
	}
	return 0;
}

#ifdef _DEBUG_
void dump(int n){
	int i;
	for(i = 0; i < n; i++){
		debug("(%d,%d) next=%d pre=%d nextXIndex=%d warmholeIndex=%d\n", pos[i].x, pos[i].y, pos[i].next, pos[i].pre, pos[i].nextXIndex, pos[i].warmholeIndex);
	}
	debug("%s","\n");
}
#else
#define dump(x) {;}
#endif

void checkAllPerm(int posIndex, int n){
	int i;
	debug("checkAllPerm %d\n", posIndex);
	if(posIndex == -1){
		if(isInfinit(n)){
			dump(n);
			count++;
		}
		all++;
	}
	else{
		for(i = pos[posIndex].next; i < n && i != -1; i=pos[i].next){
			if(i != -1 && pos[posIndex].warmholeIndex == -1 && pos[i].warmholeIndex == -1){
				pos[posIndex].warmholeIndex = i;
				pos[i].warmholeIndex = posIndex;
				
				pos[pos[i].pre].next=pos[i].next;
				pos[pos[i].next].pre=pos[i].pre;
				
				checkAllPerm(pos[posIndex].next, n);
				
				if(pos[i].next != -1){
					pos[pos[i].next].pre=i;
				}
				pos[pos[i].pre].next=i;
				
				pos[posIndex].warmholeIndex = -1;
				pos[i].warmholeIndex = -1;
			}
		}
	}
}

int cmpX(const void* a, const void* b){
	POS* pos1 = (POS*)a;
	POS* pos2 = (POS*)b;
	int diffX = pos1->x - pos2->x;
	int diffY = pos1->y - pos2->y;
	if(diffY){
		return diffY;
	}
	else{
		return diffX;
	}
}

int main(void){
    FILE *fin  = fopen("wormhole.in", "r");
    FILE *fout = fopen("wormhole.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif

	
	int i, number;
	
	fscanf(fin, "%d\n", &number);
	debug("%d\n", number);
	
	for(i = 0; i < number; i++){
		fscanf(fin, "%d %d\n", &pos[i].x, &pos[i].y);
		pos[i].warmholeIndex = -1;
		pos[i].next = -1;
		pos[i].pre = -1;
		pos[i].nextXIndex = -1;
		debug("%d %d\n", pos[i].x, pos[i].y);
	}
	
	qsort(pos, number, sizeof(POS), cmpX);
	
	debug("%s","\n");
	for(i = 1; i < number; i++){
		if(pos[i].y == pos[i-1].y){
			pos[i-1].nextXIndex = i;
		}
		pos[i-1].next = i;
	}
	for(i = 0; i < number-1; i++){
		pos[i+1].pre = i;
	}
	debug("%s","sorted\n");
	for(i = 0; i < number; i++){
		debug("%d %d next=%d pre=%d nextXIndex=%d warmholeIndex=%d\n", pos[i].x, pos[i].y, pos[i].next, pos[i].pre, pos[i].nextXIndex, pos[i].warmholeIndex);
	}
	
	checkAllPerm(0, number);
	fprintf(fout, "%d\n", count);
	debug("%d %d\n", count, all);
	
    fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

