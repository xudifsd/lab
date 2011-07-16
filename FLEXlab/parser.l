%option noyywrap nodefault yylineno

%x LOOKING_FUNCTION_NAME
%x LOOKING_FUNCTION_ARGS
%x LOOKING_FUNCTION_BODY

WS ([ \t\n]+)
IDENTIFIER ([a-zA-Z_][a-zA-Z0-9_]*)

INT_TYPE ((signed{WS}|unsigned{WS})?(int|long({WS}(int|long))?|short({WS}int)?|char))
FLOAT_TYPE (float|(long{WS})?double)
STRUCT_TYPE (struct{WS}{IDENTIFIER})

RETURN_TYPE ((const{WS})?(void|{INT_TYPE}|{FLOAT_TYPE}|{STRUCT_TYPE})({WS}[*]{1,})?)
ARGS_LIST "("([^")"]|\n)*")"

%{
/*TODO sometimes function matches '\n', use some function to trim yytext*/
#include <string.h>
int function_definition = 0;
int comment = 0;

char *function_return_type;
char *function_name;
char *function_args_list;
%}

%%

"/*"([^*]|[*]+[^/*]|\n)*"*/"	{ comment++;}
"//".*\n	{ comment++; }

(static{WS}|extern{WS})?{RETURN_TYPE}	{
	BEGIN(LOOKING_FUNCTION_NAME);
	function_return_type = strdup(yytext);
}

<LOOKING_FUNCTION_NAME>{WS}	{/*skip white space*/}
<LOOKING_FUNCTION_NAME>{IDENTIFIER}	{
	BEGIN(LOOKING_FUNCTION_ARGS);
	function_name = strdup(yytext);
}
<LOOKING_FUNCTION_NAME>. {
	BEGIN(INITIAL);
	free(function_return_type);
}

<LOOKING_FUNCTION_ARGS>{WS}	{/*skip white space*/}
<LOOKING_FUNCTION_ARGS>{ARGS_LIST}	{
	BEGIN(LOOKING_FUNCTION_BODY);
	function_args_list = strdup(yytext);
}
<LOOKING_FUNCTION_ARGS>(.|\n)	{
	BEGIN(INITIAL);
	free(function_return_type);
	free(function_name);
}

<LOOKING_FUNCTION_BODY>{WS}	{/*skip white space*/}
<LOOKING_FUNCTION_BODY>"{"	{
	BEGIN(INITIAL);
	printf("%4d meet whole function_definition which is '%s %s %s'\n", yylineno, function_return_type, function_name, function_args_list);
	function_definition++;
	free(function_return_type);
	free(function_name);
	free(function_args_list);
}
<LOOKING_FUNCTION_BODY>.	{BEGIN(INITIAL);}

.|\n	{/*do nothing*/}

%%

int main(){
	yylex();
	printf("comment %d, function_definition %d\n", comment, function_definition);
}
