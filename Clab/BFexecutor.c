#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>

/**
 * This program is used to execute brainfuck programming language from source code
 * Visit http://en.wikipedia.org/wiki/Brainfuck for more information
 */

void fatal(const char *fmt, ...){
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	fputc('\n', stderr);
	exit(1);
}

int error(const char *fmt, ...){
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	fputc('\n', stderr);
	return -1;
}

int main(int argc, char *argv[]){
	if (argc < 2){
		error("Usage: %s *.bf", argv[0]);
		exit(3);
	}
#define BUFSIZE 300000
	char buffer[BUFSIZE];
	char program[BUFSIZE];	/* save program source code */

	char *ptr = buffer;
	char *p;	/*point to instruction of BF */
	char *last_lbracket = NULL;
	char *last_rbracket = NULL;
	ssize_t numread;
	int fd;

	memset(buffer, 0, BUFSIZE);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		fatal("Could not open %s", argv[1]);

	if ((numread = read(fd, program, BUFSIZE-1)) < 0)
		fatal("read error");

	program[numread] = '\0';

	for (p = program; *p != '\0';p++){
		switch(*p){
			case '>':
				ptr++;
				break;
			case '<':
				ptr--;
				break;
			case '+':
				++*ptr;
				break;
			case '-':
				--*ptr;
				break;
			case '.':
				putchar(*ptr);
				break;
			case ',':
				*ptr = getchar();
				break;
			case '[':
				last_lbracket = p;
				/* we assume people will do right thing */
				if (!(*ptr))
					p = last_rbracket;
				break;
			case ']':
				last_rbracket = p;
				if (!last_lbracket)
					fatal("unbalance bracket");
				else
					if (*ptr)
						p = last_lbracket;
				break;
			case '\n':
			case ' ':
			case '\t':break;
			default:
				fatal("unknown token %c", p);
		}
	}
}
