/*
ID: civilte1
LANG: C
TASK: subset
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


int main(void){
    FILE *fin  = fopen("subset.in", "r");
    FILE *fout = fopen("subset.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif

	int number;

	fscanf(fin, "%d\n", &number);
	debug("%d\n", number);
	
	int i;
	int allOne = (1 << number) - 1;
	int count = 0;
	for(i = 1; i <= allOne/2; i++){
		int temp = i;
		int sum[2] = {(number+1)*number/2, 0};
		int print[40] = {0};
		int printIndex = 0;
		while(temp){
			if(temp%2){
				sum[1] += (printIndex+1);
				sum[0] -= (printIndex+1);
			}
			print[printIndex] = temp%2;
			printIndex++;
			temp = (temp >> 1);
		}
		if(sum[0] == sum[1]){
			count++;
			int j;
			for(j = 0; j < number; j++){
				debug("%d ", print[j]);
			}
			debug("%s","\n");
		}
	}
	//print out
	fprintf(fout, "%d\n", count);
	debug("%d\n", count);
	
	fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

