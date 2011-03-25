#include <stdio.h>
#include "bitmap.h"

int main(int argc, char *argv[]){
	int a[15]={18343,12,232,31111,42,53,642,721,849,90,112,123,134,8388607*2, 1412421421};
	int i;
	int rtnVal;
	initRepository();
	for (i=0 ; i < 15 ; i++){
		rtnVal = add(a[i]);
		if (rtnVal == OVERFLOW)
			fprintf(stderr,"Input number %d is too big!\n",a[i]);
	}
	int result;
	while ((result = getint()) != EOF){
		printf("%d\t",result);
		fflush(stdout);
	}
	printf("\n");
}
