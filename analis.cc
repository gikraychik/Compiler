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

/* Line 336 of yacc.c  */
#line 200 "analis.cc"

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
   by #include "analis.hh".  */
#ifndef YY_ANALIS_HH
# define YY_ANALIS_HH
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
     LABELNAME = 260,
     REF = 261,
     COLON = 262,
     SEMICOLON = 263,
     DELIM = 264,
     STRINGCONST = 265,
     QUOTE = 266,
     STRING = 267,
     INTEGER = 268,
     COMA = 269,
     RETURN = 270,
     ASSIGN = 271,
     LT = 272,
     LE = 273,
     GT = 274,
     GE = 275,
     EQ = 276,
     NE = 277,
     OR = 278,
     AND = 279,
     NOT = 280,
     IF = 281,
     WHILE = 282,
     LOOP = 283,
     POOL = 284,
     READ = 285,
     WRITE = 286,
     LABEL = 287,
     RECOPENBRACE = 288,
     RECCLOSEBRACE = 289,
     BLOCK = 290,
     KCOLB = 291,
     THEN = 292,
     ELSE = 293,
     GOTO = 294,
     ADD = 295,
     SUB = 296,
     MUL = 297,
     DIV = 298,
     OBRACE = 299,
     CBRACE = 300
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 350 of yacc.c  */
#line 134 "analis.y"

	int number;
	char *string;


/* Line 350 of yacc.c  */
#line 294 "analis.cc"
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

#endif /* !YY_ANALIS_HH  */

/* Copy the second part of user declarations.  */

