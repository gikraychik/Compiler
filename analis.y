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

%union
{
	int number;
	char *string;
}

%token <number>NUMBER <string>NAME <string>LABELNAME REF COLON SEMICOLON DELIM <string>STRINGCONST QUOTE STRING INTEGER COMA RETURN ASSIGN
%token LT LE GT GE EQ NE OR AND NOT IF WHILE LOOP POOL READ WRITE
%token LABEL RECOPENBRACE RECCLOSEBRACE
%token BLOCK KCOLB THEN ELSE GOTO ADD SUB MUL DIV OBRACE CBRACE

%%
program : 	/* empty */
		| commands
		;
commands : 	commands command
		| command
		;
command :	decl
		| action
		| control
		;
decl :		decl_func
		| decl_var
		| decl_ref
		| decl_label
		;
type :		STRING
		| INTEGER
		;
decl_var :	namelist COLON type SEMICOLON
		;
namelist : 	namelist COMA NAME
		| NAME
		;
decl_ref :	NAME REF NAME COLON type
		;
decl_label :	LABEL LABELNAME SEMICOLON
		;
decl_func :	NAME COLON type OBRACE chain_param CBRACE func_block
		;
chain_param : 	decl_list namelist COLON type
		;
decl_list :	decl_list decl_var
		| decl_var
		;
block :		BLOCK commands KCOLB
		;
func_block :	BLOCK commands RETURN expr SEMICOLON KCOLB
		;
action :	assign
		| io
		| goto
		;
assign :	NAME ASSIGN expr SEMICOLON
		;
io :		READ OBRACE NAME CBRACE SEMICOLON
		| WRITE OBRACE NAME CBRACE SEMICOLON
		| WRITE OBRACE NUMBER CBRACE SEMICOLON
		;
goto : 		GOTO LABELNAME SEMICOLON
		;
expr : 		string_expr
		| int_expr
		| bool_expr
		;
int_expr :	int_expr ADD int_term
		| int_expr SUB int_term
		| int_term
		;
int_term :	int_term MUL int_factor
		| int_term DIV int_factor
		| int_factor
		;
int_factor :	NUMBER
		| NAME
		| OBRACE int_expr CBRACE
		| NAME OBRACE act_params CBRACE
		;
act_params :	namelist COMA NAME
		| namelist COMA NUMBER
		| namelist COMA STRING
		| NAME
		| NUMBER
		| STRING
		;
bool_expr :	bool_expr OR bool_term
		| bool_term
		;
bool_term :	bool_term AND bool_factor
		| bool_factor
		;
bool_factor :	OBRACE bool_expr CBRACE
		| int_expr LT int_expr
		| int_expr LE int_expr
		| int_expr GT int_expr
		| int_expr GE int_expr
		| int_expr EQ int_expr
		| int_expr NE int_expr
		| NAME			
		| NOT bool_expr
		;
string_expr :	string_expr ADD string_factor
		| string_factor
		;
string_factor :	OBRACE string_factor CBRACE
		| STRINGCONST
		| STRINGCONST RECOPENBRACE int_expr RECCLOSEBRACE
		| NAME
		| NAME RECOPENBRACE int_expr RECCLOSEBRACE
		;
control :	cond
		| cycle
		;
cond :		IF bool_expr THEN block ELSE block
		;
cycle :		WHILE bool_expr LOOP commands POOL
		;


%%
