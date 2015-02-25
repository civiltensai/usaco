/*
ID: civilte1
LANG: C
TASK: preface
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
enum roma_number{
	I = 1,
	V,
	X,
	L,
	C,
	D,
	M,
	A = 0,
	B = 0
};

typedef struct _roma{
	int one;
	int five;
	int ten;
	int visited;
	int count[10][3];
}ROMA;

ROMA digits[4] = {
	{
		one: I,
		five: V,
		ten: X,
		visited: 0
	},
	{
		one: X,
		five: L,
		ten: C,
		visited: 0
	},
	{
		one: C,
		five: D,
		ten: M,
		visited: 0
	},
	{
		one: M,
		five: A,
		ten: B,
		visited: 0
	}
};

char const romaChar[8] = {'A', 'I', 'V', 'X', 'L', 'C', 'D', 'M'};
int counts[8] = {0};

void addRomaNumbers(int n){
	int rem = 0, i = 0;
	while(n){
		rem = n%10;
		if(digits[i].visited & (1 << rem)){
			counts[digits[i].one] += digits[i].count[rem][0];
			counts[digits[i].five] += digits[i].count[rem][1];
			counts[digits[i].ten] += digits[i].count[rem][2];
		}
		else{
			switch(rem){
				case 1:
				case 2:
				case 3:
					digits[i].count[rem][0] = rem;
					break;
				case 4:
					digits[i].count[rem][0] = 1;
					digits[i].count[rem][1] = 1;
					break;
				case 5:
					digits[i].count[rem][1] = 1;
					break;
				case 6:
					digits[i].count[rem][0] = 1;
					digits[i].count[rem][1] = 1;
					break;
				case 7:
					digits[i].count[rem][0] = 2;
					digits[i].count[rem][1] = 1;
					break;
				case 8:
					digits[i].count[rem][0] = 3;
					digits[i].count[rem][1] = 1;
					break;
				case 9:
					digits[i].count[rem][0] = 1;
					digits[i].count[rem][2] = 1;
					break;
				default:
					break;
			}
			counts[digits[i].one] += digits[i].count[rem][0];
			counts[digits[i].five] += digits[i].count[rem][1];
			counts[digits[i].ten] += digits[i].count[rem][2];
			digits[i].visited = digits[i].visited | (1 << rem);
		}
		
		
		n = n/10;
		i++;
	}
}

int main(void){
    FILE *fin  = fopen("preface.in", "r");
    FILE *fout = fopen("preface.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif

	int number;

	fscanf(fin, "%d\n", &number);
	debug("%d\n", number);
	
	int i;
	for(i = 1; i <= number; i++){
		addRomaNumbers(i);
	}
	//print out
	for(i = 1; i <= M; i++){
		if(counts[i]){
			fprintf(fout, "%c %d\n", romaChar[i], counts[i]);
			debug("%c %d\n", romaChar[i], counts[i]);
		}
	}
	
	fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

