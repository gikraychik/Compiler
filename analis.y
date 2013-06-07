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
int num_label = 0;
map<char *, char *> refs;

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
char *get_label()
{
	num_label++;
	char * res = itoa(num_label);
	res[0] = 'b';
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
char *match_ref(const char *internal_name)
{
	for (map<char *, char *>::iterator i = refs.begin(); i != refs.end(); i++)
	{
		char *first = (*i).first;
		if (!strcmp(first, internal_name))
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
int init_const_string(const char *value)
{
	cout << "STRING " << get_name() << ", " << "\"" << value << "\"" << endl;
	return v.back();
}
int init_string(char *name)
{
	char *s = get_name();
	cout << "STRING " << get_name() << ", " << "" << endl;
	move(s, name);
	return v.back();
}
void ternary(char *s, char *name1, char *name2, char *name3)
{
	cout << s << " " << name1 << ", " << name2 << ", " << name3 << "\n";
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
		{}
		| INTEGER
		{}
		;
decl_var :	namelist COLON STRING SEMICOLON
		{

		}
		| namelist COLON INTEGER SEMICOLON
		{
			for (int i = 0; i < names.size(); i++)
			{
				//m.insert(pair<char *, char *>(names[i], itoa(init_int(0))));
				m[names[i]] = itoa(init_int(0));
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
decl_ref :	NAME REF NAME COLON type SEMICOLON
		{
			char *internal_name = get_name();
			m[$1] = internal_name;
			char *image = match($3);
			refs[internal_name] = image;
			cout << "STRING " << internal_name << ", " << "\"" << image << "\"" << endl;
		}
		;
decl_label :	LABEL NAME SEMICOLON
		{
			char *name = get_label();
			m[$2] = name;
			cout << "LABEL " << name << endl;
		}
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
goto : 		GOTO NAME SEMICOLON
		{
			cout << "GOTO " << match($2) << endl;
		}
		;
expr : 		string_expr
		| int_expr
		{
			$<string>$ = $<string>1;
		}
		;
int_expr :	int_expr LT int_expr
		{
			int num = init_int(0);
			char *name = itoa(num);
			$<string>$ = name;
			ternary("LT", $<string>1, $<string>3, name);
		}
		int_expr GT int_expr
		{
			int num = init_int(0);
			char *name = itoa(num);
			$<string>$ = name;
			ternary("GT", $<string>1, $<string>3, name);
		}
		int_expr LE int_expr
		{
			int num = init_int(0);
			char *name = itoa(num);
			$<string>$ = name;
			ternary("LE", $<string>1, $<string>3, name);
		}
		int_expr GE int_expr
		{
			int num = init_int(0);
			char *name = itoa(num);
			$<string>$ = name;
			ternary("GE", $<string>1, $<string>3, name);
		}
		int_expr EQ int_expr
		{
			int num = init_int(0);
			char *name = itoa(num);
			$<string>$ = name;
			ternary("EQ", $<string>1, $<string>3, name);
		}
		int_expr NE int_expr
		{
			int num = init_int(0);
			char *name = itoa(num);
			$<string>$ = name;
			ternary("NE", $<string>1, $<string>3, name);
		}
		| int_expr_1
		{
			$<string>$ = $<string>1;
		}
		| OBRACE int_expr CBRACE
		{
			$<string>$ = $<string>2;
		}
		;
int_expr_1 :	int_expr_1 OR int_expr_2
		{
			int num = init_int(0);
			char *name = itoa(num);
			$<string>$ = name;
			ternary("OR", $<string>1, $<string>3, name);
		}
		| int_expr_2
		{
			$<string>$ = $<string>1;
		}
		| OBRACE int_expr CBRACE
		{
			$<string>$ = $<string>2;
		}
		;
int_expr_2 :	int_expr_2 AND int_expr_3
		{
			int num = init_int(0);
			char *name = itoa(num);
			$<string>$ = name;
			ternary("AND", $<string>1, $<string>3, name);
		}
		| int_expr_3
		{
			$<string>$ = $<string>1;
		}
		| OBRACE int_expr CBRACE
		{
			$<string>$ = $<string>2;
		}
		;
int_expr_3 :	int_expr_3 ADD int_term
		{
			int num = init_int(0);
			char *name = itoa(num);
			$<string>$ = name;
			//cout << "ADD " << $<string>1 << ", " << $<string>3 << ", " << name << endl;
			ternary("ADD", $<string>1, $<string>3, name);
		}
		| int_expr_3 SUB int_term
		{
			int num = init_int(0);
			char *name = itoa(num);
			$<string>$ = name;
			//cout << "SUB " << $<string>1 << ", " << $<string>3 << ", " << name << endl;
			ternary("SUB", $<string>1, $<string>3, name);
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
			//cout << "MUL " << $<string>1 << ", " << $<string>3 << ", " << name << endl;
			ternary("MUL", $<string>1, $<string>3, name);	
		}
		| int_term DIV int_factor
		{
			int num = init_int(0);
			char *name = itoa(num);
			$<string>$ = name;
			//cout << "DIV " << $<string>1 << ", " << $<number>3 << ", " << name << endl;
			ternary("DIV", $<string>1, $<string>3, name);	
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
			char *internal_name = match($1);
			char *ref = match_ref(internal_name);
			if (ref == NULL) { $<string>$ = internal_name; }
			else
			{
				//cout << "LOL:" << *(ref+1) << endl; 
				$<string>$ = ref;
			}
			//cout << "Testing: " << match($1) << endl;
		}
		| OBRACE int_expr_3 CBRACE
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
		{
			int num = init_int(0);
			char *name = itoa(num);
			$<string>$ = name;
			cout << "OR " << $<string>1 << ", " << $<string>3 << ", " << name << endl;	
		}
		| bool_term
		{
			$<string>$ = $<string>1;
		}
		;
bool_term :	bool_term AND bool_factor
		{
			int num = init_int(0);
			char *name = itoa(num);
			$<string>$ = name;
			cout << "AND " << $<string>1 << ", " << $<string>3 << ", " << name << endl;
		}
		| bool_factor
		{
			$<string>$ = $<string>1;
		}
		;
bool_factor :	OBRACE bool_expr CBRACE
		{
			$<string>$ = $<string>2;
		}
		| int_expr LT int_expr
		{
			
		}
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
