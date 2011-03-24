#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "bitmap.h"

#define ONE (1 << 1)
#define TWO (1 << 2)
#define THREE (1 << 3)
#define FOUR (1 << 4)
#define FIVE (1 << 5)
#define SIX (1 << 6)
#define SEVEN (1 << 7)
#define EIGHT (1 << 8)

#define MAX 1048576*2

static char repository[MAX];	//bigest number can store is MAX*CHAR_BIT-1

static char *byteOffset = repository;

static unsigned short bitOffset = 0;

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
	for (;;){
		if (bitOffset == 8){
			byteOffset++;
			bitOffset = 0;
		}
		if (byteOffset == (repository + MAX))
			return EOF;

		switch (bitOffset){
			case 0 :
				if (!(*byteOffset & ONE)){
					bitOffset++;
					continue;
				}
				else
					return (((byteOffset - repository) * 8) + (bitOffset++));
			case 1 :
				if (!(*byteOffset & ONE)){
					bitOffset++;
					continue;
				}
				else
					return (((byteOffset - repository) * 8) + (bitOffset++));
			case 2 :
				if (!(*byteOffset & TWO)){
					bitOffset++;
					continue;
				}
				else
					return (((byteOffset - repository) * 8) + (bitOffset++));
			case 3 :
				if (!(*byteOffset & THREE)){
					bitOffset++;
					continue;
				}
				else
					return (((byteOffset - repository) * 8) + (bitOffset++));
			case 4 :
				if (!(*byteOffset & FOUR)){
					bitOffset++;
					continue;
				}
				else
					return (((byteOffset - repository) * 8) + (bitOffset++));
			case 5 :
				if (!(*byteOffset & FIVE)){
					bitOffset++;
					continue;
				}
				else
					return (((byteOffset - repository) * 8) + (bitOffset++));
			case 6 :
				if (!(*byteOffset & SIX)){
					bitOffset++;
					continue;
				}
				else
					return (((byteOffset - repository) * 8) + (bitOffset++));
			case 7 :
				if (!(*byteOffset & SEVEN)){
					bitOffset++;
					continue;
				}
				else
					return (((byteOffset - repository) * 8) + (bitOffset++));
		}
	}
}
