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
	{DIGIT}+		{ printf("NUMBER "); yylval = atoi(yytext); return NUMBER; }
	"*"			{ printf("MULT "); return MUL; }
	"+"			{ printf("ADD "); return ADD; }
	"-"			{ printf("SUB "); return SUB; }
	"/"			{ printf("DIV "); return DIV; }
}

%%

/*int main()
{
	yylex();
	return 0;
}*/
