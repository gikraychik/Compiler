%{
#include <stdio.h>
#include <string.h>

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
expr :	/* empty */ { printf("Empty"); }
	| term ADD expr
	{
		printf("%d", $1);
	}
	| term SUB expr
	;
term : 	NUMBER { printf("%d", $1); }
	| NUMBER MUL term
	| NUMBER DIV term
	;
%%
