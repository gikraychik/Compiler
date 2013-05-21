/* A Bison parser, made by GNU Bison 2.6.1.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.6.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 336 of yacc.c  */
#line 1 "analis.y"

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

ostringstream *code, *funcs;
vector<int> v;
map<char *, char *> m;
vector<char *> names;
int num_label = 0;
map<char *, char *> refs;
stack<int> if_counter;
stack<int> while_counter;
map<char *, char *> fm;
map<char *, char *> tmp;
map<char *, char *> func_beg;
set<const char *> strings;
bool isString = false;
stack<char *> func_names;
stack<int> curParam;
char *cur_func_decl = NULL;
int param_num = 0;
stack<vector<char *> *> real_params;  //names
char *last_expr_name = 0;

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

void swap(ostringstream *&stream1, ostringstream *&stream2)
{
	ostringstream *s = stream1;
	stream1 = stream2;
	stream2 = s;
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
	vector<int> v;
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
	*code << "MOVE " << name1 << ", " << name2 << endl;
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
	if (refs.empty()) { return NULL; }
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
	char *name = get_name();
	strings.insert(name);
	if (!strcmp(value, ""))
	{
		cout << "STRING " << name << ", " << "\"" << value << "\"" << endl;
	}
	else
	{
		if (value[0] == '"') { cout << "STRING " << name << ", " << value << endl; }
		else { cout << "STRING " << name << ", " << "\"" << value << "\"" << endl; }
	}
	return v.back();
}
void ternary(const char *s, char *name1, char *name2, char *name3)
{
	*code << s << " " << name1 << ", " << name2 << ", " << name3 << "\n";
}
void set_label(const char *name)
{
	*code << "LABEL " << name << endl;
}
void addVars(map<char *, char *> &m, const char *str)
{
	if (!strcmp(str, "string"))
	{
		//strings.insert(str);
		char *name;
		for (int i = 0; i < names.size(); i++)
		{
			name = itoa(init_const_string(""));
			m[names[i]] = name;
			//strings.insert(name);
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
	*code << "GOTO " << name << endl;
}
void goto_label(const char *label)
{
	char *name = itoa(init_const_string(label));
	goto_name(name);
}
bool hasItem(int x, vector<int> &v)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] == x) { return true; }
	}
	return false;
}
char *real_name(char *name)
{
	if (name == NULL) { return NULL; }
	char *res = match_ref(name);
	if (res == NULL) { return name; }
	return res;
}
void in_chain_param(const char *type, char *param)
{
	names.push_back(param);
	info *inf = infoes.top();
	inf->v.push_back(param_num);
	param_num++;
	addVars(fm, type);
}
bool inStrings(char *name)
{
	for (set<const char *>::iterator i = strings.begin(); i != strings.end(); i++)
	{
		if (!strcmp(*i, name)) { return true; }
	}
	return false;
}
int main()
{
	code = new ostringstream();
	funcs = new ostringstream();
	cout << "STRING myVar, \"END\"" << endl;
	*funcs << "GOTO myVar" << "\n";
	v.push_back(0);
	yyparse();
	*funcs << "LABEL END" << endl;
	cout << (*code).str();
	cout << (*funcs).str();
}

/* Line 336 of yacc.c  */
#line 366 "analis.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "analis.tab.h".  */
#ifndef YY_ANALIS_TAB_H
# define YY_ANALIS_TAB_H
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     NAME = 259,
     REF = 260,
     COLON = 261,
     SEMICOLON = 262,
     STRINGCONST = 263,
     STRING = 264,
     INTEGER = 265,
     COMA = 266,
     RETURN = 267,
     ASSIGN = 268,
     IF = 269,
     WHILE = 270,
     LOOP = 271,
     POOL = 272,
     READ = 273,
     WRITE = 274,
     LABEL = 275,
     RECOPENBRACE = 276,
     RECCLOSEBRACE = 277,
     BLOCK = 278,
     KCOLB = 279,
     THEN = 280,
     ELSE = 281,
     GOTO = 282,
     OBRACE = 283,
     CBRACE = 284,
     OR = 285,
     AND = 286,
     NOT = 287,
     NE = 288,
     EQ = 289,
     GE = 290,
     LE = 291,
     GT = 292,
     LT = 293,
     SUB = 294,
     ADD = 295,
     DIV = 296,
     MUL = 297
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 350 of yacc.c  */
#line 300 "analis.y"

	int number;
	char *string;


