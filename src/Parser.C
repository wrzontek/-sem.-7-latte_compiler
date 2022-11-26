/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         latte_parse
#define yylex           latte_lex
#define yyerror         latte_error
#define yydebug         latte_debug
#define yynerrs         latte_nerrs

/* First part of user prologue.  */
#line 20 "Latte.y"

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
typedef void *yyscan_t;
#endif

typedef struct yy_buffer_state *YY_BUFFER_STATE;

extern YY_BUFFER_STATE latte__scan_string(const char *str, yyscan_t scanner);

extern void latte__delete_buffer(YY_BUFFER_STATE buf, yyscan_t scanner);

extern void latte_lex_destroy(yyscan_t scanner);

extern char *latte_get_text(yyscan_t scanner);

extern yyscan_t latte__initialize_lexer(FILE *inp);

/* End C preamble code */

#line 104 "Parser.C"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
    _DOT = 271,
    _SLASH = 272,
    _COLON = 273,
    _SEMI = 274,
    _LT = 275,
    _LDARROW = 276,
    _EQ = 277,
    _DEQ = 278,
    _GT = 279,
    _GTEQ = 280,
    _LBRACK = 281,
    _EMPTYBRACK = 282,
    _RBRACK = 283,
    _KW_boolean = 284,
    _KW_class = 285,
    _KW_else = 286,
    _KW_extends = 287,
    _KW_false = 288,
    _KW_for = 289,
    _KW_if = 290,
    _KW_int = 291,
    _KW_new = 292,
    _KW_null = 293,
    _KW_return = 294,
    _KW_string = 295,
    _KW_true = 296,
    _KW_void = 297,
    _KW_while = 298,
    _LBRACE = 299,
    _DBAR = 300,
    _RBRACE = 301,
    _STRING_ = 302,
    _INTEGER_ = 303,
    _IDENT_ = 304
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
    ListClassMember *listclassmember_;
    ListTopDef *listtopdef_;
    Arg *arg_;
    ListArg *listarg_;
    ClassMember *classmember_;
    Block *block_;
    ListStmt *liststmt_;
    Stmt *stmt_;
    Item *item_;
    ListItem *listitem_;
    ComplexStart *complexstart_;
    ComplexPart *complexpart_;
    ArrType *arrtype_;
    Type *type_;
    ArrDimType *arrdimtype_;
    ListArrDimType *listarrdimtype_;
    ListType *listtype_;
    DimDef *dimdef_;
    ListDimDef *listdimdef_;
    Expr *expr_;
    ListComplexPart *listcomplexpart_;
    ListExpr *listexpr_;
    AddOp *addop_;
    MulOp *mulop_;
    RelOp *relop_;

#line 240 "Parser.C"

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

/* Second part of user prologue.  */
#line 84 "Latte.y"

void yyerror(YYLTYPE *loc, yyscan_t scanner, YYSTYPE *result, const char *msg) {
    fprintf(stderr, "ERROR\n");
    fprintf(stderr, "%d,%d: %s at %s\n",
            loc->first_line, loc->first_column, msg, latte_get_text(scanner));
}

int yyparse(yyscan_t scanner, YYSTYPE *result);

extern int yylex(YYSTYPE *lvalp, YYLTYPE *llocp, yyscan_t scanner);

#line 281 "Parser.C"


#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__

# include <limits.h> /* INFRINGES ON USER NAME SPACE */

# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if !defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && !defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && !defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
/* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && !defined EXIT_SUCCESS \
       && !((defined YYMALLOC || defined malloc) \
 && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if !defined malloc && !defined EXIT_SUCCESS

void *malloc(YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if !defined free && !defined EXIT_SUCCESS

void free(void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (!defined yyoverflow \
     && (!defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
 && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc {
    yy_state_t yyss_alloc;
    YYSTYPE yyvs_alloc;
    YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   230

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  169

#define YYUNDEFTOK  2
#define YYMAXUTOK   304


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
        {
                0, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                2, 2, 2, 2, 2, 2, 1, 2, 3, 4,
                5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
                25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
                35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
                45, 46, 47, 48, 49
        };

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
        {
                0, 182, 182, 184, 185, 186, 188, 189, 191, 192,
                194, 196, 197, 198, 200, 201, 203, 205, 206, 208,
                209, 210, 211, 212, 213, 214, 215, 216, 217, 218,
                219, 220, 222, 223, 225, 226, 228, 229, 230, 231,
                232, 233, 235, 236, 237, 238, 240, 241, 242, 243,
                245, 246, 247, 248, 249, 250, 252, 254, 255, 261,
                263, 264, 266, 267, 268, 269, 270, 271, 272, 273,
                274, 276, 277, 279, 280, 281, 283, 284, 286, 287,
                289, 290, 292, 293, 295, 296, 298, 299, 300, 302,
                303, 305, 306, 307, 309, 310, 311, 312, 313, 314
        };
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
        {
                "$end", "error", "$undefined", "_ERROR_", "_BANG", "_BANGEQ",
                "_PERCENT", "_DAMP", "_LPAREN", "_RPAREN", "_STAR", "_PLUS", "_DPLUS",
                "_COMMA", "_MINUS", "_DMINUS", "_DOT", "_SLASH", "_COLON", "_SEMI",
                "_LT", "_LDARROW", "_EQ", "_DEQ", "_GT", "_GTEQ", "_LBRACK",
                "_EMPTYBRACK", "_RBRACK", "_KW_boolean", "_KW_class", "_KW_else",
                "_KW_extends", "_KW_false", "_KW_for", "_KW_if", "_KW_int", "_KW_new",
                "_KW_null", "_KW_return", "_KW_string", "_KW_true", "_KW_void",
                "_KW_while", "_LBRACE", "_DBAR", "_RBRACE", "_STRING_", "_INTEGER_",
                "_IDENT_", "$accept", "Program", "TopDef", "ListClassMember",
                "ListTopDef", "Arg", "ListArg", "ClassMember", "Block", "ListStmt",
                "Stmt", "Item", "ListItem", "ComplexStart", "ComplexPart", "ArrType",
                "Type", "ArrDimType", "ListArrDimType", "DimDef", "ListDimDef", "Expr6",
                "ListComplexPart", "Expr5", "Expr4", "Expr3", "Expr2", "Expr1", "Expr",
                "ListExpr", "AddOp", "MulOp", "RelOp", YY_NULLPTR
        };
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

#define YYPACT_NINF (-122)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-56)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
        {
                -26, -29, -9, -8, 6, -122, 13, 18, -26, -122,
                42, 30, -5, -122, -122, -122, 42, -122, 79, 52,
                -122, -122, -23, 47, 111, 90, 96, 58, -122, -122,
                -122, 62, -23, 81, -122, 163, 7, 118, 113, -122,
                -122, -122, -122, -23, 131, 85, -122, 17, 128, 34,
                140, 34, -122, 57, -122, -122, -122, 64, -122, -122,
                -122, 28, -2, 177, 93, -122, 120, -122, -122, 135,
                138, 122, 141, -122, 69, -122, -122, 85, 192, 81,
                -122, 167, 143, 147, -122, -122, -122, -122, -122, 124,
                131, 109, 131, 124, -122, 84, -122, -122, -122, 131,
                -122, -122, 131, -122, 131, -122, -122, -122, -122, -122,
                131, 131, -23, 131, -122, 142, 131, 146, 148, 155,
                -122, 131, -122, 152, -122, -122, -122, 149, 157, -122,
                168, -122, 131, -122, -122, -122, -122, -122, 28, -122,
                -2, -122, 159, 182, -122, 197, -122, -122, -122, 191,
                -122, 131, -122, -122, 204, 198, 80, 80, -122, -122,
                -122, 166, 186, -122, 209, 80, 80, -122, -122
        };

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
        {
                0, 48, 0, 46, 47, 53, 49, 0, 8, 2,
                0, 0, 0, 1, 9, 56, 57, 54, 0, 0,
                6, 58, 11, 0, 0, 12, 0, 0, 6, 4,
                7, 0, 11, 0, 10, 0, 32, 34, 0, 13,
                17, 3, 5, 11, 0, 0, 14, 0, 0, 0,
                0, 0, 68, 0, 67, 69, 66, 62, 71, 75,
                77, 79, 81, 83, 85, 33, 32, 35, 19, 0,
                0, 0, 0, 16, 62, 20, 18, 0, 0, 0,
                74, 62, 71, 0, 73, 48, 46, 47, 41, 0,
                86, 0, 0, 60, 38, 64, 93, 91, 92, 0,
                89, 90, 0, 99, 0, 94, 95, 98, 96, 97,
                0, 0, 0, 0, 26, 0, 0, 0, 0, 0,
                31, 0, 15, 63, 36, 70, 40, 87, 0, 37,
                0, 61, 86, 45, 42, 72, 43, 76, 78, 82,
                80, 84, 0, 0, 25, 0, 21, 23, 24, 0,
                65, 86, 39, 59, 0, 0, 0, 0, 22, 88,
                44, 0, 27, 29, 0, 0, 0, 28, 30
        };

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
        {
                -122, -122, -122, 193, 211, -122, 1, -122, -31, -122,
                29, -122, -40, 170, -122, 169, 0, -122, 207, -122,
                9, 25, -122, 125, 123, 116, -122, 126, -43, -121,
                -122, -122, -122
        };

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
        {
                -1, 7, 8, 24, 9, 25, 26, 30, 75, 47,
                76, 37, 38, 58, 135, 10, 77, 16, 17, 93,
                94, 59, 95, 60, 61, 62, 63, 64, 78, 128,
                102, 99, 110
        };

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
        {
                11, 65, 41, 1, 2, 67, 1, 83, 11, 100,
                3, 154, 101, 3, 4, 43, 5, 4, 13, 5,
                -52, 49, 27, 6, 31, 50, 6, 19, 115, 44,
                159, 51, 27, 39, 96, 31, 68, 117, 97, 20,
                12, -50, 50, 27, 48, 98, 1, 127, 122, 130,
                52, 69, 70, 3, 53, -51, 71, 4, 54, 5,
                72, 40, -55, 73, 55, 56, 74, 52, 141, 15,
                143, 53, 90, 145, 80, 54, 84, 90, 149, 18,
                91, 55, 56, 57, 49, 91, 85, 22, 50, 127,
                92, 28, 132, 86, 51, 92, -49, 87, 126, 68,
                133, 23, 131, 32, 136, 33, 88, 34, 127, 1,
                92, 36, 142, 52, 69, 70, 3, 53, -55, 71,
                4, 54, 5, 72, 40, 40, 49, 55, 56, 74,
                50, 45, 46, 134, 66, 49, 51, 79, 111, 50,
                1, 114, 44, 112, 49, 51, 113, 3, 50, 116,
                92, 4, 124, 5, 51, 52, 125, 29, 129, 53,
                6, 144, 151, 54, 52, 146, 152, 147, 53, 55,
                56, 57, 54, 52, 148, 90, 123, 53, 55, 56,
                57, 54, 103, 91, 104, 162, 163, 55, 56, 81,
                150, 156, 1, 92, 167, 168, 153, 105, 106, 3,
                107, 108, 109, 4, 118, 5, 157, 119, 155, 42,
                158, 120, 6, 160, 121, 164, 161, 165, 166, 14,
                82, 35, 89, 21, 137, 138, 140, 0, 0, 0,
                139
        };

static const yytype_int16 yycheck[] =
        {
                0, 44, 33, 29, 30, 45, 29, 50, 8, 11,
                36, 132, 14, 36, 40, 8, 42, 40, 0, 42,
                49, 4, 22, 49, 24, 8, 49, 32, 71, 22,
                151, 14, 32, 32, 6, 35, 19, 77, 10, 44,
                49, 49, 8, 43, 43, 17, 29, 90, 79, 92,
                33, 34, 35, 36, 37, 49, 39, 40, 41, 42,
                43, 44, 49, 46, 47, 48, 49, 33, 111, 27,
                113, 37, 8, 116, 49, 41, 51, 8, 121, 49,
                16, 47, 48, 49, 4, 16, 29, 8, 8, 132,
                26, 44, 8, 36, 14, 26, 27, 40, 89, 19,
                16, 49, 93, 13, 95, 9, 49, 49, 151, 29,
                26, 49, 112, 33, 34, 35, 36, 37, 49, 39,
                40, 41, 42, 43, 44, 44, 4, 47, 48, 49,
                8, 13, 19, 49, 49, 4, 14, 9, 45, 8,
                29, 19, 22, 8, 4, 14, 8, 36, 8, 8,
                26, 40, 9, 42, 14, 33, 9, 46, 49, 37,
                49, 19, 13, 41, 33, 19, 9, 19, 37, 47,
                48, 49, 41, 33, 19, 8, 9, 37, 47, 48,
                49, 41, 5, 16, 7, 156, 157, 47, 48, 49,
                38, 9, 29, 26, 165, 166, 28, 20, 21, 36,
                23, 24, 25, 40, 12, 42, 9, 15, 49, 46,
                19, 19, 49, 9, 22, 49, 18, 31, 9, 8,
                50, 28, 53, 16, 99, 102, 110, -1, -1, -1,
                104
        };

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
        {
                0, 29, 30, 36, 40, 42, 49, 51, 52, 54,
                65, 66, 49, 0, 54, 27, 67, 68, 49, 32,
                44, 68, 8, 49, 53, 55, 56, 66, 44, 46,
                57, 66, 13, 9, 49, 53, 49, 61, 62, 56,
                44, 58, 46, 8, 22, 13, 19, 59, 56, 4,
                8, 14, 33, 37, 41, 47, 48, 49, 63, 71,
                73, 74, 75, 76, 77, 78, 49, 62, 19, 34,
                35, 39, 43, 46, 49, 58, 60, 66, 78, 9,
                71, 49, 63, 78, 71, 29, 36, 40, 49, 65,
                8, 16, 26, 69, 70, 72, 6, 10, 17, 81,
                11, 14, 80, 5, 7, 20, 21, 23, 24, 25,
                82, 45, 8, 8, 19, 78, 8, 62, 12, 15,
                19, 22, 58, 9, 9, 9, 70, 78, 79, 49,
                78, 70, 8, 16, 49, 64, 70, 73, 74, 77,
                75, 78, 66, 78, 19, 78, 19, 19, 19, 78,
                38, 13, 9, 28, 79, 49, 9, 9, 19, 79,
                9, 18, 60, 60, 49, 31, 9, 60, 60
        };

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
        {
                0, 50, 51, 52, 52, 52, 53, 53, 54, 54,
                55, 56, 56, 56, 57, 57, 58, 59, 59, 60,
                60, 60, 60, 60, 60, 60, 60, 60, 60, 60,
                60, 60, 61, 61, 62, 62, 63, 63, 63, 63,
                63, 63, 64, 64, 64, 64, 65, 65, 65, 65,
                66, 66, 66, 66, 66, 66, 67, 68, 68, 69,
                70, 70, 71, 71, 71, 71, 71, 71, 71, 71,
                71, 72, 72, 73, 73, 73, 74, 74, 75, 75,
                76, 76, 77, 77, 78, 78, 79, 79, 79, 80,
                80, 81, 81, 81, 82, 82, 82, 82, 82, 82
        };

/* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
        {
                0, 2, 1, 6, 5, 7, 0, 2, 1, 2,
                2, 0, 1, 3, 3, 6, 3, 0, 2, 1,
                1, 3, 4, 3, 3, 3, 2, 5, 7, 5,
                8, 2, 1, 3, 1, 3, 3, 3, 2, 4,
                3, 2, 1, 1, 3, 1, 1, 1, 1, 1,
                1, 1, 1, 1, 2, 1, 1, 1, 2, 3,
                1, 2, 1, 3, 2, 4, 1, 1, 1, 1,
                3, 0, 2, 2, 2, 1, 3, 1, 3, 1,
                3, 1, 3, 1, 3, 1, 0, 1, 3, 1,
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1
        };


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        yyerror (&yylloc, scanner, result, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
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
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF

#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */

