/*
ID: civilte1
LANG: C
TASK: crypt1
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

int inSet(int digit, int* set, int len){
	int i;
	for(i = 0; i < len; i++){
		if(digit == set[i]){
			return 1;
		}
	}
	return 0;
}

int main(void){
    FILE *fin  = fopen("crypt1.in", "r");
    FILE *fout = fopen("crypt1.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif

	int numN, i;
	int digits[10] = {0};
	int aIndex, bIndex, cIndex, dIndex, eIndex;
	int fail = 0;
	int count = 0;
	fscanf(fin, "%d\n", &numN);
	debug("%d\n", numN);
	
	for(i = 0; i < numN; i++){
		fscanf(fin, "%d", &digits[i]);
	}
	
	for(aIndex = 0; aIndex < numN; aIndex++){
		for(bIndex = 0; bIndex < numN; bIndex++){
			for(cIndex = 0; cIndex < numN; cIndex++){
				for(dIndex = 0; dIndex < numN; dIndex++){
					for(eIndex = 0; eIndex < numN; eIndex++){
						int a = digits[aIndex];
						int b = digits[bIndex];
						int c = digits[cIndex];
						int d = digits[dIndex];
						int e = digits[eIndex];
						int num1 = a*100 + b*10 + c;
						int num2 = d*10 + e;
						int p1 = e*(num1);
						int p2 = d*(num1);
						int result = num1*num2;
						if(p1>999 || p2>999 || result>9999){
							continue;
						}
						debug("num1=%d num2=%d p1=%d p2=%d result=%d\n", num1, num2, p1, p2, result);
						int temp = p1;
						fail = 0;
						while(temp && !fail){
							if(!inSet(temp%10, digits, numN)){
								fail = 1;
								break;
							}
							temp = temp/10;
						}
						temp = p2;
						while(temp && !fail){
							if(!inSet(temp%10, digits, numN)){
								fail = 1;
								break;
							}
							temp = temp/10;
						}
						temp = result;
						while(temp && !fail){
							if(!inSet(temp%10, digits, numN)){
								fail = 1;
								break;
							}
							temp = temp/10;
						}
						if(!fail){
							count++;
						}
						debug("fail=%d %d %d %d %d %d count=%d\n", fail, a, b, c, d, e, count);
					}
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