/* Line 353 of yacc.c  */
#line 322 "analis.cc"

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
#define YYFINAL  45
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   247

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNRULES -- Number of states.  */
#define YYNSTATES  197

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     6,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    29,    34,    39,    43,    45,
      52,    56,    64,    69,    72,    74,    78,    85,    87,    89,
      91,    96,   102,   108,   114,   118,   120,   122,   123,   124,
     125,   126,   127,   151,   153,   157,   161,   163,   167,   171,
     173,   177,   181,   185,   187,   191,   195,   197,   199,   201,
     205,   210,   214,   218,   222,   224,   226,   228,   232,   234,
     238,   240,   244,   248,   252,   256,   260,   264,   268,   270,
     273,   277,   279,   283,   285,   290,   292,   297,   299,   301,
     308
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      47,     0,    -1,    -1,    48,    -1,    48,    49,    -1,    49,
      -1,    50,    -1,    61,    -1,    83,    -1,    56,    -1,    52,
      -1,    54,    -1,    55,    -1,    12,    -1,    13,    -1,    53,
       7,    12,     8,    -1,    53,     7,    13,     8,    -1,    53,
      14,     4,    -1,     4,    -1,     4,     6,     4,     7,    51,
       8,    -1,    32,     4,     8,    -1,     4,     7,    51,    44,
      57,    45,    60,    -1,    58,    53,     7,    51,    -1,    58,
      52,    -1,    52,    -1,    35,    48,    36,    -1,    35,    48,
      15,    65,     8,    36,    -1,    62,    -1,    63,    -1,    64,
      -1,     4,    16,    65,     8,    -1,    30,    44,     4,    45,
       8,    -1,    31,    44,     4,    45,     8,    -1,    31,    44,
       3,    45,     8,    -1,    39,     4,     8,    -1,    81,    -1,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    66,    17,    66,
      67,    66,    19,    66,    68,    66,    18,    66,    69,    66,
      20,    66,    70,    66,    21,    66,    71,    66,    22,    66,
      -1,    72,    -1,    44,    66,    45,    -1,    72,    23,    73,
      -1,    73,    -1,    44,    66,    45,    -1,    73,    24,    74,
      -1,    74,    -1,    44,    66,    45,    -1,    74,    40,    75,
      -1,    74,    41,    75,    -1,    75,    -1,    75,    42,    76,
      -1,    75,    43,    76,    -1,    76,    -1,     3,    -1,     4,
      -1,    44,    74,    45,    -1,     4,    44,    77,    45,    -1,
      53,    14,     4,    -1,    53,    14,     3,    -1,    53,    14,
      12,    -1,     4,    -1,     3,    -1,    12,    -1,    78,    23,
      79,    -1,    79,    -1,    79,    24,    80,    -1,    80,    -1,
      44,    78,    45,    -1,    66,    17,    66,    -1,    66,    18,
      66,    -1,    66,    19,    66,    -1,    66,    20,    66,    -1,
      66,    21,    66,    -1,    66,    22,    66,    -1,     4,    -1,
      25,    78,    -1,    81,    40,    82,    -1,    82,    -1,    44,
      82,    45,    -1,    10,    -1,    10,    33,    66,    34,    -1,
       4,    -1,     4,    33,    66,    34,    -1,    84,    -1,    85,
      -1,    26,    78,    37,    59,    38,    59,    -1,    27,    78,
      28,    48,    29,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   145,   145,   146,   148,   149,   151,   152,   153,   155,
     156,   157,   158,   160,   162,   165,   169,   179,   183,   188,
     197,   204,   206,   208,   209,   211,   213,   215,   216,   217,
     219,   225,   226,   227,   229,   234,   235,   241,   248,   255,
     262,   269,   240,   282,   286,   291,   298,   302,   307,   314,
     318,   323,   331,   339,   344,   352,   360,   365,   370,   382,
     386,   388,   389,   390,   391,   392,   393,   395,   402,   407,
     414,   419,   423,   427,   428,   429,   430,   431,   432,   433,
     435,   436,   438,   439,   440,   441,   442,   444,   445,   447,
     449
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "NAME", "LABELNAME", "REF",
  "COLON", "SEMICOLON", "DELIM", "STRINGCONST", "QUOTE", "STRING",
  "INTEGER", "COMA", "RETURN", "ASSIGN", "LT", "LE", "GT", "GE", "EQ",
  "NE", "OR", "AND", "NOT", "IF", "WHILE", "LOOP", "POOL", "READ", "WRITE",
  "LABEL", "RECOPENBRACE", "RECCLOSEBRACE", "BLOCK", "KCOLB", "THEN",
  "ELSE", "GOTO", "ADD", "SUB", "MUL", "DIV", "OBRACE", "CBRACE",
  "$accept", "program", "commands", "command", "decl", "type", "decl_var",
  "namelist", "decl_ref", "decl_label", "decl_func", "chain_param",
  "decl_list", "block", "func_block", "action", "assign", "io", "goto",
  "expr", "int_expr", "@1", "@2", "@3", "@4", "@5", "int_expr_1",
  "int_expr_2", "int_expr_3", "int_term", "int_factor", "act_params",
  "bool_expr", "bool_term", "bool_factor", "string_expr", "string_factor",
  "control", "cond", "cycle", YY_NULL
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
     295,   296,   297,   298,   299,   300
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    47,    48,    48,    49,    49,    49,    50,
      50,    50,    50,    51,    51,    52,    52,    53,    53,    54,
      55,    56,    57,    58,    58,    59,    60,    61,    61,    61,
      62,    63,    63,    63,    64,    65,    65,    67,    68,    69,
      70,    71,    66,    66,    66,    72,    72,    72,    73,    73,
      73,    74,    74,    74,    75,    75,    75,    76,    76,    76,
      76,    77,    77,    77,    77,    77,    77,    78,    78,    79,
      79,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      81,    81,    82,    82,    82,    82,    82,    83,    83,    84,
      85
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     4,     3,     1,     6,
       3,     7,     4,     2,     1,     3,     6,     1,     1,     1,
       4,     5,     5,     5,     3,     1,     1,     0,     0,     0,
       0,     0,    23,     1,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     1,     3,     3,     1,     1,     1,     3,
       4,     3,     3,     3,     1,     1,     1,     3,     1,     3,
       1,     3,     3,     3,     3,     3,     3,     3,     1,     2,
       3,     1,     3,     1,     4,     1,     4,     1,     1,     6,
       5
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,    18,     0,     0,     0,     0,     0,     0,     0,     3,
       5,     6,    10,     0,    11,    12,     9,     7,    27,    28,
      29,     8,    87,    88,     0,     0,     0,    57,    58,     0,
       0,     0,    43,    46,    49,    53,    56,     0,    68,    70,
       0,     0,     0,     0,     0,     1,     4,     0,     0,     0,
      13,    14,     0,    58,    83,     0,     0,    36,    35,    81,
       0,    79,     0,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    20,    34,     0,     0,    17,     0,
       0,     0,     0,     0,     0,    30,     0,     0,    65,    18,
      66,     0,     0,    44,    59,    71,    58,     0,    72,    73,
      74,    75,    76,    77,     0,    45,     0,    48,    51,    52,
      54,    55,    67,     0,     0,    69,     0,     0,     0,     0,
      15,    16,     0,    18,    24,     0,     0,     0,     0,    82,
      37,    85,     0,    80,     0,    60,     0,     0,     0,     0,
       0,    90,    31,    33,    32,    19,     0,    23,     0,    86,
      84,    62,    17,    63,     0,    50,    25,    89,     0,    21,
       0,     0,     0,    13,    14,    22,    38,     0,     0,     0,
       0,     0,     0,    26,    39,     0,     0,     0,    40,     0,
       0,     0,    41,     0,     0,     0,    42
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     8,     9,    10,    11,    52,    12,    13,    14,    15,
      16,   135,   136,   124,   169,    17,    18,    19,    20,    56,
      31,   146,   178,   185,   189,   193,    32,    33,    34,    35,
      36,   102,    37,    38,    39,    58,    59,    21,    22,    23
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -84
static const yytype_int16 yypact[] =
{
     107,   109,     6,     6,   -11,    25,    59,    67,    75,   107,
     -84,   -84,   -84,    54,   -84,   -84,   -84,   -84,   -84,   -84,
     -84,   -84,   -84,   -84,   139,    90,     8,   -84,    52,     6,
       6,   159,    62,    95,   114,   115,   -84,     0,   129,   -84,
     112,   156,   146,   123,   154,   -84,   -84,   170,   162,   161,
     -84,   -84,   144,    -6,   158,     8,   186,   178,   157,   -84,
      22,   173,   153,    81,   -10,    13,    13,    13,    13,    13,
      13,    16,    18,    18,    18,    18,    18,     6,   164,     6,
     107,   155,   160,   163,   -84,   -84,   193,   194,   -84,    90,
     199,    13,    13,    29,   165,   -84,    13,    20,   -84,   166,
     -84,   190,   167,   -84,   -84,   -84,   171,    13,    11,   178,
     178,   178,   178,   178,    13,    95,    18,   114,   115,   115,
     -84,   -84,   129,   107,   168,   -84,    68,   201,   205,   206,
     -84,   -84,   208,   -84,   -84,   174,   199,    19,    39,   -84,
     178,   184,    20,   -84,    55,   -84,    13,    31,    81,    78,
     164,   -84,   -84,   -84,   -84,   -84,   183,   -84,    99,   -84,
     -84,   -84,   175,   -84,   113,   -84,   -84,   -84,   107,   -84,
     172,    13,    97,   193,   194,   -84,   178,     8,    13,   213,
     169,   187,    13,   -84,   178,    13,    66,    13,   178,    13,
     127,    13,   178,    13,   125,    13,   178
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -84,   -84,   -78,    -8,   -84,   -83,   -82,   -57,   -84,   -84,
     -84,   -84,   -84,    57,   -84,   -84,   -84,   -84,   -84,    45,
     -26,   -84,   -84,   -84,   -84,   -84,   -84,   176,   -23,   116,
     117,   -84,    48,   147,   148,   -84,   -50,   -84,   -84,   -84
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -79
static const yytype_int16 yytable[] =
{
      57,    46,   126,   101,    62,    94,   132,    63,   134,    27,
      28,    27,    53,    77,   -37,   -37,    27,   106,    54,    27,
     106,    27,   106,    77,   141,    98,    99,    91,    96,    93,
      54,    29,    63,    41,   100,   105,    96,    78,    60,   108,
     109,   110,   111,   112,   113,   149,    96,   143,    96,   117,
      30,    40,    55,   159,   157,   -37,    96,   107,   161,   162,
     114,    47,   116,    43,   142,   137,   138,   163,    48,    42,
     140,    44,     1,   160,   103,    45,   165,    61,    64,   158,
     -78,    93,     1,    96,    63,    71,   187,   175,   147,   -78,
     172,    63,    94,   148,     2,     3,    60,   151,     4,     5,
       6,     1,    50,    51,     2,     3,   170,     7,     4,     5,
       6,     1,   177,    48,   166,    24,    25,     7,    46,    72,
     164,    73,    74,     2,     3,    26,   104,     4,     5,     6,
      96,    84,   171,     2,     3,    77,     7,     4,     5,     6,
      80,    46,    96,    49,    96,   176,     7,   195,   191,    82,
      83,    57,   180,    79,    73,    74,   184,    75,    76,   186,
      81,   188,    85,   190,    46,   192,    88,   194,    89,   196,
      65,    66,    67,    68,    69,    70,    65,    66,    67,    68,
      69,    70,    86,    87,   173,   174,    96,   182,    90,   118,
     119,    92,   120,   121,    95,    96,    77,    97,   103,   123,
     127,   130,   131,   133,   144,   128,   150,   167,   129,   152,
     139,   -64,   145,   153,   154,    60,   155,    91,   168,   156,
     -61,   181,   179,   183,   122,     0,     0,   125,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-84))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      26,     9,    80,    60,    30,    55,    89,    30,    90,     3,
       4,     3,     4,    23,     3,     4,     3,     4,    10,     3,
       4,     3,     4,    23,     4,     3,     4,    33,    17,    55,
      10,    25,    55,    44,    12,    45,    17,    37,    44,    65,
      66,    67,    68,    69,    70,   123,    17,    97,    17,    72,
      44,     3,    44,    34,   136,    44,    17,    44,     3,     4,
      44,     7,    44,     4,    44,    91,    92,    12,    14,    44,
      96,     4,     4,    34,    45,     0,    45,    29,    30,   136,
      28,   107,     4,    17,   107,    23,    20,   170,   114,    37,
     168,   114,   142,   116,    26,    27,    44,    29,    30,    31,
      32,     4,    12,    13,    26,    27,     7,    39,    30,    31,
      32,     4,    15,    14,    36,     6,     7,    39,   126,    24,
     146,    40,    41,    26,    27,    16,    45,    30,    31,    32,
      17,     8,    19,    26,    27,    23,    39,    30,    31,    32,
      28,   149,    17,     4,    17,   171,    39,    22,    21,     3,
       4,   177,   178,    24,    40,    41,   182,    42,    43,   185,
       4,   187,     8,   189,   172,   191,     4,   193,     7,   195,
      17,    18,    19,    20,    21,    22,    17,    18,    19,    20,
      21,    22,    12,    13,    12,    13,    17,    18,    44,    73,
      74,    33,    75,    76,     8,    17,    23,    40,    45,    35,
      45,     8,     8,     4,    14,    45,    38,   150,    45,     8,
      45,    45,    45,     8,     8,    44,     8,    33,    35,    45,
      45,     8,   177,    36,    77,    -1,    -1,    79,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    71
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    26,    27,    30,    31,    32,    39,    47,    48,
      49,    50,    52,    53,    54,    55,    56,    61,    62,    63,
      64,    83,    84,    85,     6,     7,    16,     3,     4,    25,
      44,    66,    72,    73,    74,    75,    76,    78,    79,    80,
      78,    44,    44,     4,     4,     0,    49,     7,    14,     4,
      12,    13,    51,     4,    10,    44,    65,    66,    81,    82,
      44,    78,    66,    74,    78,    17,    18,    19,    20,    21,
      22,    23,    24,    40,    41,    42,    43,    23,    37,    24,
      28,     4,     3,     4,     8,     8,    12,    13,     4,     7,
      44,    33,    33,    66,    82,     8,    17,    40,     3,     4,
      12,    53,    77,    45,    45,    45,     4,    44,    66,    66,
      66,    66,    66,    66,    44,    73,    44,    74,    75,    75,
      76,    76,    79,    35,    59,    80,    48,    45,    45,    45,
       8,     8,    51,     4,    52,    57,    58,    66,    66,    45,
      66,     4,    44,    82,    14,    45,    67,    66,    74,    48,
      38,    29,     8,     8,     8,     8,    45,    52,    53,    34,
      34,     3,     4,    12,    66,    45,    36,    59,    35,    60,
       7,    19,    48,    12,    13,    51,    66,    15,    68,    65,
      66,     8,    18,    36,    66,    69,    66,    20,    66,    70,
      66,    21,    66,    71,    66,    22,    66
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
        case 13:
