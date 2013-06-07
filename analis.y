%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <sstream>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

ostringstream code;
vector<int> v;
map<char *, char *> m;
vector<char *> names;
int num_label = 0;
map<char *, char *> refs;
stack<int> if_counter;
stack<int> while_counter;
map<char *, vector<int *> >funcs;

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
	code << "MOVE " << name1 << ", " << name2 << endl;
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
	if (!strcmp(value, ""))
	{
		cout << "STRING " << get_name() << ", " << "\"" << value << "\"" << endl;
	}
	else
	{
		cout << "STRING " << get_name() << ", " << value << endl;
	}
	return v.back();
}
int init_string(char *name)
{
	char *s = get_name();
	cout << "STRING " << get_name() << ", " << "" << endl;
	move(s, name);
	return v.back();
}
void ternary(const char *s, char *name1, char *name2, char *name3)
{
	code << s << " " << name1 << ", " << name2 << ", " << name3 << "\n";
}
void set_label(const char *name)
{
	code << "LABEL " << name << endl;
}
int main()
{
	v.push_back(0);
	yyparse();
	cout << code.str();
}
%}

%union
{
	int number;
	char *string;
}

%token <number>NUMBER <string>NAME <string>LABELNAME REF COLON SEMICOLON DELIM <string>STRINGCONST QUOTE STRING INTEGER COMA RETURN ASSIGN
%token IF WHILE LOOP POOL READ WRITE EOFF
%token LABEL RECOPENBRACE RECCLOSEBRACE
%token BLOCK KCOLB THEN ELSE GOTO OBRACE CBRACE

%left AND OR
%left NOT
%left LT GT LE GE EQ NE
%left ADD SUB
%left MUL DIV

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
			for (int i = 0; i < names.size(); i++)
			{
				m[names[i]] = itoa(init_const_string(""));
			}
			names.clear();
		}
		| namelist COLON INTEGER SEMICOLON
		{
			for (int i = 0; i < names.size(); i++)
			{
				m[names[i]] = itoa(init_int(0));
			}
			names.clear();
		}
		;
namelist : 	namelist COMA NAME
		{
			char *internal_name = match($3);
			if (internal_name == NULL)
			{
				names.push_back($3);
			}
		}
		| NAME
		{
			char *internal_name = match($1);
			if (internal_name == NULL)
			{
				names.push_back($1);
			};
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
			set_label(name);
		}
		;
decl_func :	NAME COLON type OBRACE chain_param CBRACE func_block
		{
			funcs[$1] = new vector<int>();
		}
		;
chain_param : 	decl_list namelist COLON INTEGER
		{
		}
		| decl_list namelist COLON STRING
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
			move($<string>3, match($1));
		}
		;
io :		READ OBRACE NAME CBRACE SEMICOLON
		{
			code << "READ " << match($3) << endl;
		}
		| WRITE OBRACE NAME CBRACE SEMICOLON
		{
			code << "WRITE " << match($3) << endl;
		}
		| WRITE OBRACE NUMBER CBRACE SEMICOLON
		{
			code << "WRITE " << $3 << endl;
		}
		;
goto : 		GOTO NAME SEMICOLON
		{
			char *name = match($2);
			if (name == NULL) { code << "GOTO " << "" << endl; }
			else { code << "GOTO " << name << endl; }
		}
		;
expr : 		string_expr
		{
			$<string>$ = $<string>1;
		}
		| int_expr
		{
			$<string>$ = $<string>1;
		}
		;