/* Line 350 of yacc.c  */
#line 457 "analis.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_ANALIS_TAB_H  */

/* Copy the second part of user declarations.  */

/* Line 353 of yacc.c  */
#line 485 "analis.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  38
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   221

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNRULES -- Number of states.  */
#define YYNSTATES  172

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   297

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     6,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    29,    34,    39,    43,    45,
      52,    56,    57,    66,    67,    76,    77,    85,    86,    94,
      99,   105,   110,   116,   123,   129,   135,   142,   147,   153,
     158,   163,   167,   172,   176,   180,   182,   186,   188,   189,
     190,   199,   201,   203,   205,   210,   216,   222,   226,   228,
     232,   236,   240,   244,   248,   252,   256,   260,   264,   268,
     272,   276,   279,   283,   285,   287,   292,   294,   299,   300,
     306,   307,   311,   313,   315,   317,   318,   319,   328,   329,
     330
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      44,     0,    -1,    -1,    45,    -1,    45,    46,    -1,    46,
      -1,    47,    -1,    64,    -1,    72,    -1,    49,    -1,    53,
      -1,    51,    -1,    52,    -1,     9,    -1,    10,    -1,    50,
       6,     9,     7,    -1,    50,     6,    10,     7,    -1,    50,
      11,     4,    -1,     4,    -1,     4,     5,     4,     6,    48,
       7,    -1,    20,     4,     7,    -1,    -1,     4,     6,    10,
      28,    54,    58,    29,    61,    -1,    -1,     4,     6,     9,
      28,    55,    58,    29,    61,    -1,    -1,     4,     6,     9,
      28,    56,    29,    61,    -1,    -1,     4,     6,    10,    28,
      57,    29,    61,    -1,    58,    59,     6,    10,    -1,    58,
      59,     6,    10,     7,    -1,    58,    59,     6,     9,    -1,
      58,    59,     6,     9,     7,    -1,    58,     4,     5,     6,
      10,     7,    -1,    58,     4,     5,     6,    10,    -1,    58,
       4,     5,     6,     9,    -1,    58,     4,     5,     6,     9,
       7,    -1,     4,     5,     6,    10,    -1,     4,     5,     6,
      10,     7,    -1,     4,     5,     6,     9,    -1,    59,     6,
      10,     7,    -1,    59,     6,    10,    -1,    59,     6,     9,
       7,    -1,    59,     6,     9,    -1,    59,    11,     4,    -1,
       4,    -1,    23,    45,    24,    -1,    46,    -1,    -1,    -1,
      23,    62,    44,    12,    68,    63,     7,    24,    -1,    65,
      -1,    66,    -1,    67,    -1,     4,    13,    68,     7,    -1,
      18,    28,     4,    29,     7,    -1,    19,    28,    68,    29,
       7,    -1,    27,     4,     7,    -1,    69,    -1,    69,    42,
      69,    -1,    69,    41,    69,    -1,    69,    40,    69,    -1,
      69,    39,    69,    -1,    69,    31,    69,    -1,    69,    30,
      69,    -1,    69,    38,    69,    -1,    69,    36,    69,    -1,
      69,    37,    69,    -1,    69,    35,    69,    -1,    69,    34,
      69,    -1,    69,    33,    69,    -1,    32,    69,    -1,    28,
      69,    29,    -1,     3,    -1,     8,    -1,     8,    21,    69,
      22,    -1,     4,    -1,     4,    21,    69,    22,    -1,    -1,
       4,    28,    70,    71,    29,    -1,    -1,    71,    11,    68,
      -1,    68,    -1,    73,    -1,    76,    -1,    -1,    -1,    14,
      68,    74,    25,    60,    75,    26,    60,    -1,    -1,    -1,
      77,    15,    68,    78,    16,    45,    17,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   317,   317,   318,   320,   321,   323,   324,   325,   327,
     328,   329,   330,   332,   332,   334,   338,   343,   351,   360,
     369,   377,   376,   399,   398,   420,   419,   441,   440,   463,
     467,   471,   475,   479,   483,   487,   491,   495,   499,   503,
     507,   511,   515,   519,   524,   529,   535,   536,   539,   544,
     538,   559,   560,   561,   563,   568,   572,   579,   586,   593,
     599,   605,   620,   626,   632,   638,   644,   650,   656,   662,
     668,   674,   680,   684,   688,   694,   702,   714,   722,   721,
     766,   767,   785,   804,   805,   808,   824,   807,   843,   849,
     843
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "NAME", "REF", "COLON",
  "SEMICOLON", "STRINGCONST", "STRING", "INTEGER", "COMA", "RETURN",
  "ASSIGN", "IF", "WHILE", "LOOP", "POOL", "READ", "WRITE", "LABEL",
  "RECOPENBRACE", "RECCLOSEBRACE", "BLOCK", "KCOLB", "THEN", "ELSE",
  "GOTO", "OBRACE", "CBRACE", "OR", "AND", "NOT", "NE", "EQ", "GE", "LE",
  "GT", "LT", "SUB", "ADD", "DIV", "MUL", "$accept", "program", "commands",
  "command", "decl", "type", "decl_var", "namelist", "decl_ref",
  "decl_label", "decl_func", "$@1", "$@2", "$@3", "$@4", "chain_param",
  "namelist_decl", "block", "func_block", "$@5", "$@6", "action", "assign",
  "io", "goto", "expr", "mexpr", "$@7", "act_params", "control", "cond",
  "$@8", "$@9", "cycle", "$@10", "$@11", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    44,    45,    45,    46,    46,    46,    47,
      47,    47,    47,    48,    48,    49,    49,    50,    50,    51,
      52,    54,    53,    55,    53,    56,    53,    57,    53,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    59,    59,    60,    60,    62,    63,
      61,    64,    64,    64,    65,    66,    66,    67,    68,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    70,    69,
      71,    71,    71,    72,    72,    74,    75,    73,    77,    78,
      76
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     4,     3,     1,     6,
       3,     0,     8,     0,     8,     0,     7,     0,     7,     4,
       5,     4,     5,     6,     5,     5,     6,     4,     5,     4,
       4,     3,     4,     3,     3,     1,     3,     1,     0,     0,
       8,     1,     1,     1,     4,     5,     5,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     3,     1,     1,     4,     1,     4,     0,     5,
       0,     3,     1,     1,     1,     0,     0,     8,     0,     0,
       7
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,    18,     0,     0,     0,     0,     0,     0,     3,     5,
       6,     9,     0,    11,    12,    10,     7,    51,    52,    53,
       8,    83,    84,     0,     0,     0,     0,    73,    76,    74,
       0,     0,    85,    58,     0,     0,     0,     0,     1,     4,
       0,     0,     0,     0,     0,     0,     0,     0,    78,     0,
       0,    71,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,    57,     0,
       0,    17,    89,     0,    23,    21,    54,     0,    80,     0,
      72,    88,    64,    63,    70,    69,    68,    66,    67,    65,
      62,    61,    60,    59,     0,     0,    15,    16,     0,    13,
      14,     0,     0,     0,     0,     0,    77,    82,     0,    75,
      88,    47,    86,    55,    56,    88,    19,    45,     0,     0,
       0,     0,     0,     0,    79,    88,     0,    88,     0,    45,
       0,     0,     0,     0,    48,    26,     0,    28,    81,    46,
      88,    90,     0,     0,    24,     0,    43,    41,    44,     2,
      22,    87,    39,    37,     0,    31,    29,    42,    40,     0,
      38,    35,    34,    32,    30,     0,    36,    33,    49,     0,
       0,    50
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,     8,     9,    10,   101,    11,    12,    13,    14,
      15,   104,   102,   103,   105,   118,   119,   112,   135,   149,
     169,    16,    17,    18,    19,    32,    33,    78,   108,    20,
      21,    52,   126,    22,    23,    98
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -113
static const yytype_int16 yypact[] =
{
      39,    90,     9,   -20,    -8,    18,    34,    51,    39,  -113,
    -113,  -113,    36,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
    -113,  -113,  -113,    49,    64,    -3,     9,  -113,   -17,    55,
       9,     9,  -113,   155,    76,     9,    77,    80,  -113,  -113,
      61,   113,     9,    93,    96,    97,   109,     9,  -113,     9,
     142,   165,    94,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,    98,    99,  -113,  -113,   116,
     119,  -113,  -113,    72,   101,   102,  -113,   107,     9,   128,
    -113,    42,   165,   165,    70,    70,    70,    70,    70,    70,
      52,    52,  -113,  -113,   125,   127,  -113,  -113,   120,  -113,
    -113,   144,   131,   123,   131,   124,  -113,  -113,    -6,  -113,
      88,  -113,  -113,  -113,  -113,    88,  -113,   149,    10,    38,
     132,    11,   132,     9,  -113,    59,   130,    71,   151,   169,
     132,    44,    91,   156,  -113,  -113,   132,  -113,  -113,  -113,
      42,  -113,    95,   181,  -113,   104,   201,   202,  -113,    39,
    -113,  -113,  -113,   203,   112,   204,   205,  -113,  -113,   206,
    -113,   207,   208,  -113,  -113,     9,  -113,  -113,  -113,   209,
     189,  -113
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -113,    68,   -43,    -7,  -113,  -113,  -113,  -113,  -113,  -113,
    -113,  -113,  -113,  -113,  -113,   115,   -73,    81,  -112,  -113,
    -113,  -113,  -113,  -113,  -113,   -26,   -28,  -113,  -113,  -113,
    -113,  -113,  -113,  -113,  -113,  -113
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -89
static const yytype_int16 yytable[] =
{
      46,    39,    50,    51,    47,   123,    44,    45,    34,    66,
     137,    48,    27,    28,   129,   129,    72,    29,   144,    77,
      35,    79,    36,   124,   150,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    30,    37,   130,
     136,    31,    40,     1,   132,   131,     1,    41,   131,   133,
     145,    38,   107,     2,   -88,   133,     2,     3,     4,     5,
       3,     4,     5,     1,    42,   110,     6,   125,    43,     6,
      69,    70,   127,     2,   111,     1,    49,     3,     4,     5,
      65,    99,   100,   139,    67,     2,     6,    68,   141,     3,
       4,     5,     1,    63,    64,    24,    25,   138,     6,    73,
     146,   147,     2,    26,   152,   153,     3,     4,     5,    61,
      62,    63,    64,   155,   156,     6,    76,    71,    39,    81,
      39,   161,   162,    96,    74,    75,    97,    94,    95,   106,
     -25,   -27,   113,   111,   114,   117,   115,    53,    54,   168,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
     109,   116,   120,   122,   128,   134,   140,   142,    53,    54,
     148,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    80,    53,    54,   143,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    53,    54,   154,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,   157,   158,
     160,   163,   164,   171,   166,   167,   170,   159,   165,   121,
       0,   151
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-113))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      26,     8,    30,    31,    21,    11,     9,    10,    28,    35,
     122,    28,     3,     4,     4,     4,    42,     8,   130,    47,
      28,    49,     4,    29,   136,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    28,     4,    29,
      29,    32,     6,     4,     6,   118,     4,    11,   121,    11,
       6,     0,    78,    14,    15,    11,    14,    18,    19,    20,
      18,    19,    20,     4,    15,    23,    27,   110,     4,    27,
       9,    10,   115,    14,    81,     4,    21,    18,    19,    20,
       4,     9,    10,    24,     7,    14,    27,     7,    17,    18,
      19,    20,     4,    41,    42,     5,     6,   123,    27,     6,
       9,    10,    14,    13,     9,    10,    18,    19,    20,    39,
      40,    41,    42,     9,    10,    27,     7,     4,   125,    25,
     127,     9,    10,     7,    28,    28,     7,    29,    29,    22,
      29,    29,     7,   140,     7,     4,    16,    30,    31,   165,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      22,     7,    29,    29,     5,    23,    26,     6,    30,    31,
       4,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    29,    30,    31,     5,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    30,    31,     6,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,     7,     7,
       7,     7,     7,    24,     7,     7,     7,   149,    12,   104,
      -1,   140
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    14,    18,    19,    20,    27,    44,    45,    46,
      47,    49,    50,    51,    52,    53,    64,    65,    66,    67,
      72,    73,    76,    77,     5,     6,    13,     3,     4,     8,
      28,    32,    68,    69,    28,    28,     4,     4,     0,    46,
       6,    11,    15,     4,     9,    10,    68,    21,    28,    21,
      69,    69,    74,    30,    31,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,     4,    68,     7,     7,     9,
      10,     4,    68,     6,    28,    28,     7,    69,    70,    69,
      29,    25,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    29,    29,     7,     7,    78,     9,
      10,    48,    55,    56,    54,    57,    22,    68,    71,    22,
      23,    46,    60,     7,     7,    16,     7,     4,    58,    59,
      29,    58,    29,    11,    29,    45,    75,    45,     5,     4,
      29,    59,     6,    11,    23,    61,    29,    61,    68,    24,
      26,    17,     6,     5,    61,     6,     9,    10,     4,    62,
      61,    60,     9,    10,     6,     9,    10,     7,     7,    44,
       7,     9,    10,     7,     7,    12,     7,     7,    68,    63,
       7,    24
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])



