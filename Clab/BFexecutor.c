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
	vfprintf(stderr, fmt, args);
	va_end(args);
	fputc('\n', stderr);
	exit(1);
}

int error(const char *fmt, ...){
	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	fputc('\n', stderr);
	return -1;
}

char **push(char **sp, char *obj){
	*sp = obj;
	return sp + 1;
}

char **pop(char **sp, char **rtn){
	if (rtn)
		*rtn = *(sp - 1);
	return sp - 1;
}

char *get(char **sp){
	return *(sp - 1);
}

int main(int argc, char *argv[]){
	if (argc < 2){
		error("Usage: %s *.bf", argv[0]);
		exit(3);
	}
#define BUFSIZE 300000
	char buffer[BUFSIZE];
	char program[BUFSIZE];	/* save program source code */
	char *stack[10000];	/* save last meet left bucket */

	char **sp = stack;

	char *ptr = buffer;
	char *p;	/*point to instruction of BF */
	ssize_t numread;
	int fd;

	memset(buffer, 0, BUFSIZE);
	memset(program, 0, BUFSIZE);
	memset(stack, 0, 10000);
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
				if (!(*ptr)){
					p = strchr(p, ']');
					if (!p)
						fatal("missing ]");
				} else
					sp = push(sp, p);
				break;
			case ']':
				if (*ptr){
					if (sp == stack)
						fatal("unbalance bracket");
					p = get(sp);
				} else{
					if (sp == stack)
						fatal("unbalance bracket");
					sp = pop(sp, NULL);
				}
				break;
			case '\n':
			case ' ':
			case '\t':break;
			default:
				fatal("unknown token '%c'", *p);
		}
	}
}
