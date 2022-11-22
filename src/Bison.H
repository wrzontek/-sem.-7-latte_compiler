/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_LATTE_BISON_H_INCLUDED
# define YY_LATTE_BISON_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int latte_debug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
enum yytokentype {
    _ERROR_ = 258,
    _BANG = 259,
    _BANGEQ = 260,
    _PERCENT = 261,
    _DAMP = 262,
    _LPAREN = 263,
    _RPAREN = 264,
    _STAR = 265,
    _PLUS = 266,
    _DPLUS = 267,
    _COMMA = 268,
    _MINUS = 269,
    _DMINUS = 270,
    _SLASH = 271,
    _SEMI = 272,
    _LT = 273,
    _LDARROW = 274,
    _EQ = 275,
    _DEQ = 276,
    _GT = 277,
    _GTEQ = 278,
    _KW_boolean = 279,
    _KW_else = 280,
    _KW_false = 281,
    _KW_if = 282,
    _KW_int = 283,
    _KW_return = 284,
    _KW_string = 285,
    _KW_true = 286,
    _KW_void = 287,
    _KW_while = 288,
    _LBRACE = 289,
    _DBAR = 290,
    _RBRACE = 291,
    _STRING_ = 292,
    _INTEGER_ = 293,
    _IDENT_ = 294
};
#endif

/* Value type.  */
#if !defined YYSTYPE && !defined YYSTYPE_IS_DECLARED
union YYSTYPE {
#line 50 "Latte.y"

    int _int;
    char _char;
    double _double;
    char *_string;
    Program *program_;
    TopDef *topdef_;
    ListTopDef *listtopdef_;
    Arg *arg_;
    ListArg *listarg_;
    Block *block_;
    ListStmt *liststmt_;
    Stmt *stmt_;
    Item *item_;
    ListItem *listitem_;
    Type *type_;
    ListType *listtype_;
    Expr *expr_;
    ListExpr *listexpr_;
    AddOp *addop_;
    MulOp *mulop_;
    RelOp *relop_;

#line 121 "Bison.H"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if !defined YYLTYPE && !defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE {
    int first_line;
    int first_column;
    int last_line;
    int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


int latte_parse(yyscan_t scanner, YYSTYPE *result);

#endif /* !YY_LATTE_BISON_H_INCLUDED  */
