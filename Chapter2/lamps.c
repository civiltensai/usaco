/*
ID: civilte1
LANG: C
TASK: lamps
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
FILE *fout;

#define MAXLAMPS 100
#define MAX (MAXLAMPS+1)
int number;
int counter;
int count = 0;
char* failString = "IMPOSSIBLE";


int stack[MAX];
int top = 0;
void push(int i){
	stack[top] = i;
	top++;
}
int pop(void){
	top--;
	return stack[top];
}

int finalState[MAX]; // index 0 not used

typedef struct _node{
	struct _node* on;
	struct _node* off;
	struct _node* parent;
	int answer;
#ifdef _DEBUG_
	int state[MAX];
#else
#endif
}NODE;
NODE rootNode;

typedef struct _anwser{
	unsigned long up;
	unsigned long mid;
	unsigned long low; 
}ANSWER;

#ifdef _DEBUG_
	void dumpState(NODE* leaf){
		int i;
		debug("%s","\n");
		for(i = 1; i <= number; i++){
			debug("%2d", i);
		}
		debug("%s","\n");
		for(i = 1; i <= number; i++){
			debug("%2d", leaf->state[i]);
		}
		debug("%s","\n");
	}
	void setState(NODE* leaf){
		int i;
		for(i = 0; i < number; i++){
			leaf->state[number - i] = stack[i];
		}
	}
	void initState(NODE* leaf){
		int i;
		for(i = 1; i <= number; i++){
			leaf->state[i] = 0;
		}
	}
#else
	#define dumpState(x) {;}
	#define setState(x) {;}
	#define initState(x) {;}
#endif

NODE* creatNode(NODE* parent){
	NODE* newNode = (NODE*) malloc(sizeof(NODE));
	newNode->parent = parent;
	newNode->off = NULL;
	newNode->on = NULL;
	newNode->answer = 0;
	
	return newNode;
}

int isFinalState(NODE* leaf){
	int index = number;
	do{
		if(finalState[index] == 1 && leaf->parent->off == leaf){
			return 0;
		}
		else if(finalState[index] == 0 && leaf->parent->on == leaf){
			return 0;
		}
		
		leaf = leaf->parent;
		index--;
	}while(leaf->parent);
	return 1;
}

//Return the leaf of the next new state. If not exist this state, change isExist=0;
void button1(NODE* leaf){
	int i = 1;
	//debug("%s", "(1)-");
	do{
		if(leaf->parent->off != NULL && leaf->parent->off == leaf){	//off node
			push(1); //button1 revert all
		}
		else{							//on node
			push(0); //button1 revert all
		}
		leaf = leaf->parent;
	}while(leaf->parent);
	
}

//Return the leaf of the next new state. If not exist this state, change isExist=0;
void button2(NODE* leaf){
	int i = number;
	//debug("%s", "(2)-");
	do{
		if(0 ^ (i%2)){
			if(leaf->parent->off != NULL && leaf->parent->off == leaf){	//off node
				push(1);
			}
			else{
				push(0);
			}
		}
		else{
			push(leaf->parent->on != NULL && leaf->parent->on == leaf); //on:1/off:0 mode
		}
		
		leaf = leaf->parent;
		i--;
	}while(leaf->parent);
	
}

//Return the leaf of the next new state. If not exist this state, change isExist=0;
void button3(NODE* leaf){
	int i = number;
	//debug("%s", "(3)-");
	do{
		if(1 ^ (i%2)){
			if(leaf->parent->off != NULL && leaf->parent->off == leaf){	//off node
				push(1);
			}
			else{
				push(0);
			}
		}
		else{
			push(leaf->parent->on != NULL && leaf->parent->on == leaf); //on:1/off:0 mode
		}
		leaf = leaf->parent;
		i--;
	}while(leaf->parent);
	
}

//Return the leaf of the next new state. If not exist this state, change isExist=0;
void button4(NODE* leaf){
	int i = number;
	//debug("%s", "(4)-");
	do{
		if(0 ^ (i%3==1)){
			if(leaf->parent->off != NULL && leaf->parent->off == leaf){	//off node
				push(1);
			}
			else{
				push(0);
			}
		}
		else{
			push(leaf->parent->on != NULL && leaf->parent->on == leaf); //on:1/off:0 mode
		}
		leaf = leaf->parent;
		i--;
	}while(leaf->parent);
	
}

//Return the leaf of the next new state. If not exist this state, change isExist=0;
NODE* createState(int* isExist){
	NODE* ptr = &rootNode;
	int i = 0;

	do{
		if(pop() == 0){
			if(ptr->off == NULL){
				ptr->off = creatNode(ptr);
				*isExist = 0;
			}
			ptr = ptr->off;
		}
		else{
			if(ptr->on == NULL){
				ptr->on = creatNode(ptr);
				*isExist = 0;
			}
			ptr = ptr->on;
		}
		i++;
	}while(i<number);
	initState(ptr);
	return ptr;
}

void setResult(NODE* leaf){
	while(leaf->parent){
		if(leaf == leaf->parent->on){
			leaf->parent->answer = leaf->parent->answer | 0x1;
		}
		else if(leaf == leaf->parent->off){
			leaf->parent->answer = leaf->parent->answer | 0x2;
		}
		leaf = leaf->parent;
	}
}

	//nextLeaf = createState(isExist);
void findPossible(NODE* leaf, int depth){
	debug("findPossible depth=%d", depth);
	dumpState(leaf);
	if(isFinalState(leaf)){
		count++;
		setResult(leaf);
		dumpState(leaf);
	}
	if(depth < counter){
		int isExist = 1;
		button1(leaf);
		NODE* nextLeaf = createState(&isExist);
		
		if(isExist == 0){
			debug("%s", "(1)-");
			setState(nextLeaf);
			findPossible(nextLeaf, depth+1);
		}
		
		isExist = 1;
		button2(leaf);
		nextLeaf = createState(&isExist);
		
		if(isExist == 0){
			debug("%s", "(2)-");
			setState(nextLeaf);
			findPossible(nextLeaf, depth+1);
		}
		
		isExist = 1;
		button3(leaf);
		nextLeaf = createState(&isExist);
		
		if(isExist == 0){
			debug("%s", "(3)-");
			setState(nextLeaf);
			findPossible(nextLeaf, depth+1);
		}
		
		isExist = 1;
		button4(leaf);
		nextLeaf = createState(&isExist);
		
		if(isExist == 0){
			debug("%s", "(4)-");
			setState(nextLeaf);
			findPossible(nextLeaf, depth+1);
		}
	}
	debug("findPossible end depth=%d", depth);
	
}

void DFS(NODE* root){
	static NODE* branch = NULL;
	if(root && root->answer){
		if(root->answer & 0x2){
			fprintf(fout, "%d", 0);
			debug("%d", 0);
			if(root->answer & 0x3 == 0x3){
				branch = root;
			}
			DFS(root->off);
			if(branch != NULL){
				branch->answer -= 0x2;
				branch = NULL;
			}
		}
		else if(root->answer & 0x1){
			fprintf(fout, "%d", 1);
			debug("%d", 1);
			DFS(root->on);
		}
	}
	else if(root->on == NULL && root->off == NULL){
		fprintf(fout, "\n");
		debug("%s", "\n");
	}
}

int main(void){
	FILE *fin  = fopen("lamps.in", "r");
	fout = fopen("lamps.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif
	
	fscanf(fin, "%d\n", &number);
	fscanf(fin, "%d\n", &counter);
	debug("%d\n%d\n", number, counter);
	
	int i, j;
	//init state tree
	NODE* parent = &rootNode;
	
	for(i = 0; i < number; i++){
		finalState[i+1] = -1;
		stack[i] = 1;
		parent->on = creatNode(parent);
		parent = parent->on;
	}
	setState(parent);
	
	int temp=0;
	do{
		fscanf(fin, "%d", &temp);
		debug("%d ", temp);
		if(temp != -1){
			//finalState[temp-1] = '1';
			finalState[temp] = 1;
		}
	}while(temp != -1);
	debug("%s","\n");

	temp=0;
	do{
		fscanf(fin, "%d", &temp);
		debug("%d ", temp);
		if(temp != -1){
			//finalState[temp-1] = '0';
			finalState[temp] = 0;
		}
	}while(temp != -1);
	debug("%s","\n");


	//Find all possible
	findPossible(parent, 0);
	
	ANSWER* result = (ANSWER*) malloc(sizeof(ANSWER)*count);
	memset(result, 0, sizeof(ANSWER));
	
	
	//print out
	
	if(count == 0){
		fprintf(fout, "%s\n", failString);
		debug("%s\n", failString);
	}
	else{
		while(count){
			DFS(&rootNode);
			count--;
		}
	}
	
	fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

