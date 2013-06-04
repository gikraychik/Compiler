%{
#include <stdio.h>
#include <string.h>
#define YYSTYPE char *

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


%token DIGIT
%token LETTER


%%
expr : 	/* empty */
	| expr DIGIT { printf("%s", yylval); }
	| expr LETTER { printf("%s", yylval); }
	;


%%
