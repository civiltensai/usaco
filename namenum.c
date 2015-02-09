/*
ID: civilte1
LANG: C
TASK: namenum
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

char dic[5000][13];
typedef struct _namenum{
	int len;
	long long num;
	char name[13];
}NAMENUM;
NAMENUM names[5000];

int translate(void){
    
    int i;
    int lenNames = 0;
    while(dic[i][0]){
    	int j = 0;
    	long long num = 0;
    	int noQZ = 1;
    	
    	while(dic[i][j] && noQZ){
    		
    		
    		num = num*10;
    		switch(dic[i][j]){ /* Check each char in this name */
    			case 'A':
    			case 'B':
    			case 'C':
    				num+=2;
    				break;
    			case 'D':
    			case 'E':
    			case 'F':
    				num+=3;
    				break;
    			case 'G':
    			case 'H':
    			case 'I':
    				num+=4;
    				break;
    			case 'J':
    			case 'K':
    			case 'L':
    				num+=5;
    				break;
    			case 'M':
    			case 'N':
    			case 'O':
    				num+=6;
    				break;
    			case 'P':
    			case 'R':
    			case 'S':
    				num+=7;
    				break;
    			case 'T':
    			case 'U':
    			case 'V':
    				num+=8;
    				break;
    			case 'W':
    			case 'X':
    			case 'Y':
    				num+=9;
    				break;
    			case 'Q':
    			case 'Z':
    				noQZ = 0;
    				break;
			}
			if(noQZ){
				j++;
			}
		}
		if(noQZ){ /* There is no Q/Z in this name. */
			names[lenNames].len = strlen(dic[i]);
			names[lenNames].num = num;
			strncpy(names[lenNames].name, dic[i], names[lenNames].len+1);
			lenNames++;
		}
    	
    	i++;
	}
	return lenNames;
}

int main(void){
    FILE *fin  = fopen("namenum.in", "r");
    FILE *fin_dict  = fopen("dict.txt", "r");
    FILE *fout = fopen("namenum.out", "w");
    
    int i = 0, lenNames, found = 0;
    long long digits;
    
    while(EOF != fscanf(fin_dict, "%s\n", (char*)&(dic[i]))) {
    	i++;
	}
    
    lenNames = translate();
    
    fscanf(fin, "%lld\n", &digits);
    debug(("lenNames=%d\n", lenNames));
#ifdef _DEBUG_
    for(i = 0; i < lenNames; i++){
    		fprintf(fout, "%s %lld\n", names[i].name, names[i].num);
    		//debug(("%s %d\n", names[i].name, names[i].num));
	}

#endif
    
    for(i = 0; i < lenNames; i++){
    	if(digits == names[i].num){
    		fprintf(fout, "%s\n", names[i].name);
    		debug(("%s %lld\n", names[i].name, names[i].num));
    		found++;
		}
	}
    if(found == 0){
    	fprintf(fout, "NONE\n");
	}
    
    fclose(fin);
    fclose(fout);
    exit(0);
}

