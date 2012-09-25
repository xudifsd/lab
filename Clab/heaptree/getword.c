#include <stdio.h>

char getword(char *space){
	char c;
	int i=0;
	while (!isalpha(c=getchar()))/*skip to English word*/
		if (c==EOF)
			return EOF;
	space[i]=c;
	i++;
	while (isalpha(c=getchar())){
		space[i]=c;
		i++;
	}
	space[i]='\0';
	return 1;
}
