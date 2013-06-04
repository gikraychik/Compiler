%{
#include <stdio.h>
#include "analis.tab.h"
%}

%option noyywrap 
%option yylineno
%option stack

DIGIT [0-9]

%%
<INITIAL>
{
	DIGIT		{ yylval = "digit\n"; return DIGIT; }
	"a"		{ yylval = "letter a\n"; return LETTER; }
	"b"		{ yylval = "letter b\n"; return LETTER; }
}
%%

/*int main()
{
	yylex();
	return 0;
}*/
