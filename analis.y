%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <sstream>
#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;

ostringstream code, funcs;
vector<int> v;
map<char *, char *> m;
vector<char *> names;
int num_label = 0;
map<char *, char *> refs;
stack<int> if_counter;
stack<int> while_counter;
//map<char *, vector<int *> >funcs;
map<char *, char *> fm;
map<char *, char *> tmp;
map<char *, char *> func_beg;
set<const char *> strings;
bool isString = false;
stack<char *> func_names;
stack<int> curParam;
char *cur_func_decl = NULL;

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

void swap(ostringstream &stream1, ostringstream &stream2)
{
	ostringstream s;
	s << stream1.str();
	stream2.str(stream1.str());
	stream2.str(s.str());
	/*string s = stream1.str();
	stream1.str(stream2.str());
	stream2.str(s);*/
}

class info
{
public:
	info(const char *name, const char *ret_addr, const char *ret_val, int first)
	{
		this->ret_addr = strdup(ret_addr);
		this->ret_val = strdup(ret_val);
		this->name = strdup(name);
		type = NULL;
		this->first = first;
	}
	info(const char *name, const char *ret_addr, const char *ret_val, const char *type, int first)
	{
		this->ret_addr = strdup(ret_addr);
		this->ret_val = strdup(ret_val);
		this->name = strdup(name);
		this->first = first;
		this->type = strdup(type);
	}
	~info()
	{
		free(name);
		free(ret_addr);
		free(ret_val);
		free(type);
	}
	char *name;
	char *ret_addr;
	char *ret_val;
	char *type;
	int first;
};

map<char *, info *> func_info;
stack<info *> infoes;

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
char *match_func_beg(const char *s)
{
	for (map<char *, char *>::iterator i = func_beg.begin(); i != func_beg.end(); i++)
	{
		char *first = (*i).first;
		if (!strcmp(first, s))
		{
			return (*i).second;
		}
	}
	return NULL;
}
info *match_func_info(const char *s)
{
	for (map<char *, info *>::iterator i = func_info.begin(); i != func_info.end(); i++)
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
	isString = false;
	char *s = get_name();
	cout << "INTEGER " << s << ", " << value << endl;
	return v.back();
}
int init_int(char *name)
{
	isString = false;
	char *s = get_name();
	cout << "INTEGER " << s << ", " << 0 << endl;
	move(s, name);
	return v.back();
}
int init_const_string(const char *value)
{
	isString = true;
	strings.insert(value);
	if (!strcmp(value, ""))
	{
		cout << "STRING " << get_name() << ", " << "\"" << value << "\"" << endl;
	}
	else
	{
		if (value[0] == '"') { cout << "STRING " << get_name() << ", " << value << endl; }
		else { cout << "STRING " << get_name() << ", " << "\"" << value << "\"" << endl; }
	}
	return v.back();
}
/*int init_string(char *name)
{
	isString = true;
	strings.insert(value);
	char *s = get_name();
	cout << "STRING " << get_name() << ", " << "" << endl;
	move(s, name);
	return v.back();
}*/
void ternary(const char *s, char *name1, char *name2, char *name3)
{
	code << s << " " << name1 << ", " << name2 << ", " << name3 << "\n";
}
void set_label(const char *name)
{
	code << "LABEL " << name << endl;
}
void addVars(map<char *, char *> &m, const char *str)
{
	if (!strcmp(str, "string"))
	{
		strings.insert(str);
		for (int i = 0; i < names.size(); i++)
		{
			m[names[i]] = itoa(init_const_string(""));
		}
	}
	else
	{
		for (int i = 0; i < names.size(); i++)
		{
			m[names[i]] = itoa(init_int(0));
		}		
	}
	names.clear();
}
void goto_name(const char *name)
{
	code << "GOTO " << name << endl;
}
void goto_label(const char *label)
{
	char *name = itoa(init_const_string(label));
	goto_name(name);
}
	
int main()
{
	funcs << "STRING myVar, \"END\"" << endl;
	funcs << "GOTO myVar" << endl;
	v.push_back(0);
	yyparse();
	funcs << "LABEL END" << endl;
	//cout << code.str();
	cout << funcs.str();
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
decl :		decl_var
		| decl_func
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
			addVars(m, "string");
		}
		| namelist COLON INTEGER SEMICOLON
		{
			addVars(m, "integer");
		}
		;
namelist :	namelist COMA NAME
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
			}
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
decl_func :	NAME COLON INTEGER OBRACE
		{
			swap(code, funcs);
			char *name = get_label();
			func_beg[$1] = name;
			set_label(name);
			char *ret_val = itoa(init_int(0));
			char *ret_addr = itoa(init_const_string(""));
			info *inf = new info($1, ret_addr, ret_val, "integer", v.back() + 1);
			func_info.insert(pair<char *, info *>($1, inf));		
			//func_info[$1] = inf;
			cur_func_decl = $1;
		}		
		chain_param CBRACE func_block
		{
			swap(code, funcs);
		}
		| NAME COLON STRING OBRACE chain_param CBRACE func_block
		;
