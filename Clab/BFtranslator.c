#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/**
 * This program is used to translate brainfuck programming language into C
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

int main(int argc, char *argv[]){
	if (argc < 2){
		error("Usage: %s *.bf", argv[0]);
		exit(3);
	}
	FILE *in = fopen(argv[1], "r");
	FILE *out = fopen("out.c", "w");
	char p;
	if (!in)
		fatal("Could not open %s", argv[1]);
	if (!out)
		fatal("Could not open %s", argv[1]);

	fprintf(out, "#include <stdio.h>\nvoid main(void){\n");
	fprintf(out, "char array[300000];\nchar *ptr = array;\n");

	for (;;){
		p = fgetc(in);
		if (feof(in))
			break;

		switch(p){
			case '>':
				fprintf(out, "++ptr;\n");
				break;
			case '<':
				fprintf(out, "--ptr;\n");
				break;
			case '+':
				fprintf(out, "++*ptr;\n");
				break;
			case '-':
				fprintf(out, "--*ptr;\n");
				break;
			case '.':
				fprintf(out, "putchar(*ptr);\n");
				break;
			case ',':
				fprintf(out, "*ptr = getchar();\n");
				break;
			case '[':
				fprintf(out, "while(*ptr){\n");
				break;
			case ']':
				fprintf(out, "}\n");
				break;
			case '\n':
			case ' ':
			case '\t':break;
			default:
				fatal("unknown token %c", p);
		}
	}
	fprintf(out, "}");
}
