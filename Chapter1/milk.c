/*
ID: civilte1
LANG: C
TASK: milk
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

typedef struct _node{
	int price;
	int produce;
	struct _node* parent;
	struct _node* left;
	struct _node* right;
}NODE;


int getCost(NODE* root, int* amount){
	int cost = 0;
	if(root && *amount){
		debug("root price=%d produce=%d: ", root->price, root->produce);
		cost = getCost(root->left, amount);
		if(*amount){
			if(root->produce <= *amount){
				cost = cost + (root->price * root->produce);
				*amount = *amount - root->produce;
				cost = cost + getCost(root->right, amount);
			}
			else{
				cost = cost + (root->price * (*amount));
				*amount = 0;
			}
		}
	}
	debug("Remain amount=%d cost=%d\n", *amount, cost);
	
	return cost;
}

int insert(NODE** root, int newPrice, int newProduce){
	int ret = 0;
	if(!(*root)){
		*root = (NODE*) malloc(sizeof(NODE));
		(*root)->price = newPrice;
		(*root)->produce = newProduce;
		(*root)->left = NULL;
		(*root)->right = NULL;
		debug("0x%08X price=%d produce=%d\n", *root, (*root)->price, (*root)->produce);
	}
	else{
		if(newPrice < (*root)->price){
			debug("0x%08X price=%d left: ", *root, (*root)->price);
			ret = insert(&((*root)->left), newPrice, newProduce);
			if(ret){
				(*root)->left->parent = (*root);
			}
		}
		else if(newPrice > (*root)->price){
			debug("0x%08X price=%d right: ", *root, (*root)->price);
			ret = insert(&((*root)->right), newPrice, newProduce);
			if(ret){
				(*root)->right->parent = (*root);
			}
		}
		else{
			(*root)->produce += newProduce;
			ret = 1;
		}
	}
	return ret;
}



int main(void){
    FILE *fin  = fopen("milk.in", "r");
    FILE *fout = fopen("milk.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif

	int total, farmCount;
	int produce = 0;
	int price = 0;
	int cost = 0;
	int i;
	NODE* root = NULL;
	
	fscanf(fin, "%d %d\n", &total, &farmCount);
    for(i = 0; i < farmCount; i++){
    	fscanf(fin, "%d %d\n", &price, &produce);
    	insert(&root, price, produce);
	}
    
    cost = getCost(root, &total);
    
	fprintf(fout, "%d\n", cost);
	
    fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

