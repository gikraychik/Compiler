%{
#include <stdio.h>
#include "analis.tab.h"
%}

%option noyywrap 
%option yylineno
%option stack

DIGIT [0-9]

%%
<INITIAL>{
	[ \t]			{ }
	{DIGIT}+		{ yylval = atoi(yytext); return NUMBER; }
	"*"			{ return MUL; }
	"+"			{ return ADD; }
	"-"			{ return SUB; }
	"/"			{ return DIV; }
}

%%

/*int main()
{
	yylex();
	return 0;
}*/