#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_(FILE *yyo, YYLTYPE const *const yylocp) {
    int res = 0;
    int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
    if (0 <= yylocp->first_line) {
        res += YYFPRINTF(yyo, "%d", yylocp->first_line);
        if (0 <= yylocp->first_column)
            res += YYFPRINTF(yyo, ".%d", yylocp->first_column);
    }
    if (0 <= yylocp->last_line) {
        if (yylocp->first_line < yylocp->last_line) {
            res += YYFPRINTF(yyo, "-%d", yylocp->last_line);
            if (0 <= end_col)
                res += YYFPRINTF(yyo, ".%d", end_col);
        } else if (0 <= end_col && yylocp->first_column < end_col)
            res += YYFPRINTF(yyo, "-%d", end_col);
    }
    return res;
}

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, scanner, result); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print(FILE *yyo, int yytype, YYSTYPE const *const yyvaluep, YYLTYPE const *const yylocationp,
                      yyscan_t scanner, YYSTYPE *result) {
    FILE *yyoutput = yyo;
    YYUSE (yyoutput);
    YYUSE (yylocationp);
    YYUSE (scanner);
    YYUSE (result);
    if (!yyvaluep)
        return;
# ifdef YYPRINT
        if (yytype < YYNTOKENS)
          YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
    YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
    YYUSE (yytype);
    YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print(FILE *yyo, int yytype, YYSTYPE const *const yyvaluep, YYLTYPE const *const yylocationp,
                yyscan_t scanner, YYSTYPE *result) {
    YYFPRINTF(yyo, "%s %s (",
              yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

    YY_LOCATION_PRINT (yyo, *yylocationp);
    YYFPRINTF(yyo, ": ");
    yy_symbol_value_print(yyo, yytype, yyvaluep, yylocationp, scanner, result);
    YYFPRINTF(yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print(yy_state_t *yybottom, yy_state_t *yytop) {
    YYFPRINTF(stderr, "Stack now");
    for (; yybottom <= yytop; yybottom++) {
        int yybot = *yybottom;
        YYFPRINTF(stderr, " %d", yybot);
    }
    YYFPRINTF(stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print(yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, yyscan_t scanner, YYSTYPE *result) {
    int yylno = yyrline[yyrule];
    int yynrhs = yyr2[yyrule];
    int yyi;
    YYFPRINTF(stderr, "Reducing stack by rule %d (line %d):\n",
              yyrule - 1, yylno);
    /* The symbols being reduced.  */
    for (yyi = 0; yyi < yynrhs; yyi++) {
        YYFPRINTF(stderr, "   $%d = ", yyi + 1);
        yy_symbol_print(stderr,
                        yystos[+yyssp[yyi + 1 - yynrhs]],
                        &yyvsp[(yyi + 1) - (yynrhs)], &(yylsp[(yyi + 1) - (yynrhs)]), scanner, result);
        YYFPRINTF(stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, scanner, result); \
} while (0)

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
#ifndef YYINITDEPTH
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct(const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, yyscan_t scanner, YYSTYPE *result) {
    YYUSE (yyvaluep);
    YYUSE (yylocationp);
    YYUSE (scanner);
    YYUSE (result);
    if (!yymsg)
        yymsg = "Deleting";
    YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
    YYUSE (yytype);
    YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*----------.
| yyparse.  |
`----------*/

int
yyparse(yyscan_t scanner, YYSTYPE *result) {
/* The lookahead symbol.  */
    int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
    YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
    YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
    static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
            = {1, 1, 1, 1}
# endif
    ;
    YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

    int yyn;
    int yyresult;
    /* Lookahead token as an internal (translated) token number.  */
    int yytoken = 0;
    /* The variables used to return semantic value and location from the
       action routines.  */
    YYSTYPE yyval;
    YYLTYPE yyloc;

#if YYERROR_VERBOSE
    /* Buffer for error messages, and its allocated size.  */
    char yymsgbuf[128];
    char *yymsg = yymsgbuf;
    YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

    /* The number of symbols on the RHS of the reduced rule.
       Keep to zero when no symbol should be popped.  */
    int yylen = 0;

    yyssp = yyss = yyssa;
    yyvsp = yyvs = yyvsa;
    yylsp = yyls = yylsa;
    yystacksize = YYINITDEPTH;

    YYDPRINTF ((stderr, "Starting parse\n"));

    yystate = 0;
    yyerrstatus = 0;
    yynerrs = 0;
    yychar = YYEMPTY; /* Cause a token to be read.  */
    yylsp[0] = yylloc;
    goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
    yynewstate:
    /* In all cases, when you get here, the value and location stacks
       have just been pushed.  So pushing a state here evens the stacks.  */
    yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
    yysetstate:
    YYDPRINTF ((stderr, "Entering state %d\n", yystate));
    YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
    YY_IGNORE_USELESS_CAST_BEGIN
    *yyssp = YY_CAST (yy_state_t, yystate);
    YY_IGNORE_USELESS_CAST_END

    if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
        goto yyexhaustedlab;
#else
    {
        /* Get the current used size of the three stacks, in elements.  */
        YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
        {
          /* Give user a chance to reallocate the stack.  Use copies of
             these so that the &'s don't force the real ones into
             memory.  */
          yy_state_t *yyss1 = yyss;
          YYSTYPE *yyvs1 = yyvs;
          YYLTYPE *yyls1 = yyls;

          /* Each stack pointer address is followed by the size of the
             data in use in that stack, in bytes.  This used to be a
             conditional around just the two extra args, but that might
             be undefined if yyoverflow is a macro.  */
          yyoverflow (YY_("memory exhausted"),
                      &yyss1, yysize * YYSIZEOF (*yyssp),
                      &yyvs1, yysize * YYSIZEOF (*yyvsp),
                      &yyls1, yysize * YYSIZEOF (*yylsp),
                      &yystacksize);
          yyss = yyss1;
          yyvs = yyvs1;
          yyls = yyls1;
        }
# else /* defined YYSTACK_RELOCATE */
        /* Extend the stack our own way.  */
        if (YYMAXDEPTH <= yystacksize)
            goto yyexhaustedlab;
        yystacksize *= 2;
        if (YYMAXDEPTH < yystacksize)
            yystacksize = YYMAXDEPTH;

        {
            yy_state_t *yyss1 = yyss;
            union yyalloc *yyptr =
                    YY_CAST (union yyalloc *,
                             YYSTACK_ALLOC(YY_CAST(YYSIZE_T, YYSTACK_BYTES(yystacksize))));
            if (!yyptr)
                goto yyexhaustedlab;
            YYSTACK_RELOCATE (yyss_alloc, yyss);
            YYSTACK_RELOCATE (yyvs_alloc, yyvs);
            YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
            if (yyss1 != yyssa)
                YYSTACK_FREE(yyss1);
        }
# endif

        yyssp = yyss + yysize - 1;
        yyvsp = yyvs + yysize - 1;
        yylsp = yyls + yysize - 1;

        YY_IGNORE_USELESS_CAST_BEGIN
        YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                YY_CAST(long, yystacksize)));
        YY_IGNORE_USELESS_CAST_END

        if (yyss + yystacksize - 1 <= yyssp)
            YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
    if (yychar == YYEMPTY) {
        YYDPRINTF ((stderr, "Reading a token: "));
        yychar = yylex(&yylval, &yylloc, scanner);
    }

    if (yychar <= YYEOF) {
        yychar = yytoken = YYEOF;
        YYDPRINTF ((stderr, "Now at end of input.\n"));
    } else {
        yytoken = YYTRANSLATE (yychar);
        YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
        goto yydefault;
    yyn = yytable[yyn];
    if (yyn <= 0) {
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
    yystate = yyn;
    YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
    *++yyvsp = yylval;
    YY_IGNORE_MAYBE_UNINITIALIZED_END
    *++yylsp = yylloc;

    /* Discard the shifted token.  */
    yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
    yyreduce:
    /* yyn is the number of a rule to reduce with.  */
    yylen = yyr2[yyn];

    /* If YYLEN is nonzero, implement the default value of the action:
       '$$ = $1'.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  Assigning to YYVAL
       unconditionally makes the parser a bit smaller, and it avoids a
       GCC warning that YYVAL may be used uninitialized.  */
    yyval = yyvsp[1 - yylen];

    /* Default location. */
    YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
    yyerror_range[1] = yyloc;
    YY_REDUCE_PRINT (yyn);
    switch (yyn) {
        case 2:
#line 182 "Latte.y"
        {
            std::reverse((yyvsp[0].listtopdef_)->begin(), (yyvsp[0].listtopdef_)->end());
            (yyval.program_) = new Prog((yyvsp[0].listtopdef_));
            (yyval.program_)->line_number = (yyloc).first_line;
            (yyval.program_)->char_number = (yyloc).first_column;
            result->program_ = (yyval.program_);
        }
#line 1685 "Parser.C"
            break;

        case 3:
#line 184 "Latte.y"
        {
            std::reverse((yyvsp[-2].listarg_)->begin(), (yyvsp[-2].listarg_)->end());
            (yyval.topdef_) = new FnDef((yyvsp[-5].type_), (yyvsp[-4]._string), (yyvsp[-2].listarg_),
                                        (yyvsp[0].block_));
            (yyval.topdef_)->line_number = (yyloc).first_line;
            (yyval.topdef_)->char_number = (yyloc).first_column;
        }
#line 1691 "Parser.C"
            break;

        case 4:
#line 185 "Latte.y"
        {
            (yyval.topdef_) = new ClassDef((yyvsp[-3]._string), (yyvsp[-1].listclassmember_));
            (yyval.topdef_)->line_number = (yyloc).first_line;
            (yyval.topdef_)->char_number = (yyloc).first_column;
        }
#line 1697 "Parser.C"
            break;

        case 5:
#line 186 "Latte.y"
        {
            (yyval.topdef_) = new ClassExtendDef((yyvsp[-5]._string), (yyvsp[-3]._string),
                                                 (yyvsp[-1].listclassmember_));
            (yyval.topdef_)->line_number = (yyloc).first_line;
            (yyval.topdef_)->char_number = (yyloc).first_column;
        }
#line 1703 "Parser.C"
            break;

        case 6:
#line 188 "Latte.y"
        {
            (yyval.listclassmember_) = new ListClassMember();
        }
#line 1709 "Parser.C"
            break;

        case 7:
#line 189 "Latte.y"
        {
            (yyvsp[-1].listclassmember_)->push_back((yyvsp[0].classmember_));
            (yyval.listclassmember_) = (yyvsp[-1].listclassmember_);
        }
#line 1715 "Parser.C"
            break;

        case 8:
#line 191 "Latte.y"
        {
            (yyval.listtopdef_) = new ListTopDef();
            (yyval.listtopdef_)->push_back((yyvsp[0].topdef_));
        }
#line 1721 "Parser.C"
            break;

        case 9:
#line 192 "Latte.y"
        {
            (yyvsp[0].listtopdef_)->push_back((yyvsp[-1].topdef_));
            (yyval.listtopdef_) = (yyvsp[0].listtopdef_);
        }
#line 1727 "Parser.C"
            break;

        case 10:
#line 194 "Latte.y"
        {
            (yyval.arg_) = new Ar((yyvsp[-1].type_), (yyvsp[0]._string));
            (yyval.arg_)->line_number = (yyloc).first_line;
            (yyval.arg_)->char_number = (yyloc).first_column;
        }
#line 1733 "Parser.C"
            break;

        case 11:
#line 196 "Latte.y"
        {
            (yyval.listarg_) = new ListArg();
        }
#line 1739 "Parser.C"
            break;

        case 12:
#line 197 "Latte.y"
        {
            (yyval.listarg_) = new ListArg();
            (yyval.listarg_)->push_back((yyvsp[0].arg_));
        }
#line 1745 "Parser.C"
            break;

        case 13:
#line 198 "Latte.y"
        {
            (yyvsp[0].listarg_)->push_back((yyvsp[-2].arg_));
            (yyval.listarg_) = (yyvsp[0].listarg_);
        }
#line 1751 "Parser.C"
            break;

        case 14:
#line 200 "Latte.y"
        {
            std::reverse((yyvsp[-1].listitem_)->begin(), (yyvsp[-1].listitem_)->end());
            (yyval.classmember_) = new AttrMember((yyvsp[-2].type_), (yyvsp[-1].listitem_));
            (yyval.classmember_)->line_number = (yyloc).first_line;
            (yyval.classmember_)->char_number = (yyloc).first_column;
        }
#line 1757 "Parser.C"
            break;

        case 15:
#line 201 "Latte.y"
        {
            std::reverse((yyvsp[-2].listarg_)->begin(), (yyvsp[-2].listarg_)->end());
            (yyval.classmember_) = new MethodMember((yyvsp[-5].type_), (yyvsp[-4]._string), (yyvsp[-2].listarg_),
                                                    (yyvsp[0].block_));
            (yyval.classmember_)->line_number = (yyloc).first_line;
            (yyval.classmember_)->char_number = (yyloc).first_column;
        }
#line 1763 "Parser.C"
            break;

        case 16:
#line 203 "Latte.y"
        {
            (yyval.block_) = new Blk((yyvsp[-1].liststmt_));
            (yyval.block_)->line_number = (yyloc).first_line;
            (yyval.block_)->char_number = (yyloc).first_column;
        }
#line 1769 "Parser.C"
            break;

        case 17:
#line 205 "Latte.y"
        {
            (yyval.liststmt_) = new ListStmt();
        }
#line 1775 "Parser.C"
            break;

        case 18:
#line 206 "Latte.y"
        {
            (yyvsp[-1].liststmt_)->push_back((yyvsp[0].stmt_));
            (yyval.liststmt_) = (yyvsp[-1].liststmt_);
        }
#line 1781 "Parser.C"
            break;

        case 19:
#line 208 "Latte.y"
        {
            (yyval.stmt_) = new Empty();
            (yyval.stmt_)->line_number = (yyloc).first_line;
            (yyval.stmt_)->char_number = (yyloc).first_column;
        }
#line 1787 "Parser.C"
            break;

        case 20:
#line 209 "Latte.y"
        {
            (yyval.stmt_) = new BStmt((yyvsp[0].block_));
            (yyval.stmt_)->line_number = (yyloc).first_line;
            (yyval.stmt_)->char_number = (yyloc).first_column;
        }
#line 1793 "Parser.C"
            break;

        case 21:
#line 210 "Latte.y"
        {
            std::reverse((yyvsp[-1].listitem_)->begin(), (yyvsp[-1].listitem_)->end());
            (yyval.stmt_) = new Decl((yyvsp[-2].type_), (yyvsp[-1].listitem_));
            (yyval.stmt_)->line_number = (yyloc).first_line;
            (yyval.stmt_)->char_number = (yyloc).first_column;
        }
#line 1799 "Parser.C"
            break;

        case 22:
#line 211 "Latte.y"
        {
            (yyval.stmt_) = new Ass((yyvsp[-3].expr_), (yyvsp[-1].expr_));
            (yyval.stmt_)->line_number = (yyloc).first_line;
            (yyval.stmt_)->char_number = (yyloc).first_column;
        }
#line 1805 "Parser.C"
            break;

        case 23:
#line 212 "Latte.y"
        {
            (yyval.stmt_) = new Incr((yyvsp[-2].expr_));
            (yyval.stmt_)->line_number = (yyloc).first_line;
            (yyval.stmt_)->char_number = (yyloc).first_column;
        }
#line 1811 "Parser.C"
            break;

        case 24:
#line 213 "Latte.y"
        {
            (yyval.stmt_) = new Decr((yyvsp[-2].expr_));
            (yyval.stmt_)->line_number = (yyloc).first_line;
            (yyval.stmt_)->char_number = (yyloc).first_column;
        }
#line 1817 "Parser.C"
            break;

        case 25:
#line 214 "Latte.y"
        {
            (yyval.stmt_) = new Ret((yyvsp[-1].expr_));
            (yyval.stmt_)->line_number = (yyloc).first_line;
            (yyval.stmt_)->char_number = (yyloc).first_column;
        }
#line 1823 "Parser.C"
            break;

        case 26:
#line 215 "Latte.y"
        {
            (yyval.stmt_) = new VRet();
            (yyval.stmt_)->line_number = (yyloc).first_line;
            (yyval.stmt_)->char_number = (yyloc).first_column;
        }
#line 1829 "Parser.C"
            break;

        case 27:
#line 216 "Latte.y"
        {
            (yyval.stmt_) = new Cond((yyvsp[-2].expr_), (yyvsp[0].stmt_));
            (yyval.stmt_)->line_number = (yyloc).first_line;
            (yyval.stmt_)->char_number = (yyloc).first_column;
        }
#line 1835 "Parser.C"
            break;

        case 28:
#line 217 "Latte.y"
        {
            (yyval.stmt_) = new CondElse((yyvsp[-4].expr_), (yyvsp[-2].stmt_), (yyvsp[0].stmt_));
            (yyval.stmt_)->line_number = (yyloc).first_line;
            (yyval.stmt_)->char_number = (yyloc).first_column;
        }
#line 1841 "Parser.C"
            break;

        case 29:
#line 218 "Latte.y"
        {
            (yyval.stmt_) = new While((yyvsp[-2].expr_), (yyvsp[0].stmt_));
            (yyval.stmt_)->line_number = (yyloc).first_line;
            (yyval.stmt_)->char_number = (yyloc).first_column;
        }
#line 1847 "Parser.C"
            break;

        case 30:
#line 219 "Latte.y"
        {
            (yyval.stmt_) = new ForEach((yyvsp[-5].type_), (yyvsp[-4]._string), (yyvsp[-2]._string), (yyvsp[0].stmt_));
            (yyval.stmt_)->line_number = (yyloc).first_line;
            (yyval.stmt_)->char_number = (yyloc).first_column;
        }
#line 1853 "Parser.C"
            break;

        case 31:
#line 220 "Latte.y"
        {
            (yyval.stmt_) = new SExp((yyvsp[-1].expr_));
            (yyval.stmt_)->line_number = (yyloc).first_line;
            (yyval.stmt_)->char_number = (yyloc).first_column;
        }
#line 1859 "Parser.C"
            break;

        case 32:
#line 222 "Latte.y"
        {
            (yyval.item_) = new NoInit((yyvsp[0]._string));
            (yyval.item_)->line_number = (yyloc).first_line;
            (yyval.item_)->char_number = (yyloc).first_column;
        }
#line 1865 "Parser.C"
            break;

        case 33:
#line 223 "Latte.y"
        {
            (yyval.item_) = new Init((yyvsp[-2]._string), (yyvsp[0].expr_));
            (yyval.item_)->line_number = (yyloc).first_line;
            (yyval.item_)->char_number = (yyloc).first_column;
        }
#line 1871 "Parser.C"
            break;

        case 34:
#line 225 "Latte.y"
        {
            (yyval.listitem_) = new ListItem();
            (yyval.listitem_)->push_back((yyvsp[0].item_));
        }
#line 1877 "Parser.C"
            break;

        case 35:
#line 226 "Latte.y"
        {
            (yyvsp[0].listitem_)->push_back((yyvsp[-2].item_));
            (yyval.listitem_) = (yyvsp[0].listitem_);
        }
#line 1883 "Parser.C"
            break;

        case 36:
#line 228 "Latte.y"
        {
            (yyval.complexstart_) = new CBracketed((yyvsp[-1].complexstart_));
            (yyval.complexstart_)->line_number = (yyloc).first_line;
            (yyval.complexstart_)->char_number = (yyloc).first_column;
        }
#line 1889 "Parser.C"
            break;

        case 37:
#line 229 "Latte.y"
        {
            (yyval.complexstart_) = new CMember((yyvsp[-2]._string), (yyvsp[0]._string));
            (yyval.complexstart_)->line_number = (yyloc).first_line;
            (yyval.complexstart_)->char_number = (yyloc).first_column;
        }
#line 1895 "Parser.C"
            break;

        case 38:
#line 230 "Latte.y"
        {
            std::reverse((yyvsp[0].listdimdef_)->begin(), (yyvsp[0].listdimdef_)->end());
            (yyval.complexstart_) = new CArray((yyvsp[-1]._string), (yyvsp[0].listdimdef_));
            (yyval.complexstart_)->line_number = (yyloc).first_line;
            (yyval.complexstart_)->char_number = (yyloc).first_column;
        }
#line 1901 "Parser.C"
            break;

        case 39:
#line 231 "Latte.y"
        {
            std::reverse((yyvsp[-1].listexpr_)->begin(), (yyvsp[-1].listexpr_)->end());
            (yyval.complexstart_) = new CMethod((yyvsp[-3]._string), (yyvsp[-1].listexpr_));
            (yyval.complexstart_)->line_number = (yyloc).first_line;
            (yyval.complexstart_)->char_number = (yyloc).first_column;
        }
#line 1907 "Parser.C"
            break;

        case 40:
#line 232 "Latte.y"
        {
            std::reverse((yyvsp[0].listdimdef_)->begin(), (yyvsp[0].listdimdef_)->end());
            (yyval.complexstart_) = new NewArray((yyvsp[-1].arrtype_), (yyvsp[0].listdimdef_));
            (yyval.complexstart_)->line_number = (yyloc).first_line;
            (yyval.complexstart_)->char_number = (yyloc).first_column;
        }
#line 1913 "Parser.C"
            break;

        case 41:
#line 233 "Latte.y"
        {
            (yyval.complexstart_) = new NewObject((yyvsp[0]._string));
            (yyval.complexstart_)->line_number = (yyloc).first_line;
            (yyval.complexstart_)->char_number = (yyloc).first_column;
        }
#line 1919 "Parser.C"
            break;

        case 42:
#line 235 "Latte.y"
        {
            (yyval.complexpart_) = new Variable((yyvsp[0]._string));
            (yyval.complexpart_)->line_number = (yyloc).first_line;
            (yyval.complexpart_)->char_number = (yyloc).first_column;
        }
#line 1925 "Parser.C"
            break;

        case 43:
#line 236 "Latte.y"
        {
            std::reverse((yyvsp[0].listdimdef_)->begin(), (yyvsp[0].listdimdef_)->end());
            (yyval.complexpart_) = new ArrElement((yyvsp[0].listdimdef_));
            (yyval.complexpart_)->line_number = (yyloc).first_line;
            (yyval.complexpart_)->char_number = (yyloc).first_column;
        }
#line 1931 "Parser.C"
            break;

        case 44:
#line 237 "Latte.y"
        {
            std::reverse((yyvsp[-1].listexpr_)->begin(), (yyvsp[-1].listexpr_)->end());
            (yyval.complexpart_) = new Method((yyvsp[-1].listexpr_));
            (yyval.complexpart_)->line_number = (yyloc).first_line;
            (yyval.complexpart_)->char_number = (yyloc).first_column;
        }
#line 1937 "Parser.C"
            break;

        case 45:
#line 238 "Latte.y"
        {
            (yyval.complexpart_) = new MemberAccess();
            (yyval.complexpart_)->line_number = (yyloc).first_line;
            (yyval.complexpart_)->char_number = (yyloc).first_column;
        }
#line 1943 "Parser.C"
            break;

        case 46:
#line 240 "Latte.y"
        {
            (yyval.arrtype_) = new IntArrType();
            (yyval.arrtype_)->line_number = (yyloc).first_line;
            (yyval.arrtype_)->char_number = (yyloc).first_column;
        }
#line 1949 "Parser.C"
            break;

        case 47:
#line 241 "Latte.y"
        {
            (yyval.arrtype_) = new StrArrType();
            (yyval.arrtype_)->line_number = (yyloc).first_line;
            (yyval.arrtype_)->char_number = (yyloc).first_column;
        }
#line 1955 "Parser.C"
            break;

        case 48:
#line 242 "Latte.y"
        {
            (yyval.arrtype_) = new BoolArrType();
            (yyval.arrtype_)->line_number = (yyloc).first_line;
            (yyval.arrtype_)->char_number = (yyloc).first_column;
        }
#line 1961 "Parser.C"
            break;

        case 49:
#line 243 "Latte.y"
        {
            (yyval.arrtype_) = new ClassArrType((yyvsp[0]._string));
            (yyval.arrtype_)->line_number = (yyloc).first_line;
            (yyval.arrtype_)->char_number = (yyloc).first_column;
        }
#line 1967 "Parser.C"
            break;

        case 50:
#line 245 "Latte.y"
        {
            (yyval.type_) = new Int();
            (yyval.type_)->line_number = (yyloc).first_line;
            (yyval.type_)->char_number = (yyloc).first_column;
        }
#line 1973 "Parser.C"
            break;

        case 51:
#line 246 "Latte.y"
        {
            (yyval.type_) = new Str();
            (yyval.type_)->line_number = (yyloc).first_line;
            (yyval.type_)->char_number = (yyloc).first_column;
        }
#line 1979 "Parser.C"
            break;

        case 52:
#line 247 "Latte.y"
        {
            (yyval.type_) = new Bool();
            (yyval.type_)->line_number = (yyloc).first_line;
            (yyval.type_)->char_number = (yyloc).first_column;
        }
#line 1985 "Parser.C"
            break;

        case 53:
#line 248 "Latte.y"
        {
            (yyval.type_) = new Void();
            (yyval.type_)->line_number = (yyloc).first_line;
            (yyval.type_)->char_number = (yyloc).first_column;
        }
#line 1991 "Parser.C"
            break;

        case 54:
#line 249 "Latte.y"
        {
            std::reverse((yyvsp[0].listarrdimtype_)->begin(), (yyvsp[0].listarrdimtype_)->end());
            (yyval.type_) = new Arr((yyvsp[-1].arrtype_), (yyvsp[0].listarrdimtype_));
            (yyval.type_)->line_number = (yyloc).first_line;
            (yyval.type_)->char_number = (yyloc).first_column;
        }
#line 1997 "Parser.C"
            break;

        case 55:
#line 250 "Latte.y"
        {
            (yyval.type_) = new Class((yyvsp[0]._string));
            (yyval.type_)->line_number = (yyloc).first_line;
            (yyval.type_)->char_number = (yyloc).first_column;
        }
#line 2003 "Parser.C"
            break;

        case 56:
#line 252 "Latte.y"
        {
            (yyval.arrdimtype_) = new DimType();
            (yyval.arrdimtype_)->line_number = (yyloc).first_line;
            (yyval.arrdimtype_)->char_number = (yyloc).first_column;
        }
#line 2009 "Parser.C"
            break;

        case 57:
#line 254 "Latte.y"
        {
            (yyval.listarrdimtype_) = new ListArrDimType();
            (yyval.listarrdimtype_)->push_back((yyvsp[0].arrdimtype_));
        }
#line 2015 "Parser.C"
            break;

        case 58:
#line 255 "Latte.y"
        {
            (yyvsp[0].listarrdimtype_)->push_back((yyvsp[-1].arrdimtype_));
            (yyval.listarrdimtype_) = (yyvsp[0].listarrdimtype_);
        }
#line 2021 "Parser.C"
            break;

        case 59:
#line 261 "Latte.y"
        {
            (yyval.dimdef_) = new ArrDimDef((yyvsp[-1].expr_));
            (yyval.dimdef_)->line_number = (yyloc).first_line;
            (yyval.dimdef_)->char_number = (yyloc).first_column;
        }
#line 2027 "Parser.C"
            break;

        case 60:
#line 263 "Latte.y"
        {
            (yyval.listdimdef_) = new ListDimDef();
            (yyval.listdimdef_)->push_back((yyvsp[0].dimdef_));
        }
#line 2033 "Parser.C"
            break;

        case 61:
#line 264 "Latte.y"
        {
            (yyvsp[0].listdimdef_)->push_back((yyvsp[-1].dimdef_));
            (yyval.listdimdef_) = (yyvsp[0].listdimdef_);
        }
#line 2039 "Parser.C"
            break;

        case 62:
#line 266 "Latte.y"
        {
            (yyval.expr_) = new EVar((yyvsp[0]._string));
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2045 "Parser.C"
            break;

        case 63:
#line 267 "Latte.y"
        {
            (yyval.expr_) = new EBracketVar((yyvsp[-1]._string));
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2051 "Parser.C"
            break;

        case 64:
#line 268 "Latte.y"
        {
            (yyval.expr_) = new EComplex((yyvsp[-1].complexstart_), (yyvsp[0].listcomplexpart_));
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2057 "Parser.C"
            break;

        case 65:
#line 269 "Latte.y"
        {
            (yyval.expr_) = new ENullCast((yyvsp[-2]._string));
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2063 "Parser.C"
            break;

        case 66:
#line 270 "Latte.y"
        {
            (yyval.expr_) = new ELitInt((yyvsp[0]._int));
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2069 "Parser.C"
            break;

        case 67:
#line 271 "Latte.y"
        {
            (yyval.expr_) = new ELitTrue();
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2075 "Parser.C"
            break;

        case 68:
#line 272 "Latte.y"
        {
            (yyval.expr_) = new ELitFalse();
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2081 "Parser.C"
            break;

        case 69:
#line 273 "Latte.y"
        {
            (yyval.expr_) = new EString((yyvsp[0]._string));
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2087 "Parser.C"
            break;

        case 70:
#line 274 "Latte.y"
        {
            (yyval.expr_) = (yyvsp[-1].expr_);
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2093 "Parser.C"
            break;

        case 71:
#line 276 "Latte.y"
        {
            (yyval.listcomplexpart_) = new ListComplexPart();
        }
#line 2099 "Parser.C"
            break;

        case 72:
#line 277 "Latte.y"
        {
            (yyvsp[-1].listcomplexpart_)->push_back((yyvsp[0].complexpart_));
            (yyval.listcomplexpart_) = (yyvsp[-1].listcomplexpart_);
        }
#line 2105 "Parser.C"
            break;

        case 73:
#line 279 "Latte.y"
        {
            (yyval.expr_) = new Neg((yyvsp[0].expr_));
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2111 "Parser.C"
            break;

        case 74:
#line 280 "Latte.y"
        {
            (yyval.expr_) = new Not((yyvsp[0].expr_));
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2117 "Parser.C"
            break;

        case 75:
#line 281 "Latte.y"
        {
            (yyval.expr_) = (yyvsp[0].expr_);
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2123 "Parser.C"
            break;

        case 76:
#line 283 "Latte.y"
        {
            (yyval.expr_) = new EMul((yyvsp[-2].expr_), (yyvsp[-1].mulop_), (yyvsp[0].expr_));
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2129 "Parser.C"
            break;

        case 77:
#line 284 "Latte.y"
        {
            (yyval.expr_) = (yyvsp[0].expr_);
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2135 "Parser.C"
            break;

        case 78:
#line 286 "Latte.y"
        {
            (yyval.expr_) = new EAdd((yyvsp[-2].expr_), (yyvsp[-1].addop_), (yyvsp[0].expr_));
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2141 "Parser.C"
            break;

        case 79:
#line 287 "Latte.y"
        {
            (yyval.expr_) = (yyvsp[0].expr_);
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2147 "Parser.C"
            break;

        case 80:
#line 289 "Latte.y"
        {
            (yyval.expr_) = new ERel((yyvsp[-2].expr_), (yyvsp[-1].relop_), (yyvsp[0].expr_));
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2153 "Parser.C"
            break;

        case 81:
#line 290 "Latte.y"
        {
            (yyval.expr_) = (yyvsp[0].expr_);
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2159 "Parser.C"
            break;

        case 82:
#line 292 "Latte.y"
        {
            (yyval.expr_) = new EAnd((yyvsp[-2].expr_), (yyvsp[0].expr_));
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2165 "Parser.C"
            break;

        case 83:
#line 293 "Latte.y"
        {
            (yyval.expr_) = (yyvsp[0].expr_);
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2171 "Parser.C"
            break;

        case 84:
#line 295 "Latte.y"
        {
            (yyval.expr_) = new EOr((yyvsp[-2].expr_), (yyvsp[0].expr_));
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2177 "Parser.C"
            break;

        case 85:
#line 296 "Latte.y"
        {
            (yyval.expr_) = (yyvsp[0].expr_);
            (yyval.expr_)->line_number = (yyloc).first_line;
            (yyval.expr_)->char_number = (yyloc).first_column;
        }
#line 2183 "Parser.C"
            break;

        case 86:
#line 298 "Latte.y"
        {
            (yyval.listexpr_) = new ListExpr();
        }
#line 2189 "Parser.C"
            break;

        case 87:
#line 299 "Latte.y"
        {
            (yyval.listexpr_) = new ListExpr();
            (yyval.listexpr_)->push_back((yyvsp[0].expr_));
        }
#line 2195 "Parser.C"
            break;

        case 88:
#line 300 "Latte.y"
        {
            (yyvsp[0].listexpr_)->push_back((yyvsp[-2].expr_));
            (yyval.listexpr_) = (yyvsp[0].listexpr_);
        }
#line 2201 "Parser.C"
            break;

        case 89:
#line 302 "Latte.y"
        {
            (yyval.addop_) = new Plus();
            (yyval.addop_)->line_number = (yyloc).first_line;
            (yyval.addop_)->char_number = (yyloc).first_column;
        }
#line 2207 "Parser.C"
            break;

        case 90:
#line 303 "Latte.y"
        {
            (yyval.addop_) = new Minus();
            (yyval.addop_)->line_number = (yyloc).first_line;
            (yyval.addop_)->char_number = (yyloc).first_column;
        }
#line 2213 "Parser.C"
            break;

        case 91:
#line 305 "Latte.y"
        {
            (yyval.mulop_) = new Times();
            (yyval.mulop_)->line_number = (yyloc).first_line;
            (yyval.mulop_)->char_number = (yyloc).first_column;
        }
#line 2219 "Parser.C"
            break;

        case 92:
#line 306 "Latte.y"
        {
            (yyval.mulop_) = new Div();
            (yyval.mulop_)->line_number = (yyloc).first_line;
            (yyval.mulop_)->char_number = (yyloc).first_column;
        }
#line 2225 "Parser.C"
            break;

        case 93:
#line 307 "Latte.y"
        {
            (yyval.mulop_) = new Mod();
            (yyval.mulop_)->line_number = (yyloc).first_line;
            (yyval.mulop_)->char_number = (yyloc).first_column;
        }
#line 2231 "Parser.C"
            break;

        case 94:
#line 309 "Latte.y"
        {
            (yyval.relop_) = new LTH();
            (yyval.relop_)->line_number = (yyloc).first_line;
            (yyval.relop_)->char_number = (yyloc).first_column;
        }
#line 2237 "Parser.C"
            break;

        case 95:
#line 310 "Latte.y"
        {
            (yyval.relop_) = new LE();
            (yyval.relop_)->line_number = (yyloc).first_line;
            (yyval.relop_)->char_number = (yyloc).first_column;
        }
#line 2243 "Parser.C"
            break;

        case 96:
#line 311 "Latte.y"
        {
            (yyval.relop_) = new GTH();
            (yyval.relop_)->line_number = (yyloc).first_line;
            (yyval.relop_)->char_number = (yyloc).first_column;
        }
#line 2249 "Parser.C"
            break;

        case 97:
#line 312 "Latte.y"
        {
            (yyval.relop_) = new GE();
            (yyval.relop_)->line_number = (yyloc).first_line;
            (yyval.relop_)->char_number = (yyloc).first_column;
        }
#line 2255 "Parser.C"
            break;

        case 98:
#line 313 "Latte.y"
        {
            (yyval.relop_) = new EQU();
            (yyval.relop_)->line_number = (yyloc).first_line;
            (yyval.relop_)->char_number = (yyloc).first_column;
        }
#line 2261 "Parser.C"
            break;

        case 99:
#line 314 "Latte.y"
        {
            (yyval.relop_) = new NE();
            (yyval.relop_)->line_number = (yyloc).first_line;
            (yyval.relop_)->char_number = (yyloc).first_column;
        }
#line 2267 "Parser.C"
            break;


#line 2271 "Parser.C"

        default:
            break;
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
    *++yylsp = yyloc;

    /* Now 'shift' the result of the reduction.  Determine what state
       that goes to, based on the state we popped back to and the rule
       number reduced by.  */
    {
        const int yylhs = yyr1[yyn] - YYNTOKENS;
        const int yyi = yypgoto[yylhs] + *yyssp;
        yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
                   ? yytable[yyi]
                   : yydefgoto[yylhs]);
    }

    goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
    yyerrlab:
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus) {
        ++yynerrs;
#if !YYERROR_VERBOSE
        yyerror(&yylloc, scanner, result, YY_("syntax error"));
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
              yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
          yyerror (&yylloc, scanner, result, yymsgp);
          if (yysyntax_error_status == 2)
            goto yyexhaustedlab;
        }
# undef YYSYNTAX_ERROR
#endif
    }

    yyerror_range[1] = yylloc;

    if (yyerrstatus == 3) {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        if (yychar <= YYEOF) {
            /* Return failure if at end of input.  */
            if (yychar == YYEOF)
                YYABORT;
        } else {
            yydestruct("Error: discarding",
                       yytoken, &yylval, &yylloc, scanner, result);
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
    /* Pacify compilers when the user code never invokes YYERROR and the
       label yyerrorlab therefore never appears in user code.  */
    if (0)
        YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
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
    yyerrstatus = 3;      /* Each real token shifted decrements this.  */

    for (;;) {
        yyn = yypact[yystate];
        if (!yypact_value_is_default (yyn)) {
            yyn += YYTERROR;
            if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR) {
                yyn = yytable[yyn];
                if (0 < yyn)
                    break;
            }
        }

        /* Pop the current state because it cannot handle the error token.  */
        if (yyssp == yyss)
            YYABORT;

        yyerror_range[1] = *yylsp;
        yydestruct("Error: popping",
                   yystos[yystate], yyvsp, yylsp, scanner, result);
        YYPOPSTACK (1);
        yystate = *yyssp;
        YY_STACK_PRINT (yyss, yyssp);
    }

    YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
    *++yyvsp = yylval;
    YY_IGNORE_MAYBE_UNINITIALIZED_END

    yyerror_range[2] = yylloc;
    /* Using YYLLOC is tempting, but would change the location of
       the lookahead.  YYLOC is available though.  */
    YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
    *++yylsp = yyloc;

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
    yyerror(&yylloc, scanner, result, YY_("memory exhausted"));
    yyresult = 2;
    /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
    yyreturn:
    if (yychar != YYEMPTY) {
        /* Make sure we have latest lookahead translation.  See comments at
           user semantic actions for why this is necessary.  */
        yytoken = YYTRANSLATE (yychar);
        yydestruct("Cleanup: discarding lookahead",
                   yytoken, &yylval, &yylloc, scanner, result);
    }
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    YYPOPSTACK (yylen);
    YY_STACK_PRINT (yyss, yyssp);
    while (yyssp != yyss) {
        yydestruct("Cleanup: popping",
                   yystos[+*yyssp], yyvsp, yylsp, scanner, result);
        YYPOPSTACK (1);
    }
#ifndef yyoverflow
    if (yyss != yyssa)
        YYSTACK_FREE(yyss);
#endif
#if YYERROR_VERBOSE
    if (yymsg != yymsgbuf)
      YYSTACK_FREE (yymsg);
#endif
    return yyresult;
}

#line 317 "Latte.y"


/* Entrypoint: parse Program* from file. */
Program *pProgram(FILE *inp) {
    YYSTYPE result;
    yyscan_t scanner = latte__initialize_lexer(inp);
    if (!scanner) {
        fprintf(stderr, "Failed to initialize lexer.\n");
        return 0;
    }
    int error = yyparse(scanner, &result);
    latte_lex_destroy(scanner);
    if (error) { /* Failure */
        return 0;
    } else { /* Success */
        return result.program_;
    }
}

/* Entrypoint: parse Program* from string. */
Program *psProgram(const char *str) {
    YYSTYPE result;
    yyscan_t scanner = latte__initialize_lexer(0);
    if (!scanner) {
        fprintf(stderr, "Failed to initialize lexer.\n");
        return 0;
    }
    YY_BUFFER_STATE buf = latte__scan_string(str, scanner);
    int error = yyparse(scanner, &result);
    latte__delete_buffer(buf, scanner);
    latte_lex_destroy(scanner);
    if (error) { /* Failure */
        return 0;
    } else { /* Success */
        return result.program_;
    }
}



