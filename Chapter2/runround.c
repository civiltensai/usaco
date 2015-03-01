/*
ID: civilte1
LANG: C
TASK: runround
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

int number;
int count;
int digit[10];
int digits = 0;
int visit[10];
int unique[10];
int isUnique = 1;
int hasZero = 0;


int makeDigit(int n){
	int index = 0;
	isUnique = 1;
	hasZero = 0;
	int i;
	for(i =0; i < 10; i++){
		digit[i] = 0;
		visit[i] = 0;
		unique[i] = 0;
	}
	while(n){
		digit[index] = n%10;
		visit[index] = 0;
		if(unique[digit[index]] == 0){
			unique[digit[index]] = 1;
		}
		else{
			isUnique = 0;
		}
		if(digit[index] == 0){
			hasZero = 1;
		}
		debug("%d ", digit[index]);
		index++;
		n = n/10;
	}
	debug(" - index=%d\n", index);
	return index;
}

//If not RR, return distance to the next posible number
int isRR(int n){
	digits = makeDigit(n);
	
	int i, digitSum = 0;
	int add = 0;
	//If a number is RR, the sum of its all digits should be divisible by the count of its digits.
	for(i = 0; i < digits; i++){
		digitSum += digit[i];
	}
	if(hasZero){
		for(i = digits-1; i >= 0; i--){
			add = add*10;
			if(digit[i] == 0){
				add = add + 1;
			}
		}
		return add;
	}
	if(isUnique == 0){
		return 1;
	}
	add = (digits - digitSum%digits)%digits;
	debug("isRR - digitSum=%d add=%d\n", digitSum, add);
	if(add){
		return add;
	}
	else{
		int nextIndex = digits-1;
		debug("isRR - nextIndex=%d", nextIndex);
		for(i = 0; i < digits && visit[nextIndex] == 0; i++){
			visit[nextIndex] = 1;
			nextIndex = (nextIndex + 9*digits - digit[nextIndex])%digits;
			debug(" %d", nextIndex);
		}
		debug("%s", "\n");
		if(nextIndex == digits-1 && i == digits){
			return 0;
		}
		else{
			return (add==0)? digits:add;
		}
	}
}

int main(void){
    FILE *fin  = fopen("runround.in", "r");
    FILE *fout = fopen("runround.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif
	
	fscanf(fin, "%d\n", &number);
	debug("%d\n", number);

	int nextRR = number+1;
	int distance = 0;
	do{
		debug("nextRR=%d\n", nextRR);
		distance = isRR(nextRR);
		debug("distance=%d\n", distance);
		if(distance == 0){
			break;
		}
		else{
			nextRR = nextRR+distance;
		}
		
	}while(1);

	//print out
	fprintf(fout, "%d\n", nextRR);
	debug("%d\n", nextRR);
	
	fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

