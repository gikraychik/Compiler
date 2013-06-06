%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <iostream>
#include <vector>

using namespace std;

vector<int> v;
map<char *, char *> m;
vector<char *> names;

extern "C"
{
	int yyparse(void);
	int yylex(void);
	int yywrap()
	{
		return 1;
	}
}
void yyerror(const char *s)
{
	fprintf(stderr, "Unexpected error: %s\n", s);
}

/*int yywrap()
{
	return 1;
}*/
void move(char *name1, char *name2)
{
	cout << "MOVE " << name1 << ", " << name2 << endl;
}
void reverse(char s[])
{
	int i, j;
	char c;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
	{
		c = s[i]; s[i] = s[j]; s[j] = c;
	}
}
char *itoa(int n)
{
	char *s = (char *)malloc(5*sizeof(char));
	int i = 0;
	do {
	s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	s[i++] = 'a';
	s[i] = '\0';
	reverse(s);
	return s;
}
char *get_name()
{
	v.back()++;
	char *res = itoa(v.back());
	return res;
}
char *match(const char *s)
{
	for (map<char *, char *>::iterator i = m.begin(); i != m.end(); i++)
	{
		char *first = (*i).first;
		if (!strcmp(first, s))
		{
			return (*i).second;
		}
	}
	return NULL;
}
int init_int(int value)
{
	char *s = get_name();
	cout << "INTEGER " << s << ", " << value << endl;
	return v.back();
}
int init_int(char *name)
{
	char *s = get_name();
	cout << "INTEGER " << s << ", " << 0 << endl;
	move(s, name);
	return v.back();
}
int main()
{
	v.push_back(0);
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
		{
			cout << "STRING";
		}
		| INTEGER
		{
			cout << "INTEGER";
		}
		;
decl_var :	namelist COLON STRING SEMICOLON
		{

		}
		| namelist COLON INTEGER SEMICOLON
		{
			for (int i = 0; i < names.size(); i++)
			{
				m.insert(pair<char *, char *>(names[i], itoa(init_int(0))));
				//m[names[i]] = itoa(init_int(0));
			}
			names.clear();
		}
		;
namelist : 	namelist COMA NAME
		{
			names.push_back($3);
		}
		| NAME
		{
			names.push_back($1);
		}
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
		{
			//move(itoa(v.back()), m[$1]);
			move($<string>3, match($1));
		}
		;
io :		READ OBRACE NAME CBRACE SEMICOLON
		| WRITE OBRACE NAME CBRACE SEMICOLON
		| WRITE OBRACE NUMBER CBRACE SEMICOLON
		;
goto : 		GOTO LABELNAME SEMICOLON
		;
expr : 		string_expr
		| int_expr
		{
			$<string>$ = $<string>1;
		}
		| bool_expr
		;
int_expr :	int_expr ADD int_term
		{
			int num = init_int(0);
			char *name = itoa(num);
			$<string>$ = name;
			cout << "ADD	 " << $<string>1 << ", " << $<string>3 << ", " << name << endl;	
		}
		| int_expr SUB int_term
		{
			int num = init_int(0);
			char *name = itoa(num);
			$<string>$ = name;
			cout << "SUB " << $<string>1 << ", " << $<string>3 << ", " << name << endl;	
		}
		| int_term
		{
			$<string>$ = $<string>1;
		}
		;
int_term :	int_term MUL int_factor
		{
			int num = init_int(0);
			char *name = itoa(num);
			$<string>$ = name;
			cout << "MUL " << $<string>1 << ", " << $<string>3 << ", " << name << endl;	
		}
		| int_term DIV int_factor
		{
			int num = init_int(0);
			char *name = itoa(num);
			$<string>$ = name;
			cout << "DIV " << $<string>1 << ", " << $<number>3 << ", " << name << endl;	
		}
		| int_factor
		{
			$<string>$ = $<string>1;
		}
		;
int_factor :	NUMBER
		{
			int num = init_int($1);
			$<string>$ = itoa(num);
		}
		| NAME
		{
			$<string>$ = match($1);
			cout << "Testing: " << match($1) << endl;
		}
		| OBRACE int_expr CBRACE
		{
			$<string>$ = $<string>2;
		}
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
