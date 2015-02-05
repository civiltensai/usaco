/*
ID: civilte1
LANG: C
TASK: beads
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define _DEBUG_
#ifdef _DEBUG_
	#define debug(x) {printf x;}
#else
	#define debug(x) {;}
#endif

typedef struct _beadGroup{
	char beadType;
	int count;
	int startIndex;
	struct _beadGroup* previos;
	struct _beadGroup* next;
}BEADGROUP;

int longest2strings(char* string, int length){
	int i;
	for(i=0; i<length; (i++)){
		;
	}
}

int main(void){
    FILE *fin  = fopen("beads.in", "r");
    FILE *fout = fopen("beads.out", "w");
    
    
    int n = 0;
    int i;
    int max = 0;
    int thisMax = 0;
    int repeatOnce = 0;
    char beads[351] = {0};
    BEADGROUP beadStart;
    BEADGROUP* thisPtr = &beadStart;
    BEADGROUP* nextPtr = NULL;
    BEADGROUP* maxPtr = NULL;
    
    fscanf(fin, "%d\n%s", &n, beads);
    debug(("%d %s\n", n, beads));
    
    beadStart.beadType = beads[0];
    beadStart.count = 1;
    beadStart.previos = NULL;
    beadStart.next = NULL;
    
    for(i = 1; i < 2*n; i++){
    	if(thisPtr->count >= n){
    		break;
		}
    	if(beads[i%n] == thisPtr->beadType){
    		thisPtr->count++;
		}
		else{
	    	nextPtr = (BEADGROUP*) malloc(sizeof(BEADGROUP));
	    	nextPtr->beadType = beads[i%n];
	    	nextPtr->count = 1;
	    	nextPtr->startIndex = i%n;
	    	nextPtr->next = NULL;
	    	nextPtr->previos = thisPtr;
	    	
			thisPtr->next = nextPtr;
			thisPtr = nextPtr;
		}
	}
    
    thisPtr = &beadStart;
    nextPtr = thisPtr->next;
    max = thisPtr->count;
    maxPtr = thisPtr;
    while(nextPtr){    	
    	//Initial thisMax
    	thisMax = thisPtr->count;
    	//check if start from 'w'
    	if(thisPtr->beadType == 'w'){
    		thisPtr = thisPtr->next;
    		if(thisPtr)
    			thisMax = thisMax + thisPtr->count;
    		else
    			break;
		}
		nextPtr = thisPtr->next;
		if(!nextPtr){
			break;
		}
    	//check if next group is 'w' or same char with thisPtr->beadType
    	while(nextPtr && (nextPtr->beadType == 'w' || nextPtr->beadType == thisPtr->beadType)){
    		thisMax = thisMax + nextPtr->count;
    		nextPtr = nextPtr->next;
		}
		
		if(nextPtr){
			//add count of different char
			thisMax = thisMax + nextPtr->count;
			
	    	//check if next group is 'w' or same char with nextPtr->beadType
			BEADGROUP* nextEndPtr = nextPtr->next;
	    	while(nextEndPtr && (nextEndPtr->beadType == 'w' || nextPtr->beadType == nextEndPtr->beadType)){
	    		thisMax = thisMax + nextEndPtr->count;
	    		nextEndPtr = nextEndPtr->next;
			}
		}
		
		if(thisMax > n){
			max = n;
			break;
		}
		
    	if(max < thisMax){
    		max = thisMax;
    		maxPtr = thisPtr;
		}
    	
    	nextPtr = thisPtr->next;
    	thisPtr = nextPtr;
	}
	
    
    fprintf(fout, "%d\n", max);
    
    fclose(fin);
    fclose(fout);
    exit(0);
}
