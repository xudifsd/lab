#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "bitmap.h"

#define MAX 6553621

static char repository[MAX];	//bigest number can store is MAX*CHAR_BIT-1

static char *byteOffset = repository;

static unsigned short bitOffset = 0;

struct field {
	unsigned ONE : 1;
	unsigned TWO : 1;
	unsigned THREE : 1;
	unsigned FOUR : 1;
	unsigned FIVE : 1;
	unsigned SIX : 1;
	unsigned SEVEN : 1;
	unsigned EIGHT : 1;
};	//one byte

extern void initRepository(){
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
	struct field * result;
	for (;;){
		if (bitOffset == 8){
			byteOffset++;
			bitOffset = 0;
		}
		if (byteOffset == (repository + MAX))
			return EOF;

		result = byteOffset;
		switch (bitOffset){
			case 0 :
				if (result->ONE == 0){
					bitOffset++;
					continue;
				}
				else
					return (((byteOffset - repository) * 8) + (bitOffset++));
			case 1 :
				if (result->TWO == 0){
					bitOffset++;
					continue;
				}
				else
					return (((byteOffset - repository) * 8) + (bitOffset++));
			case 2 :
				if (result->THREE == 0){
					bitOffset++;
					continue;
				}
				else
					return (((byteOffset - repository) * 8) + (bitOffset++));
			case 3 :
				if (result->FOUR == 0){
					bitOffset++;
					continue;
				}
				else
					return (((byteOffset - repository) * 8) + (bitOffset++));
			case 4 :
				if (result->FIVE == 0){
					bitOffset++;
					continue;
				}
				else
					return (((byteOffset - repository) * 8) + (bitOffset++));
			case 5 :
				if (result->SIX == 0){
					bitOffset++;
					continue;
				}
				else
					return (((byteOffset - repository) * 8) + (bitOffset++));
			case 6 :
				if (result->SEVEN == 0){
					bitOffset++;
					continue;
				}
				else
					return (((byteOffset - repository) * 8) + (bitOffset++));
			case 7 :
				if (result->EIGHT == 0){
					bitOffset++;
					continue;
				}
				else
					return (((byteOffset - repository) * 8) + (bitOffset++));
		}
	}
}
