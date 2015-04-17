#define EQUALS 257
#define R_PAREN 258
#define L_PAREN 259
#define QUOTE 260
#define COLON 261
#define COMMENT 262
#define COMMA 263
#define EXCLAIM 264
#define NEWLN 265
#define WORD 266
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
	char *str;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
