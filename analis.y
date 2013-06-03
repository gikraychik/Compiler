%{
#include <stdio.h>
#include <string.h>
#define YYSTYPE double

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
%token OBRACE
%token CBRACE

%%
val : expr { printf("%f", $$); };
expr : 	/* empty */
	| expr ADD term { $$ = $1 + $3;}
	| expr SUB term { $$ = $1 - $3; }
	| term
	;
term :	term MUL factor { $$ = $1*$3; }
	| term DIV factor { $$ = $1/$3; }
	| factor { $$ = $1; }
	;
factor:	NUMBER { $$ = $1; }
	| OBRACE expr CBRACE { $$ = $2; }


%%
