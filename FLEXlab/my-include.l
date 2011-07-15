%option noyywrap
%x IFILE

%{
struct stack {
	struct stack *prev;
	char *filename;
	int lineno;
	YY_BUFFER_STATE bs;
	FILE *f;
} *top = NULL;

int newfile(char *);
int pop();
%}

%%

^"#"[ \t]*"include"[ \t]*[\"<]	{ BEGIN IFILE; }

<IFILE>[^ \t\n\">]+	{
	{
		int c;
		while (( c = input()) && c != '\n');
	}
	top->lineno++;
	if (!newfile(yytext))
		yyterminate();

	BEGIN INITIAL;
}

<<EOF>>	{ if(!pop()) yyterminate(); }

^[^#].*\n	{printf("%4d %s", top->lineno++, yytext);}

%%

int newfile(char *name){
	FILE *f = fopen(name, "r");
	if (!f){
		perror(name);
		return 0;
	}

	struct stack *bs = (struct stack *)malloc(sizeof(struct stack));
	bs->prev = top;
	bs->filename = name;
	bs->lineno = 1;
	bs->bs = yy_create_buffer(f, YY_BUF_SIZE);
	bs->f = f;
	top = bs;
	yy_switch_to_buffer(top->bs);
	return 1;
}

int pop(){
	struct stack *del = top;
	top = top->prev;
	yy_delete_buffer(del->bs);
	fclose(del->f);
	free(del);
	if (top == NULL){
		yyterminate();
		return 0;
	} else{
		yy_switch_to_buffer(top->bs);
		return 1;
	}
}

int main(int argc, char *argv[]){
	newfile(argv[1]);
	yylex();
}
