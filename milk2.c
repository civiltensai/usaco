/*
ID: civilte1
LANG: C
TASK: milk2
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

typedef struct _time{
	int time;
	int diff;
	struct _time* next;
}MILKTIME;

int insert(MILKTIME** root, MILKTIME* newNode){
	if(!(*root)){
		*root = newNode;
	}
	else{
		MILKTIME* temp = *root;
		MILKTIME* previous = NULL;
		do{
			if(temp->time > newNode->time){
				newNode->next = temp;
				if(previous)
					previous->next = newNode;
				else
					*root = newNode;
				return;
			}
			else if(temp->time == newNode->time){
				temp->diff += newNode->diff;
				free(newNode);
				return;
			}
			else{
				previous = temp;
				temp = temp->next;
			}
			
		}while(temp);
		previous->next = newNode;
	}
}

int main(void){
    FILE *fin  = fopen("milk2.in", "r");
    FILE *fout = fopen("milk2.out", "w");
    
    
    int n = 0, i;
    int startMilkTime = 0;
    int endMilkTime = 0;
    
    fscanf(fin, "%d\n", &n);
    MILKTIME* start = NULL;
    
    for(i = 0; i < n; i++){
    	MILKTIME* ptr = (MILKTIME*) malloc(sizeof(MILKTIME));
    	fscanf(fin, "%d ", &(ptr->time));
    	ptr->diff = 1;
    	ptr->next = NULL;
    	insert(&start, ptr);
    	
    	ptr = (MILKTIME*) malloc(sizeof(MILKTIME));
    	fscanf(fin, "%d\n", &(ptr->time));
    	ptr->diff = -1;
    	ptr->next = NULL;
    	insert(&start, ptr);
	}
    
    MILKTIME* ptr1 = start;
    MILKTIME* ptr2 = ptr1->next;
    int duration = 0;
    int maxDurationMilks = 0;
    int durationMilks = 0;
    int maxDurationNoOneMilks = 0;
    int durationNoOneMilks = 0;
    int currentMilkCount = ptr1->diff;
    int nextMilkCount = 0;
    while(ptr1 && ptr2){
    	nextMilkCount = currentMilkCount + ptr2->diff;
    	duration = duration + (ptr2->time - ptr1->time);
    	if(currentMilkCount==0 && nextMilkCount){
    		if(duration > maxDurationNoOneMilks){
    			maxDurationNoOneMilks = duration;
			}
    		duration = 0;
		}
		else if(currentMilkCount && nextMilkCount==0){
    		if(duration > maxDurationMilks){
    			maxDurationMilks = duration;
			}
    		duration = 0;
		}
    	currentMilkCount = nextMilkCount;
    	debug(("time:%d diff:%d -> time:%d diff:%d -- d:%d, MND:%d, MD:%d\n", ptr1->time, ptr1->diff, ptr2->time, ptr2->diff, duration, maxDurationNoOneMilks, maxDurationMilks));
    	ptr1 = ptr2;
    	ptr2 = ptr2->next;
	}
    
    fprintf(fout, "%d %d\n", maxDurationMilks, maxDurationNoOneMilks);
    
    fclose(fin);
    fclose(fout);
    exit(0);
}
