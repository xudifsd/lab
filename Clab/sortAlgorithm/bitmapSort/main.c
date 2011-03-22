#include <stdio.h>
#include "bitmap.h"

int main(int argc, char *argv[]){
	int a[14]={18343,12,232,31111,42,53,642,721,849,90,112,123,134,8388607*2};
	int i;
	int rtnVal;
	initRepository();
	for (i=0 ; i < 14 ; i++){
		rtnVal = add(a[i]);
		if (rtnVal == OVERFLOW)
			fprintf(stderr,"Input number is too big!\n");
	}
	int result;
	while ((result = getint()) != EOF){
		printf("%d\t",result);
		fflush(stdout);
	}
	printf("\n");
}
