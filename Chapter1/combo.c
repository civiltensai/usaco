/*
ID: civilte1
LANG: C
TASK: combo
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


int isInTolerance(int a, int b, int c, int* key, int number){
	if((a-key[0]+number)%number > 2 && (key[0]-a+number)%number > 2){
		return 0;
	}
	if((b-key[1]+number)%number > 2 && (key[1]-b+number)%number > 2){
		return 0;
	}
	if((c-key[2]+number)%number > 2 && (key[2]-c+number)%number > 2){
		return 0;
	}
	return 1;
}

int main(void){
    FILE *fin  = fopen("combo.in", "r");
    FILE *fout = fopen("combo.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif

	int number;
	int Keys[2][3];
	int result[10][3];
	int i, j, k;
	int ok = 0;
	int count = 0;
	fscanf(fin, "%d\n", &number);
	debug("%d\n", number);
	
	fscanf(fin, "%d %d %d\n", &Keys[0][0], &Keys[0][1], &Keys[0][2]);
	fscanf(fin, "%d %d %d\n", &Keys[1][0], &Keys[1][1], &Keys[1][2]);
	
	
	for(i = 1; i <= number; i++){
		for(j = 1; j <= number; j++){
			for(k = 1; k <= number; k++){
				ok = 0;
				if(isInTolerance(i, j, k, Keys[0], number)){
					ok++;
				}
				if(isInTolerance(i, j, k, Keys[1], number)){
					ok++;
				}
				if(ok){
					debug("%d %d %d\n", i, j, k);
					count++;
				}
			}
		}
	}
	
	fprintf(fout, "%d\n", count);
	debug("%d\n", count);
	
    fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

