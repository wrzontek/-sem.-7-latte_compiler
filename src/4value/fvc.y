/* -*- c++ -*- File generated by the BNF Converter (bnfc 2.9.3). */

/* Parser definition to be used with Bison. */

/* Generate header file for lexer. */
%defines "Bison.H"

/* Reentrant parser */
%pure_parser
  /* From Bison 2.3b (2008): %define api.pure full */
%lex-param   { yyscan_t scanner }
%parse-param { yyscan_t scanner }

/* Turn on line/column tracking in the fvc_lloc structure: */
%locations

/* Argument to the parser to be filled with the parsed tree. */
%parse-param { YYSTYPE *result }

%{
/* Begin C preamble code */

#include <algorithm> /* for std::reverse */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Absyn.H"

#define YYMAXDEPTH 10000000

/* The type yyscan_t is defined by flex, but we need it in the parser already. */
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE fvc__scan_string(const char *str, yyscan_t scanner);
extern void fvc__delete_buffer(YY_BUFFER_STATE buf, yyscan_t scanner);

extern void fvc_lex_destroy(yyscan_t scanner);
extern char* fvc_get_text(yyscan_t scanner);

extern yyscan_t fvc__initialize_lexer(FILE * inp);

/* End C preamble code */
%}

%union
{
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
}

%{
void yyerror(YYLTYPE *loc, yyscan_t scanner, YYSTYPE *result, const char *msg)
{
  fprintf(stderr, "error: %d,%d: %s at %s\n",
    loc->first_line, loc->first_column, msg, fvc_get_text(scanner));
}

int yyparse(yyscan_t scanner, YYSTYPE *result);

extern int yylex(YYSTYPE *lvalp, YYLTYPE *llocp, yyscan_t scanner);
%}

%token          _ERROR_
%token          _BANGEQ     /* != */
%token          _PERCENT    /* % */
%token          _DAMP       /* && */
%token          _STAR       /* * */
%token          _PLUS       /* + */
%token          _DPLUS      /* ++ */
%token          _MINUS      /* - */
%token          _DMINUS     /* -- */
%token          _SLASH      /* / */
%token          _COLON      /* : */
%token          _COLONEQ    /* := */
%token          _SEMI       /* ; */
%token          _LT         /* < */
%token          _LDARROW    /* <= */
%token          _DEQ        /* == */
%token          _GT         /* > */
%token          _GTEQ       /* >= */
%token          _SYMB_2     /* _call */
%token          _SYMB_7     /* _go_next */
%token          _SYMB_6     /* _goto */
%token          _KW_else    /* else */
%token          _KW_if      /* if */
%token          _KW_return  /* return */
%token          _KW_then    /* then */
%token          _DBAR       /* || */
%token<_string> T_UIdent    /* UIdent */
%token<_string> _STRING_
%token<_int>    _INTEGER_

%type <program_> Program
%type <codeblock_> CodeBlock
%type <nonjmpstmt_> NonJmpStmt
%type <jmpstmt_> JmpStmt
%type <atom_> Atom
%type <binop_> BinOp
%type <listcodeblock_> ListCodeBlock
%type <listnonjmpstmt_> ListNonJmpStmt
%type <listjmpstmt_> ListJmpStmt
%type <listatom_> ListAtom

%start Program

%%

Program : ListCodeBlock { $$ = new Prog($1); result->program_ = $$; }
;
CodeBlock : T_UIdent _COLON ListNonJmpStmt ListJmpStmt { std::reverse($4->begin(),$4->end()) ;$$ = new Block($1, $3, $4); }
;
NonJmpStmt : T_UIdent _COLONEQ Atom BinOp Atom { $$ = new StmtBinOp($1, $3, $4, $5); }
  | T_UIdent _COLONEQ Atom { $$ = new StmtNoOp($1, $3); }
  | T_UIdent _COLONEQ _SYMB_2 T_UIdent ListAtom _SEMI { $$ = new StmtCall($1, $4, $5); }
  | T_UIdent _DPLUS { $$ = new StmtInc($1); }
  | T_UIdent _DMINUS { $$ = new StmtDecr($1); }
;
JmpStmt : _SYMB_6 T_UIdent { $$ = new StmtGoto($2); }
  | _SYMB_7 { $$ = new StmtGoNext(); }
  | _KW_if Atom _KW_then _SYMB_6 T_UIdent _KW_else _SYMB_6 T_UIdent { $$ = new StmtCondJmp($2, $5, $8); }
  | _KW_return Atom { $$ = new StmtRet($2); }
  | _KW_return { $$ = new StmtVRet(); }
;
Atom : T_UIdent { $$ = new AtomVar($1); }
  | _INTEGER_ { $$ = new AtomInt($1); }
  | _STRING_ { $$ = new AtomStr($1); }
;
BinOp : _PLUS { $$ = new AddOp(); }
  | _MINUS { $$ = new SubOp(); }
  | _STAR { $$ = new MulOp(); }
  | _SLASH { $$ = new DivOp(); }
  | _PERCENT { $$ = new ModOp(); }
  | _DAMP { $$ = new AndOp(); }
  | _DBAR { $$ = new OrOp(); }
  | _LT { $$ = new LTH(); }
  | _LDARROW { $$ = new LE(); }
  | _GT { $$ = new GTH(); }
  | _GTEQ { $$ = new GE(); }
  | _DEQ { $$ = new EQU(); }
  | _BANGEQ { $$ = new NE(); }
;
ListCodeBlock : /* empty */ { $$ = new ListCodeBlock(); }
  | ListCodeBlock CodeBlock { $1->push_back($2); $$ = $1; }
;
ListNonJmpStmt : /* empty */ { $$ = new ListNonJmpStmt(); }
  | ListNonJmpStmt NonJmpStmt { $1->push_back($2); $$ = $1; }
;
ListJmpStmt : JmpStmt { $$ = new ListJmpStmt(); $$->push_back($1); }
  | JmpStmt ListJmpStmt { $2->push_back($1); $$ = $2; }
;
ListAtom : /* empty */ { $$ = new ListAtom(); }
  | ListAtom Atom { $1->push_back($2); $$ = $1; }
;

%%


/* Entrypoint: parse Program* from file. */
Program* pProgram(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = fvc__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  fvc_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.program_;
  }
}

/* Entrypoint: parse Program* from string. */
Program* psProgram(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = fvc__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = fvc__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  fvc__delete_buffer(buf, scanner);
  fvc_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.program_;
  }
}