/* Line 1787 of yacc.c  */
#line 161 "analis.y"
    {}
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 163 "analis.y"
    {}
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 166 "analis.y"
    {

		}
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 170 "analis.y"
    {
			for (int i = 0; i < names.size(); i++)
			{
				//m.insert(pair<char *, char *>(names[i], itoa(init_int(0))));
				m[names[i]] = itoa(init_int(0));
			}
			names.clear();
		}
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 180 "analis.y"
    {
			names.push_back((yyvsp[(3) - (3)].string));
		}
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 184 "analis.y"
    {
			names.push_back((yyvsp[(1) - (1)].string));
		}
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 189 "analis.y"
    {
			char *internal_name = get_name();
			m[(yyvsp[(1) - (6)].string)] = internal_name;
			char *image = match((yyvsp[(3) - (6)].string));
			refs[internal_name] = image;
			cout << "STRING " << internal_name << ", " << "\"" << image << "\"" << endl;
		}
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 198 "analis.y"
    {
			char *name = get_label();
			m[(yyvsp[(2) - (3)].string)] = name;
			cout << "LABEL " << name << endl;
		}
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 220 "analis.y"
    {
			//move(itoa(v.back()), m[$1]);
			move((yyvsp[(3) - (4)].string), match((yyvsp[(1) - (4)].string)));
		}
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 230 "analis.y"
    {
			cout << "GOTO " << match((yyvsp[(2) - (3)].string)) << endl;
		}
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 236 "analis.y"
    {
			(yyval.string) = (yyvsp[(1) - (1)].string);
		}
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 241 "analis.y"
    {
			int num = init_int(0);
			char *name = itoa(num);
			(yyval.string) = name;
			ternary("LT", (yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string), name);
		}
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 248 "analis.y"
    {
			int num = init_int(0);
			char *name = itoa(num);
			(yyval.string) = name;
			ternary("GT", (yyvsp[(1) - (7)].string), (yyvsp[(3) - (7)].string), name);
		}
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 255 "analis.y"
    {
			int num = init_int(0);
			char *name = itoa(num);
			(yyval.string) = name;
			ternary("LE", (yyvsp[(1) - (11)].string), (yyvsp[(3) - (11)].string), name);
		}
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 262 "analis.y"
    {
			int num = init_int(0);
			char *name = itoa(num);
			(yyval.string) = name;
			ternary("GE", (yyvsp[(1) - (15)].string), (yyvsp[(3) - (15)].string), name);
		}
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 269 "analis.y"
    {
			int num = init_int(0);
			char *name = itoa(num);
			(yyval.string) = name;
			ternary("EQ", (yyvsp[(1) - (19)].string), (yyvsp[(3) - (19)].string), name);
		}
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 276 "analis.y"
    {
			int num = init_int(0);
			char *name = itoa(num);
			(yyval.string) = name;
			ternary("NE", (yyvsp[(1) - (23)].string), (yyvsp[(3) - (23)].string), name);
		}
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 283 "analis.y"
    {
			(yyval.string) = (yyvsp[(1) - (1)].string);
		}
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 287 "analis.y"
    {
			(yyval.string) = (yyvsp[(2) - (3)].string);
		}
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 292 "analis.y"
    {
			int num = init_int(0);
			char *name = itoa(num);
			(yyval.string) = name;
			ternary("OR", (yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string), name);
		}
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 299 "analis.y"
    {
			(yyval.string) = (yyvsp[(1) - (1)].string);
		}
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 303 "analis.y"
    {
			(yyval.string) = (yyvsp[(2) - (3)].string);
		}
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 308 "analis.y"
    {
			int num = init_int(0);
			char *name = itoa(num);
			(yyval.string) = name;
			ternary("AND", (yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string), name);
		}
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 315 "analis.y"
    {
			(yyval.string) = (yyvsp[(1) - (1)].string);
		}
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 319 "analis.y"
    {
			(yyval.string) = (yyvsp[(2) - (3)].string);
		}
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 324 "analis.y"
    {
			int num = init_int(0);
			char *name = itoa(num);
			(yyval.string) = name;
			//cout << "ADD " << $<string>1 << ", " << $<string>3 << ", " << name << endl;
			ternary("ADD", (yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string), name);
		}
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 332 "analis.y"
    {
			int num = init_int(0);
			char *name = itoa(num);
			(yyval.string) = name;
			//cout << "SUB " << $<string>1 << ", " << $<string>3 << ", " << name << endl;
			ternary("SUB", (yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string), name);
		}
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 340 "analis.y"
    {
			(yyval.string) = (yyvsp[(1) - (1)].string);
		}
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 345 "analis.y"
    {
			int num = init_int(0);
			char *name = itoa(num);
			(yyval.string) = name;
			//cout << "MUL " << $<string>1 << ", " << $<string>3 << ", " << name << endl;
			ternary("MUL", (yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string), name);	
		}
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 353 "analis.y"
    {
			int num = init_int(0);
			char *name = itoa(num);
			(yyval.string) = name;
			//cout << "DIV " << $<string>1 << ", " << $<number>3 << ", " << name << endl;
			ternary("DIV", (yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].string), name);	
		}
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 361 "analis.y"
    {
			(yyval.string) = (yyvsp[(1) - (1)].string);
		}
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 366 "analis.y"
    {
			int num = init_int((yyvsp[(1) - (1)].number));
			(yyval.string) = itoa(num);
		}
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 371 "analis.y"
    {
			char *internal_name = match((yyvsp[(1) - (1)].string));
			char *ref = match_ref(internal_name);
			if (ref == NULL) { (yyval.string) = internal_name; }
			else
			{
				//cout << "LOL:" << *(ref+1) << endl; 
				(yyval.string) = ref;
			}
			//cout << "Testing: " << match($1) << endl;
		}
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 383 "analis.y"
    {
			(yyval.string) = (yyvsp[(2) - (3)].string);
		}
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 396 "analis.y"
    {
			int num = init_int(0);
			char *name = itoa(num);
			(yyval.string) = name;
			cout << "OR " << (yyvsp[(1) - (3)].string) << ", " << (yyvsp[(3) - (3)].string) << ", " << name << endl;	
		}
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 403 "analis.y"
    {
			(yyval.string) = (yyvsp[(1) - (1)].string);
		}
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 408 "analis.y"
    {
			int num = init_int(0);
			char *name = itoa(num);
			(yyval.string) = name;
			cout << "AND " << (yyvsp[(1) - (3)].string) << ", " << (yyvsp[(3) - (3)].string) << ", " << name << endl;
		}
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 415 "analis.y"
    {
			(yyval.string) = (yyvsp[(1) - (1)].string);
		}
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 420 "analis.y"
    {
			(yyval.string) = (yyvsp[(2) - (3)].string);
		}
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 424 "analis.y"
    {
			
		}
    break;


/* Line 1787 of yacc.c  */
#line 2101 "analis.cc"
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
#line 453 "analis.y"


