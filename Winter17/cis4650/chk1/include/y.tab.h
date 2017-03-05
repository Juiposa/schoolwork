
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ENDFILE = 258,
     ERROR = 259,
     ELSE = 260,
     IF = 261,
     INT = 262,
     RETURN = 263,
     VOID = 264,
     WHILE = 265,
     ID = 266,
     NUM = 267,
     PLUS = 268,
     MINUS = 269,
     MULTI = 270,
     DIVIDE = 271,
     LT = 272,
     GT = 273,
     LE = 274,
     GE = 275,
     EQ = 276,
     NE = 277,
     ASSIGN = 278,
     SEMICLN = 279,
     COMMA = 280,
     LPAREN = 281,
     RPAREN = 282,
     LBRACKET = 283,
     RBRACKET = 284,
     LBRACE = 285,
     RBRACE = 286,
     OPENCOMMENT = 287,
     CLOSECOMMENT = 288
   };
#endif
/* Tokens.  */
#define ENDFILE 258
#define ERROR 259
#define ELSE 260
#define IF 261
#define INT 262
#define RETURN 263
#define VOID 264
#define WHILE 265
#define ID 266
#define NUM 267
#define PLUS 268
#define MINUS 269
#define MULTI 270
#define DIVIDE 271
#define LT 272
#define GT 273
#define LE 274
#define GE 275
#define EQ 276
#define NE 277
#define ASSIGN 278
#define SEMICLN 279
#define COMMA 280
#define LPAREN 281
#define RPAREN 282
#define LBRACKET 283
#define RBRACKET 284
#define LBRACE 285
#define RBRACE 286
#define OPENCOMMENT 287
#define CLOSECOMMENT 288




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


