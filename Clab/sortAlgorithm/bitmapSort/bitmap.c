#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "bitmap.h"

#define MAX (1048576*2)	//bigest number can stored in bitmap

static char repository[MAX];	//bigest number can store is MAX*CHAR_BIT-1

extern void initRepository(){	//since bitmap need accurate bit stat, so it needs to init before use add
	memset(&repository, 0, sizeof(repository));
}

extern int add(int number){	//0 for success
	if (number > MAX*CHAR_BIT-1 || number < 0)
		return OVERFLOW;
	char *p = repository;
	char stuff = 1;
	p += number / CHAR_BIT;
	stuff <<= number % CHAR_BIT;
	*p |= stuff;
	return 0;
}

extern int getint(void){	//return EOF indicate it has all returned
	static char *byteOffset = repository;

	static unsigned short bitOffset = 0;

	for (;;){
		if (bitOffset == CHAR_BIT){
			byteOffset++;
			bitOffset = 0;
		}
		if (byteOffset == (repository + MAX))
			return EOF;

		if (!(*byteOffset & (1 << bitOffset))){	//no number in current bit
			bitOffset++;
			continue;
		}
		else	//has number
			return (((byteOffset - repository) * CHAR_BIT) + (bitOffset++));
	}
}
