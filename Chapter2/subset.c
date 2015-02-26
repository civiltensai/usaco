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

int number;
int print[40] = {0};
int count = 0;
int printIndex = 0;
int counts[40][400];

#ifdef _DEBUG_
void output(void){
	int j;
	debug("%s","output - ");
	for(j = 1; j <= number; j++){
		debug("%d ", print[j]);
	}
	debug("%s","\n");
}
void set(int start, int end, int value){
	int j;
	for(j = start; j <= end; j++){
		print[j] = value;
	}
}
#else
	#define output() {;}
	#define set(x, y, z) {;}
#endif

void findDiff(int start, int end, int diff){
	debug("findDiff - %d->%d, %d\n", start, end, diff);
	int pDiff = diff;
	if(pDiff < 0){
		pDiff = -1*pDiff;
	}
	
	if( (start+end)*(end-start+1)/2 < pDiff ){
		return;
	}
	else if(start == end){
		if(start == diff){
			count++;
			print[start] = 1;
			output();
			return;
		}
		else{
			return;
		}
	}
	else{
		print[end] = 1;
		findDiff(start, end-1, diff+end);
		print[end] = 0;
		findDiff(start, end-1, diff-end);
	}
}

void findSum(int start, int end, int sum){
	debug("findSum - %d->%d, %d\n", start, end, sum);
	if(sum == 0){
		set(start, end, 0);
		output();
		count++;
		return;
	}
	else if( (start+end)*(end-start+1)/2 == sum){
		set(start, end, 1);
		output();
		count++;
		return;
	}
	else if((start+end)*(end-start+1)/2 < sum){
		return;
	}
	else if(start == end && start != sum){
		return;
	}
	else{
		if(sum >= end){
			print[end] = 1;
			findSum(start, end-1, sum-end);
			print[end] = 0;
			findSum(start, end-1, sum);
			
		}
		else{
			set(sum+1, end, 0);
			findSum(start, sum, sum);
		}
		/*
		print[end] = 0;
		findSum(start, end-1, sum);
		*/
	}
}


void findSum2(int end, int sum){
	debug("findSum2 - end=%d, sum=%d\n", end, sum);
	int all = (1+end)*end/2;
	if(sum == 0 || all == sum){
		set(1, end, (sum != 0));
		output();
		count++;
		return;
	}
	{
		if(sum >= end){
			print[end] = 1;
			findSum2(end-1, sum-end);
			
			if( all-end >= sum ){
				print[end] = 0;
				findSum2(end-1, sum);
			}
			
		}
		else{
			set(sum+1, end, 0);
			findSum2(sum, sum);
		}
	}
}


void findSum3(int end, int sum){
	debug("findSum3 - end=%d, sum=%d\n", end, sum);
	int all = (1+end)*end/2;
	
	if(sum == 0 || all == sum){
		set(1, end, (sum != 0));
		output();
		count++;
		return;
	}
	if(sum >= end){
		print[end] = 1;
		findSum3(end-1, sum-end);
		
		if( all-end >= sum ){
			print[end] = 0;
			findSum3(end-1, sum);
		}
		
	}
	else{
		set(sum+1, end, 0);
		findSum3(sum, sum);
	}
}


int findSum4(int end, int sum){
	debug("findSum4 - end=%d, sum=%d\n", end, sum);
	int all = (1+end)*end/2;
	int c = 0;
	if(sum == 0 || all == sum){
		set(1, end, (sum != 0));
		output();
		c = 1;
		count += c;
		return c;
	}
	if(sum >= end){
		print[end] = 1;
		if(counts[end-1][sum-end] != -1){
			counts[end-1][sum-end] = findSum4(end-1, sum-end);
		}
		c += counts[end-1][sum-end];
		
		if( all-end >= sum ){
			print[end] = 0;
			if(counts[end-1][sum] == -1){
				counts[end-1][sum] = findSum4(end-1, sum);
			}
			c += counts[end-1][sum];
		}
		count += c;
		return c;
	}
	else{
		set(sum+1, end, 0);
		if(counts[sum][sum] == -1){
			counts[sum][sum] = findSum4(sum, sum);
		}
		c += counts[sum][sum];
		count += c;
		return c;
	}
}


int main(void){
    FILE *fin  = fopen("subset.in", "r");
    FILE *fout = fopen("subset.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif

	int i, j;
	for(i = 0; i < 40; i++){
		for(j = 0; j < 400; j++){
			counts[i][j] = -1;
		}
	}
	
	fscanf(fin, "%d\n", &number);
	debug("%d\n", number);

	if(number > 2 && (number*(number+1)/2)%2 == 0 ){
		print[number] = 1;
		//findSum(1, number-1, number*(number+1)/2/2-number);
		findSum3(number-1, number*(number+1)/2/2-number);
		debug("%d\n\n", count);
		
	}
	
/*
#if 0	
	if(number > 2){
		print[number] = 1;
		print[number-1] = 0;
		findDiff(1, number-2, 1);
		findDiff(1, number-2, -1);
		findDiff(1, number-2, 2*number-1);
		findDiff(1, number-2, 1-2*number);
	}
	else
#endif
	{
		findDiff(1, number, 0);
	}
*/

/*
	unsigned long long i;
	unsigned long long allOne = ((long long)1 << number) - 1;
	
	for(i = 1; i <= allOne/2; i++){
		unsigned long long temp = i;
		int sum[2] = {(number+1)*number/2, 0};

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
*/

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