int_expr :	int_expr MUL int_expr
		{			
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("MUL", $<string>1, $<string>3, name);
		}
		| int_expr DIV int_expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("DIV", $<string>1, $<string>3, name);	
		}
		| int_expr ADD int_expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("ADD", $<string>1, $<string>3, name);
		}
		| int_expr SUB int_expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("SUB", $<string>1, $<string>3, name);	
		}
		| int_expr AND int_expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("AND", $<string>1, $<string>3, name);	
		}
		| int_expr OR int_expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("OR", $<string>1, $<string>3, name);	
		}
		| int_expr LT int_expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("LT", $<string>1, $<string>3, name);	
		}
		| int_expr LE int_expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("LE", $<string>1, $<string>3, name);	
		}
		| int_expr GT int_expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("GT", $<string>1, $<string>3, name);	
		}
		| int_expr GE int_expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("GE", $<string>1, $<string>3, name);	
		}
		| int_expr EQ int_expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("EQ", $<string>1, $<string>3, name);	
		}
		| int_expr NE int_expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("NE", $<string>1, $<string>3, name);	
		}
		| NOT int_expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			code << "NOT " << $<string>2 << ", " << name << endl;
		}
		| OBRACE int_expr CBRACE
		{
			$<string>$ = $<string>2;
		}
		| NUMBER
		{
			$<string>$ = itoa(init_int($1));
		}
		| NAME
		{
			$<string>$ = match($1);
		}
		;
string_expr :	string_expr ADD string_factor
		{
			int num = init_const_string("");
			char *name = itoa(num);
			$<string>$ = name;
			ternary("ADD", $<string>1, $<string>3, name);
		}
		| string_factor
		{
			$<string>$ = $<string>1;
		}
		;
string_factor :	OBRACE string_expr CBRACE
		{
			$<string>$ = $<string>2;
		}
		| STRINGCONST
		{			
			int num = init_const_string($1);
			char *name = itoa(num);
			$<string>$ = name;
		}
		| STRINGCONST RECOPENBRACE int_expr RECCLOSEBRACE
		{			
			int num = init_const_string("");
			char *name = itoa(num);
			$<string>$ = name;
			code << "IND " << match($<string>1) << ", " << itoa(v.back()-1) << ", " << name << endl;
		}
		| NAME
		{
			$<string>$ = match($1);
		}
		| NAME RECOPENBRACE int_expr RECCLOSEBRACE
		{			
			int num = init_const_string("");
			char *name = itoa(num);
			$<string>$ = name;
			code << "IND " << match($<string>1) << ", " << itoa(v.back()-1) << ", " << name << endl;
		}
		;
control :	cond
		| cycle
		;
cond :		IF int_expr
		{
			char *name_var = itoa(v.back());
			char *name_label = get_label();
			code << "BRANCH " << name_var << ", " << name_label << endl;
			free(name_var);
			//free(name_label);
			//name_label = get_label();
			code << "GOTO " << get_label() << endl;
			set_label(name_label);
			//free(name_label);
			if_counter.push(num_label);
		}		
		THEN block
		{
			char *name_label = get_label();
			code << "GOTO " << name_label << endl;
			int first = if_counter.top();
			name_label = itoa(first);
			name_label[0] = 'b';
			set_label(name_label);
			if_counter.push(num_label);
			free(name_label);
		}
		ELSE block
		{
			char *name_label = itoa(if_counter.top());
			name_label[0] = 'b';
			set_label(name_label);
			for (int i = 0; i < 2; i++) { if_counter.pop(); }
		}
		;
cycle :		{
			char *name = get_label();
			while_counter.push(num_label);
			set_label(name);
		}
		WHILE int_expr
		{
			char *var_name = itoa(v.back());
			char *name = itoa(init_int(0));
			code << "NOT " << var_name << ", " << name << endl;
			free(var_name);
			var_name = strdup(name);
			free(name);
			name = get_label();
			while_counter.push(num_label);
			code << "BRANCH " << var_name << ", " << name << endl;
			free(var_name);
		}
		LOOP commands POOL
		{
			char *first = itoa(while_counter.top());
			while_counter.pop();
			char *second = itoa(while_counter.top());
			while_counter.pop();
			first[0] = 'b';
			second[0] = 'b';
			code << "GOTO " << second << endl;
			set_label(first);
			free(first);
			free(second);
		}
		;


%%
