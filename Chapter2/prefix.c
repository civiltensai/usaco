/*
ID: civilte1
LANG: C
TASK: prefix
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _DEBUG_
#ifdef _DEBUG_
	FILE *fdebug;
	#define debug(str, ...) do{ fprintf(fdebug, str, __VA_ARGS__); printf(str, __VA_ARGS__); }while(0)
#else
	#define debug(str, ...) {;}
#endif
FILE *fout;

char primitives[201][11];
int primitiveCount = 0;
char sequence[200001];
int sLength = 0;
int maxPrefixLen = 0;

void cmpLen(int len){
	if(len > maxPrefixLen){
		maxPrefixLen = len;
		debug("maxPrefixLen = %d\n", maxPrefixLen);
	}
}


void prefix(char* string, int length){
	if(length==0){
		cmpLen(sLength - length);
	}
	else{
		int i, matched = 0;
		for(i = 0; i < primitiveCount; i++){
			int len = strlen(primitives[i]);
			if(strncmp(string, primitives[i], len) == 0){
				prefix(string+len, length - len);
				matched++;
			}
		}
		if(matched == 0){
			cmpLen(sLength - length);
		}
	}
}

int main(void){
	FILE *fin  = fopen("prefix.in", "r");
	fout = fopen("prefix.out", "w");
#ifdef _DEBUG_
	fdebug = fopen("debug.log", "w");
#endif
	
	
	do{
		fscanf(fin, "%s", primitives[primitiveCount]);
		debug("%s\n", primitives[primitiveCount]);
		primitiveCount++;
	}while(primitives[primitiveCount-1][0] != '.');
	
	char* sStart = sequence;
	debug("aAAAAAAa%s", "\n");
	while(fscanf(fin, "%s", sStart) != EOF){
		debug("%s\n", sStart);
		sStart = sStart+strlen(sStart);
	}
	sLength = strlen(sequence);
	debug("%d %s\n", sLength, sequence);
	
	prefix(sequence, sLength);
	//print out
	fprintf(fout, "%d\n", maxPrefixLen);
	debug("%d\n", maxPrefixLen);
	
	
	fclose(fin);
    fclose(fout);
#ifdef _DEBUG_
	fclose(fdebug);
#endif
    exit(0);
}

