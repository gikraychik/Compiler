%{
#include <stdio.h>
#include "analis.tab.h"
%}

%option noyywrap 
%option yylineno
%option stack

DIGIT [0-9]
NAME [a-zA-Z][a-zA-Z0-9]*
LABELNAME [a-zA-Z0-9]+
QUOTE [\"]
STRINGCONST {QUOTE}[a-zA-Z0-9]+{QUOTE}
WS [ \t\n]+
WSN [ \t\n]*
DELIM {WS}|[;]

%%
<INITIAL>
{
	{DIGIT}+{WSN}				{ yylval.number = atoi(yytext); printf("NUMBER "); return NUMBER; }
	{STRINGCONST}{WSN}			{ yylval.string = strdup(yytext); printf("STRINGCONST "); return STRINGCONST; }
	"if"{WS}				{ printf("IF "); return IF; }	
	"==>"{WS}				{ printf("THEN "); return THEN; }
	"!=>"{WS}				{ printf("ELSE "); return ELSE; }
	"while"{WS}				{ printf("WHILE "); return WHILE; }
	"loop"{WS}				{ printf("LOOP "); return LOOP; }
	"pool"{WS}				{ printf("POOL "); return POOL; }
	"block"{WS}				{ printf("BLOCK "); return BLOCK; }
	"kcolb"{WS}				{ printf("KCOLB "); return KCOLB; }
	"goto"{WS}				{ printf("GOTO "); return GOTO; }
	"write"{WSN}/"("			{ printf("WRITE "); return WRITE; }
	"read"{WSN}/"("				{ printf("READ "); return READ; }
	"string"{WSN}				{ printf("STRING "); return STRING; }
	"integer"{WSN}				{ printf("INTEGER "); return INTEGER; }
	"label"{WS}				{ printf("LABEL "); return LABEL; }
	"return"{WS}				{ printf("RETURN "); return RETURN; }
	"["{WSN}				{ printf("RECOPENBRACE "); return RECOPENBRACE; }
	"]"{WSN}				{ printf("RECCLOSEBRACE "); return RECCLOSEBRACE; }
	"<"{WSN}				{ printf("LT "); return LT; }
	"<="{WSN}				{ printf("LE "); return LE; }
	">"{WSN}				{ printf("GT "); return GT; }
	">="{WSN}				{ printf("GE "); return GE; }
	"=="{WSN}				{ printf("EQ "); return EQ; }
	"!="{WSN}				{ printf("NE "); return NE; }
	"&&"{WSN}				{ printf("AND "); return AND; }
	"||"{WSN}				{ printf("OR "); return OR; }
	"!"{WSN}				{ printf("NOT "); return NOT; }
	"+"{WSN}				{ printf("ADD "); return ADD; }
	"-"{WSN}				{ printf("SUB "); return SUB; }
	"*"{WSN}				{ printf("MUL "); return MUL; }
	"/"{WSN}				{ printf("DIV "); return DIV; }		
	"->"{WSN}				{ printf("REF "); return REF; }
	":="{WSN}				{ printf("ASSIGN "); return ASSIGN; }
	":"{WSN}				{ printf("COLON "); return COLON; }
	";"{WSN}				{ printf("SEMICOLON "); return SEMICOLON; }
	","{WSN}				{ printf("COMA "); return COMA; }
	"("{WSN}				{ printf("OBRACE "); return OBRACE; }
	")"{WSN}				{ printf("CBRACE "); return CBRACE; }
	{NAME}{WSN}				{ yylval.string = strdup(yytext); printf("NAME "); return NAME; }				
}

%%

/*int main()
{
	yylex();
	return 0;
}*/
