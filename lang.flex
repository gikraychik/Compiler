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
	{DIGIT}+"."{DIGIT}+	{ printf("Float: %s (%f)\n", yytext, yylval); yylval = atof(yytext); return NUMBER; }
	{DIGIT}+		{ printf("Int: %s (%f)\n", yytext, yylval); yylval = atof(yytext); return NUMBER; }
	"*"			{ return MUL; }
	"+"			{ return ADD; }
	"-"			{ return SUB; }
	"/"			{ return DIV; }
	"("			{ return OBRACE; }
	")"			{ return CBRACE; }
}

%%

/*int main()
{
	yylex();
	return 0;
}*/