/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 15:
/* Line 1787 of yacc.c  */
#line 335 "analis.y"
    {
			addVars(m, "string");
		}
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 339 "analis.y"
    {
			addVars(m, "integer");
		}
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 344 "analis.y"
    {
			char *internal_name = match((yyvsp[(3) - (3)].string));
			if (internal_name == NULL)
			{
				names.push_back((yyvsp[(3) - (3)].string));
			}
		}
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 352 "analis.y"
    {
			char *internal_name = match((yyvsp[(1) - (1)].string));
			if (internal_name == NULL)
			{
				names.push_back((yyvsp[(1) - (1)].string));
			}
		}
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 361 "analis.y"
    {
			char *internal_name = get_name();
			m[(yyvsp[(1) - (6)].string)] = internal_name;
			char *image = match((yyvsp[(3) - (6)].string));
			refs[internal_name] = image;
			//cout << "STRING " << internal_name << ", " << "\"" << image << "\"" << endl;
		}
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 370 "analis.y"
    {
			char *name = get_label();
			m[(yyvsp[(2) - (3)].string)] = name;
			set_label(name);
		}
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 377 "analis.y"
    {
			//fm.clear();
			param_num = 0;
			swap(code, funcs);
			char *name = get_label();
			func_beg[(yyvsp[(1) - (4)].string)] = name;
			set_label(name);
			char *ret_val = itoa(init_int(0));
			char *ret_addr = itoa(init_const_string(""));
			info *inf = new info((yyvsp[(1) - (4)].string), ret_addr, ret_val, "integer", v.back() + 1);
			func_info.insert(pair<char *, info *>((yyvsp[(1) - (4)].string), inf));		
			//func_info[$1] = inf;
			cur_func_decl = (yyvsp[(1) - (4)].string);
			infoes.push(inf);
		}
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 393 "analis.y"
    {
			swap(code, funcs);
			infoes.pop();
			param_num = 0;
		}
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 399 "analis.y"
    {
			param_num = 0;
			swap(code, funcs);
			char *name = get_label();
			func_beg[(yyvsp[(1) - (4)].string)] = name;
			set_label(name);
			char *ret_val = itoa(init_const_string(""));
			char *ret_addr = itoa(init_const_string(""));
			info *inf = new info((yyvsp[(1) - (4)].string), ret_addr, ret_val, "string", v.back() + 1);
			func_info.insert(pair<char *, info *>((yyvsp[(1) - (4)].string), inf));		
			//func_info[$1] = inf;
			cur_func_decl = (yyvsp[(1) - (4)].string);
			infoes.push(inf);
		}
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 414 "analis.y"
    {
			swap(code, funcs);
			infoes.pop();
			param_num = 0;
		}
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 420 "analis.y"
    {
			param_num = 0;
			swap(code, funcs);
			char *name = get_label();
			func_beg[(yyvsp[(1) - (4)].string)] = name;
			set_label(name);
			char *ret_val = itoa(init_const_string(""));
			char *ret_addr = itoa(init_const_string(""));
			info *inf = new info((yyvsp[(1) - (4)].string), ret_addr, ret_val, "string", v.back() + 1);
			func_info.insert(pair<char *, info *>((yyvsp[(1) - (4)].string), inf));		
			//func_info[$1] = inf;
			cur_func_decl = (yyvsp[(1) - (4)].string);
			infoes.push(inf);
		}
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 435 "analis.y"
    {
			swap(code, funcs);
			infoes.pop();
			param_num = 0;
		}
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 441 "analis.y"
    {
			//fm.clear();
			param_num = 0;
			swap(code, funcs);
			char *name = get_label();
			func_beg[(yyvsp[(1) - (4)].string)] = name;
			set_label(name);
			char *ret_val = itoa(init_int(0));
			char *ret_addr = itoa(init_const_string(""));
			info *inf = new info((yyvsp[(1) - (4)].string), ret_addr, ret_val, "integer", v.back() + 1);
			func_info.insert(pair<char *, info *>((yyvsp[(1) - (4)].string), inf));		
			//func_info[$1] = inf;
			cur_func_decl = (yyvsp[(1) - (4)].string);
			infoes.push(inf);
		}
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 457 "analis.y"
    {
			swap(code, funcs);
			infoes.pop();
			param_num = 0;
		}
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 464 "analis.y"
    {
			addVars(fm, "integer");
		}
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 468 "analis.y"
    {
			addVars(fm, "integer");
		}
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 472 "analis.y"
    {
			addVars(fm, "string");
		}
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 476 "analis.y"
    {
			addVars(fm, "string");
		}
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 480 "analis.y"
    {
			in_chain_param("integer", (yyvsp[(2) - (6)].string));
		}
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 484 "analis.y"
    {
			in_chain_param("integer", (yyvsp[(2) - (5)].string));
		}
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 488 "analis.y"
    {
			in_chain_param("string", (yyvsp[(2) - (5)].string));
		}
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 492 "analis.y"
    {
			in_chain_param("string", (yyvsp[(2) - (6)].string));
		}
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 496 "analis.y"
    {
			in_chain_param("integer", (yyvsp[(2) - (4)].string));
		}
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 500 "analis.y"
    {
			in_chain_param("integer", (yyvsp[(2) - (5)].string));
		}
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 504 "analis.y"
    {
			in_chain_param("string", (yyvsp[(2) - (4)].string));
		}
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 508 "analis.y"
    {
			addVars(fm, "integer");
		}
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 512 "analis.y"
    {
			addVars(fm, "integer");
		}
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 516 "analis.y"
    {
			addVars(fm, "string");
		}
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 520 "analis.y"
    {
			addVars(fm, "string");
		}
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 525 "analis.y"
    {
			names.push_back((yyvsp[(3) - (3)].string));
			param_num++;
		}
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 530 "analis.y"
    {
			names.push_back((yyvsp[(1) - (1)].string));
			param_num++;
		}
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 539 "analis.y"
    {
			tmp = m;
			m = fm;
		}
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 544 "analis.y"
    {
			info *inf = infoes.top();
			char *where = inf->ret_val;
			char *what = last_expr_name;
			move(what, where);
			free(what);
			where = inf->ret_addr;
			goto_name(where);	
		}
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 554 "analis.y"
    {
			m = tmp;
			fm.clear();
		}
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 564 "analis.y"
    {
			move(last_expr_name, real_name(match((yyvsp[(1) - (4)].string))));
		}
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 569 "analis.y"
    {
			*code << "READ " << real_name(match((yyvsp[(3) - (5)].string))) << endl;
		}
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 573 "analis.y"
    {
			//char *name = itoa(v.back());
			char *name = last_expr_name;
			*code << "WRITE " << real_name(name) << endl;
		}
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 580 "analis.y"
    {
			char *name = real_name(match((yyvsp[(2) - (3)].string)));
			if (name == NULL) { *code << "GOTO " << "" << endl; }
			else { goto_label(name); }
		}
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 587 "analis.y"
    {
			(yyval.string) = (yyvsp[(1) - (1)].string);
			last_expr_name = (yyvsp[(1) - (1)].string);
			//cout << "name" << $<string>1 << endl;
		}
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 594 "analis.y"
    {			
			char *name = itoa(init_int(0));
			(yyval.string) = name;
			ternary("MUL", (yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string), name);
		}
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 600 "analis.y"
    {
			char *name = itoa(init_int(0));
			(yyval.string) = name;
			ternary("DIV", (yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string), name);	
		}
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 606 "analis.y"
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
			(yyval.string) = name;
			//cout << "add :" << $<string>$ << endl;
			ternary("ADD", (yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string), name);
		}
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 621 "analis.y"
    {
			char *name = itoa(init_int(0));
			(yyval.string) = name;
			ternary("SUB", (yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string), name);	
		}
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 627 "analis.y"
    {
			char *name = itoa(init_int(0));
			(yyval.string) = name;
			ternary("AND", (yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string), name);	
		}
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 633 "analis.y"
    {
			char *name = itoa(init_int(0));
			(yyval.string) = name;
			ternary("OR", (yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string), name);	
		}
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 639 "analis.y"
    {
			char *name = itoa(init_int(0));
			(yyval.string) = name;
			ternary("LT", (yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string), name);	
		}
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 645 "analis.y"
    {
			char *name = itoa(init_int(0));
			(yyval.string) = name;
			ternary("LE", (yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string), name);	
		}
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 651 "analis.y"
    {
			char *name = itoa(init_int(0));
			(yyval.string) = name;
			ternary("GT", (yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string), name);	
		}
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 657 "analis.y"
    {
			char *name = itoa(init_int(0));
			(yyval.string) = name;
			ternary("GE", (yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string), name);	
		}
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 663 "analis.y"
    {
			char *name = itoa(init_int(0));
			(yyval.string) = name;
			ternary("EQ", (yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string), name);	
		}
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 669 "analis.y"
    {
			char *name = itoa(init_int(0));
			(yyval.string) = name;
			ternary("NE", (yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string), name);	
		}
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 675 "analis.y"
    {
			char *name = itoa(init_int(0));
			(yyval.string) = name;
			*code << "NOT " << (yyvsp[(2) - (2)].string) << ", " << name << endl;
		}
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 681 "analis.y"
    {
			(yyval.string) = (yyvsp[(2) - (3)].string);
		}
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 685 "analis.y"
    {
			(yyval.string) = itoa(init_int((yyvsp[(1) - (1)].number)));
		}
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 689 "analis.y"
    {			
			int num = init_const_string((yyvsp[(1) - (1)].string));
			char *name = itoa(num);
			(yyval.string) = name;
		}
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 695 "analis.y"
    {		
			char *new_name = itoa(init_const_string((yyvsp[(1) - (4)].string)));
			int num = init_const_string("");
			char *name = itoa(num);
			(yyval.string) = name;
			*code << "IND " << new_name << ", " << itoa(v.back()-2) << ", " << name << endl;
		}
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 703 "analis.y"
    {
			char *name = real_name(match((yyvsp[(1) - (1)].string)));
			//if (strings.find(name) == strings.end())
			if (!inStrings(name))
			{
				isString = false;
			}
			else { isString = true; }
			(yyval.string) = name;
			//cout << "name :" << $<string>$ << endl;
		}
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 715 "analis.y"
    {	
			int num = init_const_string("");
			char *name = itoa(num);
			(yyval.string) = name;
			*code << "IND " << real_name(match((yyvsp[(1) - (4)].string))) << ", " << itoa(v.back()-1) << ", " << name << endl;
		}
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 722 "analis.y"
    {
			//func_names.push($1);
			infoes.push(match_func_info((yyvsp[(1) - (2)].string)));
			curParam.push(infoes.top()->first);
			vector<char *> *v = new vector<char *>();
			real_params.push(v);
			param_num = 0;
		}
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 731 "analis.y"
    {
			int num;
			info *inf = infoes.top();
			if (!strcmp(inf->type, "string"))
			{
				num = init_const_string("");
			}
			else
			{
				num = init_int(0);
			}
			//ret_val.push(num);
			char *res_name = itoa(num);
			(yyval.string) = res_name;
			char *label_back = get_label();
			char *name = itoa(init_const_string(label_back));
			move(name, inf->ret_addr);
			goto_label(match_func_beg(inf->name));
			set_label(label_back);
			move(inf->ret_val, res_name);
			vector<char *> *v = real_params.top();
			for (int i = 0; i < v->size(); i++)
			{
				char *dest = itoa((inf->v[i])+inf->first);  //
				move(dest, v->at(i));
				free(dest);
				free(v->at(i));
			}
			delete v;
			real_params.pop();
			curParam.pop();
			infoes.pop();
			param_num = 0;
		}
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 768 "analis.y"
    {
			//char *name = itoa(v.back());
			vector<char *> *v = real_params.top();
			info *inf = infoes.top();
			//char *name = $<string>3;
			char *name = last_expr_name;
			(yyval.string) = last_expr_name;
			char *dest = itoa(curParam.top());
			if (hasItem(param_num, inf->v))
			{
				v->push_back(strdup(name));
			}
			param_num++;
			move(name, dest);
			free(dest);
			curParam.top()++;
		}
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 786 "analis.y"
    {
			//char *name = itoa(v.back());
			vector<char *> *v = real_params.top();
			//char *name = $<string>1;
			char *name = last_expr_name;
			(yyval.string) = last_expr_name;
			char *dest = itoa(curParam.top());
			info *inf = infoes.top();
			if (hasItem(param_num, inf->v))
			{
				v->push_back(strdup(name));
			}
			param_num++;
			move(name, dest);
			free(dest);
			curParam.top()++;
		}
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 808 "analis.y"
    {
			//char *name_var = itoa(v.back());
			char *name_var = last_expr_name;
			char *name_label = get_label();
			*code << "BRANCH " << name_var << ", " << name_label << endl;
			free(name_var);
			//free(name_label);
			//name_label = get_label();
			char *name = get_label();
			//*code << "GOTO " << name << endl;
			goto_label(name);
			set_label(name_label);
			//free(name_label);
			if_counter.push(num_label);
		}
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 824 "analis.y"
    {
			char *name_label = get_label();
			//*code << "GOTO " << name_label << endl;
			goto_label(name_label);
			int first = if_counter.top();
			name_label = itoa(first);
			name_label[0] = 'b';
			set_label(name_label);
			if_counter.push(num_label);
			free(name_label);
		}
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 836 "analis.y"
    {
			char *name_label = itoa(if_counter.top());
			name_label[0] = 'b';
			set_label(name_label);
			for (int i = 0; i < 2; i++) { if_counter.pop(); }
		}
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 843 "analis.y"
    {
			char *name = get_label();
			while_counter.push(num_label);
			set_label(name);
		}
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 849 "analis.y"
    {
			//char *var_name = itoa(v.back());
			char *var_name = last_expr_name;
			char *name = itoa(init_int(0));
			*code << "NOT " << var_name << ", " << name << endl;
			var_name = strdup(name);
			free(name);
			name = get_label();
			while_counter.push(num_label);
			*code << "BRANCH " << var_name << ", " << name << endl;
			last_expr_name = NULL;
		}
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 862 "analis.y"
    {
			char *first = itoa(while_counter.top());
			while_counter.pop();
			char *second = itoa(while_counter.top());
			while_counter.pop();
			first[0] = 'b';
			second[0] = 'b';
			goto_label(second);
			set_label(first);
			free(first);
			free(second);
		}
    break;


/* Line 1787 of yacc.c  */
#line 2657 "analis.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2048 of yacc.c  */
#line 875 "analis.y"


