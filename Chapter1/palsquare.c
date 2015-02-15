/*
ID: civilte1
LANG: C
TASK: palsquare
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define _DEBUG_
#ifdef _DEBUG_
	#define debug(str, ...) do{ fprintf(fdebug, str, __VA_ARGS__); printf(str, __VA_ARGS__); }while(0)
#else
	#define debug(str, ...) {;}
#endif

#define MAX 300

int numbaseB[17] = {0};
int numIndex = 0;
int baseB[17] = {0};
int baseBIndex = 0;

int main(void){
    FILE *fin  = fopen("palsquare.in", "r");
    FILE *fout = fopen("palsquare.out", "w");
#ifdef _DEBUG_
	FILE *fdebug = fopen("debug.log", "w");
#endif
    
    int numB, i, j;
    fscanf(fin, "%d\n", &numB);
    
    for(i = 1; i <= MAX; i++){
    	int square = i*i;
    	int temp = square;
    	int fail = 0;
		int number = i;
		for(numIndex = 0; numIndex < 17 && number!=0; numIndex++){
			numbaseB[numIndex] = number%numB;
			number = number/numB;
			debug("numbaseB[%d]=%d ", numIndex, numbaseB[numIndex]);
		}
    	
    	for(baseBIndex = 0; baseBIndex < 17 && temp!=0; baseBIndex++){
    		baseB[baseBIndex] = temp % numB;
    		debug("baseB[%d]=%d ", baseBIndex, baseB[baseBIndex]);
    		temp = temp / numB;
		}
		debug("\n%s\n", "---------------------------------------");
		
		for(j = 0; j < baseBIndex/2; j++){
			if(baseB[j] != baseB[baseBIndex-1-j]){
				fail = 1;
			}
		}
		if(fail == 0){
			for(j = numIndex-1; j >= 0; j--){
				if(numbaseB[j] < 10){
					fprintf(fout, "%d", numbaseB[j]);
					debug("%d", numbaseB[j]);
				}
				else{
					fprintf(fout, "%c", 'A' + numbaseB[j] - 10);
					debug("%d", 'A' + numbaseB[j] - 10);
				}
			}
			fprintf(fout, " ");
			debug("%s", " ");
			for(j = 0; j < baseBIndex; j++){
				if(baseB[j] < 10){
					fprintf(fout, "%d", baseB[j]);
					debug("%d", baseB[j]);
				}
				else{
					fprintf(fout, "%c", 'A' + baseB[j] - 10);
					debug("%d", 'A' + baseB[j] - 10);
				}
			}
			fprintf(fout, "\n");
			debug("%s", "\n");
		}
		
	}
	
    
    
    fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

