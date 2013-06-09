/* A Bison parser, made by GNU Bison 2.6.1.  */

/* Bison interface for Yacc-like parsers in C
   
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
     IF = 272,
     WHILE = 273,
     LOOP = 274,
     POOL = 275,
     READ = 276,
     WRITE = 277,
     EOFF = 278,
     LABEL = 279,
     RECOPENBRACE = 280,
     RECCLOSEBRACE = 281,
     BLOCK = 282,
     KCOLB = 283,
     THEN = 284,
     ELSE = 285,
     GOTO = 286,
     OBRACE = 287,
     CBRACE = 288,
     OR = 289,
     AND = 290,
     NOT = 291,
     NE = 292,
     EQ = 293,
     GE = 294,
     LE = 295,
     GT = 296,
     LT = 297,
     SUB = 298,
     ADD = 299,
     DIV = 300,
     MUL = 301
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2049 of yacc.c  */
#line 175 "analis.y"

	int number;
	char *string;


/* Line 2049 of yacc.c  */
#line 109 "analis.tab.h"
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
