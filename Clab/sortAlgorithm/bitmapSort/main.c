#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"

int main(int argc, char *argv[]){
	int a[15]={18343,12,232,31111,42,53,642,721,849,90,112,123,134,8388607*2, 14124214};
	int i;
	int rtnVal;
	struct repository rep;
	rtnVal = initRepository(&rep, 80*1000*1000);
	if (rtnVal == MEMORY_NOT_ENOUGH){
		fprintf(stderr, "Memory is not enough!\n");
		exit(MEMORY_NOT_ENOUGH);
	}
	for (i=0 ; i < 15 ; i++){
		rtnVal = add(&rep, a[i]);
		if (rtnVal == OVERFLOW)
			fprintf(stderr, "Input number %d is too big!\n",a[i]);
	}
	int result;
	while ((result = getint(&rep)) != EOF){
		printf("%d\n",result);
		fflush(stdout);
	}
}
