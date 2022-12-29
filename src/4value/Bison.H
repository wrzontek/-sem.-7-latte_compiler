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

#ifndef YY_FVC_BISON_H_INCLUDED
# define YY_FVC_BISON_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int fvc_debug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    _ERROR_ = 258,
    _BANGEQ = 259,
    _PERCENT = 260,
    _DAMP = 261,
    _STAR = 262,
    _PLUS = 263,
    _DPLUS = 264,
    _MINUS = 265,
    _DMINUS = 266,
    _SLASH = 267,
    _COLON = 268,
    _COLONEQ = 269,
    _SEMI = 270,
    _LT = 271,
    _LDARROW = 272,
    _DEQ = 273,
    _GT = 274,
    _GTEQ = 275,
    _SYMB_2 = 276,
    _SYMB_7 = 277,
    _SYMB_6 = 278,
    _KW_else = 279,
    _KW_if = 280,
    _KW_return = 281,
    _SYMB_8 = 282,
    _KW_then = 283,
    _DBAR = 284,
    T_UIdent = 285,
    _STRING_ = 286,
    _INTEGER_ = 287
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 50 "fvc.y"

  int    _int;
  char   _char;
  double _double;
  char*  _string;
  Program* program_;
  CodeBlock* codeblock_;
  NonJmpStmt* nonjmpstmt_;
  JmpStmt* jmpstmt_;
  Atom* atom_;
  BinOp* binop_;
  ListCodeBlock* listcodeblock_;
  ListNonJmpStmt* listnonjmpstmt_;
  ListJmpStmt* listjmpstmt_;
  ListAtom* listatom_;

#line 107 "Bison.H"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int fvc_parse (yyscan_t scanner, YYSTYPE *result);

#endif /* !YY_FVC_BISON_H_INCLUDED  */