chain_param : 	chain_param namelist_decl COLON INTEGER
		{
			addVars(fm, "integer");
		}
		| chain_param namelist_decl COLON INTEGER SEMICOLON
		{
			addVars(fm, "integer");
		}
		| chain_param namelist_decl COLON STRING
		{
			addVars(fm, "string");
		}
		| chain_param namelist_decl COLON STRING SEMICOLON
		{
			addVars(fm, "string");
		}
		| namelist_decl COLON INTEGER SEMICOLON
		{
			addVars(fm, "integer");
		}
		| namelist_decl COLON INTEGER
		{
			addVars(fm, "integer");
		}
		| namelist_decl COLON STRING SEMICOLON
		{
			addVars(fm, "string");
		}
		| namelist_decl COLON STRING
		{
			addVars(fm, "string");
		}
		;
namelist_decl : namelist_decl COMA NAME
		{
			names.push_back($3);
		}
		| NAME
		{
			names.push_back($1);
		}
		;
block :		BLOCK commands KCOLB
		;
func_block :	BLOCK
		{
			tmp = m;
			m = fm;
		}		
		program RETURN expr
		{
			info *inf = match_func_info(cur_func_decl);
			char *where = inf->ret_val;
			char *what = itoa(v.back());
			move(what, where);
			free(what);
			where = inf->ret_addr;
			//char *new_name = itoa(init_const_string(""));
			//code << "INDIR " << where << ", " << new_name << endl;
			//goto_name(new_name);
			goto_name(where);
			//cout << "inf: " << inf->ret_val << endl;
			//free(where);
			//ret_val.pop();
			//ret_addr.pop();
			
		}		
		SEMICOLON KCOLB
		{
			m = tmp;
			fm.clear();
		}
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
			else { goto_label(name); }
		}
		;
expr : 		expr MUL expr
		{			
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("MUL", $<string>1, $<string>3, name);
		}
		| expr DIV expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("DIV", $<string>1, $<string>3, name);	
		}
		| expr ADD expr
		{
			char *name;
			if (isString)
			{
				name = itoa(init_const_string(""));
			}
			else
			{
				name = itoa(init_int(0));
			}
			$<string>$ = name;
			ternary("ADD", $<string>1, $<string>3, name);
		}
		| expr SUB expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("SUB", $<string>1, $<string>3, name);	
		}
		| expr AND expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("AND", $<string>1, $<string>3, name);	
		}
		| expr OR expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("OR", $<string>1, $<string>3, name);	
		}
		| expr LT expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("LT", $<string>1, $<string>3, name);	
		}
		| expr LE expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("LE", $<string>1, $<string>3, name);	
		}
		| expr GT expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("GT", $<string>1, $<string>3, name);	
		}
		| expr GE expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("GE", $<string>1, $<string>3, name);	
		}
		| expr EQ expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("EQ", $<string>1, $<string>3, name);	
		}
		| expr NE expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			ternary("NE", $<string>1, $<string>3, name);	
		}
		| NOT expr
		{
			char *name = itoa(init_int(0));
			$<string>$ = name;
			code << "NOT " << $<string>2 << ", " << name << endl;
		}
		| OBRACE expr CBRACE
		{
			$<string>$ = $<string>2;
		}
		| NUMBER
		{
			$<string>$ = itoa(init_int($1));
		}
		| STRINGCONST
		{			
			int num = init_const_string($1);
			char *name = itoa(num);
			$<string>$ = name;
		}
		| STRINGCONST RECOPENBRACE expr RECCLOSEBRACE
		{		
			char *new_name = itoa(init_const_string($<string>1));
			int num = init_const_string("");
			char *name = itoa(num);
			$<string>$ = name;
			code << "IND " << new_name << ", " << itoa(v.back()-2) << ", " << name << endl;
		}
		| NAME
		{
			char *name = match($1);
			if (strings.find(name) == strings.end())
			{
				isString = false;
			}
			else { isString = true; }
			$<string>$ = name;
		}
		| NAME RECOPENBRACE expr RECCLOSEBRACE
		{	
			int num = init_const_string("");
			char *name = itoa(num);
			$<string>$ = name;
			code << "IND " << match($<string>1) << ", " << itoa(v.back()-1) << ", " << name << endl;
		}
		| NAME OBRACE
		{
			//func_names.push($1);
			infoes.push(match_func_info($1));
			curParam.push(infoes.top()->first);
		}
		act_params CBRACE
		{
			int num;
			info *inf = infoes.top();
			if (inf->type == "string")
			{
				num = init_const_string("");
			}
			else
			{
				num = init_int(0);
			}
			//ret_val.push(num);
			char *res_name = itoa(num);
			$<string>$ = res_name;
			char *label_back = get_label();
			char *name = itoa(init_const_string(label_back));
			move(name, inf->ret_addr);
			goto_label(match_func_beg(inf->name));
			set_label(label_back);
			move(inf->ret_val, res_name);
			curParam.pop();
			infoes.pop();
		}
		;
act_params :	act_params COMA expr
		{
			//char *name = itoa(v.back());
			char *name = $<string>3;
			$<string>$ = $<string>3;
			char *dest = itoa(curParam.top());
			move(name, dest);
			free(dest);
			curParam.top()++;
		}
		| expr
		{
			//char *name = itoa(v.back());
			char *name = $<string>1;
			$<string>$ = $<string>1;
			char *dest = itoa(curParam.top());
			move(name, dest);
			free(dest);
			curParam.top()++;
		}
		;
control :	cond
		| cycle
		;
cond :		IF expr
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
		WHILE expr
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
