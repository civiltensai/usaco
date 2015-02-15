/*
ID: civilte1
LANG: C
TASK: transform
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

typedef struct _pair{
	char c;
	int x;
	int y;
}PAIR;


void Rotate90(int* x, int* y, int n){
	int oldX = *x, oldY = *y;
	*x = n - oldY - 1;
	*y = oldX;
	debug(("%s (%d,%d)->(%d,%d)\n", __FUNCTION__,oldX, oldY, *x, *y));
}

void Rotate180(int* x, int* y, int n){
	int oldX = *x, oldY = *y;
	*x = n - oldX - 1;
	*y = n - oldY - 1;
	debug(("%s (%d,%d)->(%d,%d)\n", __FUNCTION__,oldX, oldY, *x, *y));
}

void Rotate270(int* x, int* y, int n){
	int oldX = *x, oldY = *y;
	*x = oldY;
	*y = n - oldX - 1;
	debug(("%s (%d,%d)->(%d,%d)\n", __FUNCTION__,oldX, oldY, *x, *y));
}

void reflect(int* x, int* y, int n){
	int oldX = *x, oldY = *y;
	*x = n - oldX - 1;
	*y = oldY;
	debug(("%s (%d,%d)->(%d,%d)\n", __FUNCTION__,oldX, oldY, *x, *y));
}

int main(void){
    FILE *fin  = fopen("transform.in", "r");
    FILE *fout = fopen("transform.out", "w");
    
    int n = 0;
    int i = 0, j = 0;
    PAIR sourcePtr[100] = {0};
    int srclength = 0;
    char str[11] = {0};
    char result[10][11];
    int rltlength = 0;
    
    fscanf(fin, "%d\n", &n);
    for(i = 0; i< n; i++){
    	fscanf(fin, "%s\n", str);
    	int j = 0;
    	for(j = 0; j < n; j++){
	    	if(str[j] == '@' || str[j] == '-'){
	    		sourcePtr[srclength].c = str[j];
				sourcePtr[srclength].x = j;
				sourcePtr[srclength].y = i;
	    		debug(("source[%d][%d]=%c\n", sourcePtr[srclength].y, sourcePtr[srclength].x, sourcePtr[srclength].c));
				srclength++;
			}
			else{
				debug(("Error! Line%d .in line %d - str[%d]=%c\n", __LINE__, i, j, str[j]));
			}
		}
		
	}
	
    for(i = 0; i< n; i++){
    	fscanf(fin, "%s\n", result[i]);
    	debug(("%s\n", result[i]));
	}
	if(srclength!=n*n){
		debug(("Error! Line%d srclength=%d n=%d\n", __LINE__, srclength, n));
	}
#ifdef _DEBUG_
	else{
		debug(("Line%d srclength=%d n=%d\n", __LINE__, srclength, n));
	}
	
    for(i = 0; i< n; i++){
    	int j = 0;
    	for(j = 0; j < n; j++){
    		debug(("result[%d][%d]=%c", i, j, result[j][i]));
		}
    }
#endif
    
    int transformFail[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    for(i = 0; i< srclength; i++){
    	debug(("i=%d source %c %d %d\n", i, sourcePtr[i].c, sourcePtr[i].x, sourcePtr[i].y));
    	debug(("transformFail={%d,%d,%d,%d,%d,%d,%d,%d}\n", transformFail[0], transformFail[1], transformFail[2], transformFail[3], transformFail[4], transformFail[5], transformFail[6], transformFail[7]));
		int x, y;
		
    	for(j = 0; (j < 8); j++){
    		debug(("transformFail[%d]=%d - ", j, transformFail[j]));
    		if(transformFail[j] == 0){
				x = sourcePtr[i].x;
				y = sourcePtr[i].y;
	    		switch(j){
	    			case 0: /* #1: 90 Degree Rotation: The pattern was rotated clockwise 90 degrees. */
	    				Rotate90(&x, &y, n);
	    				break;
	    			case 1: /* #2: 180 Degree Rotation: The pattern was rotated clockwise 180 degrees. */
	    				Rotate180(&x, &y, n);
	    				break;
	    			case 2: /* #3: 270 Degree Rotation: The pattern was rotated clockwise 270 degrees. */
	    				Rotate270(&x, &y, n);
	    				break;
	    			case 3: /* #4: Reflection: The pattern was reflected horizontally (turned into a mirror image of itself by reflecting around a vertical line in the middle of the image). */
	    				reflect(&x, &y, n);
	    				break;
	    			case 4: /* #5: Combination: The pattern was reflected horizontally and then 90 Degree Rotation */
	    				reflect(&x, &y, n);
	    				Rotate90(&x, &y, n);
	    				break;
	    			case 5: /* #5: Combination: The pattern was reflected horizontally and then 180 Degree Rotation */
	    				reflect(&x, &y, n);
	    				Rotate180(&x, &y, n);
	    				break;
	    			case 6:  /* #5: Combination: The pattern was reflected horizontally and then 270 Degree Rotation */
	    				reflect(&x, &y, n);
	    				Rotate270(&x, &y, n);
	    				break;
	    			case 7: /* #6: No Change: The original pattern was not changed. */
	    				/* do nothing */
	    				debug(("no change\n"));
	    				break;
				}
				
				if(result[y][x]!=sourcePtr[i].c){
					transformFail[j] = 1;
					debug(("x --- result[%d][%d]=%c source %c (%d,%d)\n", y, x, result[y][x], sourcePtr[i].c, sourcePtr[i].y, sourcePtr[i].x));
				}
				else{
					debug(("o --- result[%d][%d]=%c source %c (%d,%d)\n", y, x, result[y][x], sourcePtr[i].c, sourcePtr[i].y, sourcePtr[i].x));
				}
			}
		}
		debug(("\n"));
    }
    
    
    int ret = 7;
    for(j = 0; j < 8; j++){
    	if(!transformFail[j]){
    		if(j < 4){
    			ret = j + 1;	
			}
			else if(j < 7){
				ret = 5;
			}
			else{
				ret = 6;
			}
			debug(("ret=%d transformFail[%d]=%d\n", ret, j, transformFail[j]));
    		break;
    	}
    }
    fprintf(fout, "%d\n", ret);
    
    fclose(fin);
    fclose(fout);
    exit(0);
}
