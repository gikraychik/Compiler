%{
#include <stdio.h>
#include <string.h>
int result = 0;
void yyerror(const char *s)
{
	fprintf(stderr, "Unexpected error: %s\n", s);
}

int yywrap()
{
	return 1;
}

int main()
{
	yyparse();
}

%}

%token NUMBER
%token MUL
%token DIV
%token ADD
%token SUB

%%
val : expr { printf("%d", $$); }
expr : 	/* empty */
	| expr ADD term { $$ = $1 + $3;}
	| expr SUB term { $$ = $1 - $3; }
	| term
	;
term :	term MUL NUMBER { $$ = $1*$3; }
	| term DIV NUMBER { $$ = $1/$3; }
	| NUMBER { $$ = $1; }
	;

%%
