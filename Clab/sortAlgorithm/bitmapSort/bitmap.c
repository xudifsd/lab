#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"

extern int initRepository(struct repository *rep, unsigned int byteSize){
	rep->buffer = (char *)malloc(byteSize);
	if (!(rep->buffer))
		return MEMORY_NOT_ENOUGH;
	memset(rep->buffer, 0, byteSize);
	rep->size = byteSize;
	rep->byteOffset = rep->buffer;
	rep->bitOffset = 0;
	return SUCCESS;
}

extern int add(struct repository *rep, unsigned int number){
	if (number >= (rep->size * CHAR_BIT))
		return OVERFLOW;
	char *p = rep->buffer;
	char stuff = 1;
	p += number / CHAR_BIT;
	stuff <<= number % CHAR_BIT;
	*p |= stuff;
	return SUCCESS;
}

extern int getint(struct repository *rep){	//return EOF indicate it has all returned
	for (;;){
		if (rep->bitOffset == CHAR_BIT){
			(rep->byteOffset)++;
			rep->bitOffset = 0;
		}
		if (rep->byteOffset == (rep->buffer + rep->size))
			return EOF;

		if (!(*rep->byteOffset & (1 << (rep->bitOffset)))){	//no number in current bit
			(rep->bitOffset)++;
			continue;
		}
		else	//has number
			return (((rep->byteOffset - rep->buffer) * CHAR_BIT) + ((rep->bitOffset++)));
	}
}
