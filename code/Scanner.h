/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2021
*************************************************************
* File name: Scanner.h
* Compiler: MS Visual Studio 2019, GCC 9.3.0
* Author: Svillen Ranev - Paulo Sousa, Jon Liu 040967432, Tyson Moyes 040761903
* Course: CST 8152 - Compilers, Lab Section: 013
* Assignment: A22
* Date: July 7, 2021
* Purpose: This file is the main header for Scanner (.h)
* Function list:
* - startScanner
* - tokenizer
* - nextState
* - nextClass
* - funcVID
* - funcIL
* - funcFL
* - funcSL
* - funcKW
* - funcEr
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */ /*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/ /* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 8  /* variable identifier length */
#define ERR_LEN 20 /* error message length */
#define NUM_LEN 5  /* maximum number of digits for IL */

#define RTE_CODE 1 /* Value for run-time error */

enum TOKENS
{
  ERR_T,    /* Error token */
  VID_T,    /* Variable Identifier */
  INL_T,    /* Integer literal token */
  FPL_T,    /* Floating point literal token */
  STR_T,    /* String literal token */
  SCC_OP_T, /* String concatenation operator token: (++) */
  ASS_OP_T, /* Assignment operator token */
  ART_OP_T, /* Arithmetic operator token */
  REL_OP_T, /* Relational operator token */
  LOG_OP_T, /* Logical operator token */
  LPR_T,    /* Left parenthesis token */
  RPR_T,    /* Right parenthesis token */
  LBR_T,    /* Left bracket token */
  RBR_T,    /* Right bracket token */
  KW_T,     /* Keyword token */
  COM_T,    /* Comma token */
  RTE_T,    /* Run-time error token */
  SEOF_T    /* Source end-of-file token */
};

/* CHECK: Operators token attributes */
typedef enum ArithmeticOperators
{
  ADD,
  SUB,
  MUL,
  DIV
} AriOperator;
typedef enum RelationalOperators
{
  EQ,
  NE,
  GT,
  LT
} RelOperator;
typedef enum LogicalOperators
{
  AND,
  OR,
  NOT
} LogOperator;
typedef enum SourceEndOfFile
{
  SEOF_0,
  SEOF_EOF
} EofOperator;

typedef union TokenAttribute
{
  zz_int codeType;                /* integer attributes accessor */
  AriOperator arithmeticOperator; /* arithmetic operator attribute code */
  RelOperator relationalOperator; /* relational operator attribute code */
  LogOperator logicalOperator;    /* logical operator attribute code */
  EofOperator seofType;           /* source-end-of-file attribute code */
  zz_int intValue;                /* integer literal attribute (value) */
  zz_int keywordIndex;            /* keyword index in the keyword table */
  zz_int contentString;           /* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
  zz_flt floatValue;              /* floating-point literal attribute (value) */
  zz_char vidLexeme[VID_LEN + 1]; /* variable identifier token attribute */
  zz_char errLexeme[ERR_LEN + 1]; /* error token attribite */
} TokenAttribute;

typedef struct VidAttibutes
{
  zz_flags flags; /* Flags information */
  union
  {
    zz_int intValue;       /* Integer value */
    zz_flt floatValue;     /* Float value */
    zz_nul *stringContent; /* String value */
  } values;
} VidAttibutes;

/* CHECK: Token declaration */
typedef struct Token
{
  zz_int code;               /* token code */
  TokenAttribute attribute;  /* token attribute */
  VidAttibutes vidAttribute; /* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* CHECK: EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/* Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';', 
 *  white space, @comment@ , ',' , ';' , '-' , '+' , '*' , '/', ## , 
 *  .&., .|. , .!. , SEOF.
 */

#define ES 14 /* Error state with no retract */
#define ER 13 /* Error state with retract */
#define IS -1 /* Illegal state */

#define TABLE_COLUMNS 8

/* TODO: 6: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
/* TODO: Not sure if we need CHRCOL 1 or 2 since they are ranges */
#define CHRCOL1 '-'
#define CHRCOL2 '1'
/* Updated these to our values according to table from A21 - TM*/
#define CHRCOL3 '~'
#define CHRCOL4 '.'
#define CHRCOL5 '"'
#define CHRCOL6 '#'
/* TODO: not sure if we need this one. */
/* #define CHRCOL7 '\"' */
/* These constants will be used on VID function 
  TODO: Update because I think we are using VID only
*/
#define IVIDPREFIX '#'
#define FVIDPREFIX '%'
#define SVIDPREFIX '$'

/* transitionTable based off values from A21 */
static zz_int transitionTable[][TABLE_COLUMNS] = {
    /*        [A-z], [-?!+-/*=]  [0-9],  ~,    .,    ",    #,   EOFS 	*/
    /*	       L(0),    V(1),     D(2), T(3), R(4), Q(5), H(6), E(7)	*/
    /* S00 */ {1, 1, 3, 2, ES, 8, 10, ER},      /* NOAS */
    /* S01 */ {1, 1, 1, 2, 2, 2, 2, ER},        /* NOAS */
    /* S02 */ {IS, IS, IS, IS, IS, IS, IS, IS}, /* ASWR (VID) */
    /* S03 */ {4, 4, 3, 4, 5, 4, 4, ER},        /* NOAS */
    /* S04 */ {IS, IS, IS, IS, IS, IS, IS, IS}, /* ASNR (IL) */
    /* S05 */ {ES, ES, 6, ES, ES, ES, ES, ER},  /* NOAS */
    /* S06 */ {7, 7, 6, 7, 7, 7, 7, ER},        /* NOAS */
    /* S07 */ {IS, IS, IS, IS, IS, IS, IS, IS}, /* ASWR (FL) */
    /* S08 */ {8, 8, 8, 8, 8, 9, 8, ER},        /* NOAS */
    /* S09 */ {IS, IS, IS, IS, IS, IS, IS, IS}, /* ASNR (SL) */
    /* S10 */ {11, ES, ES, ES, ES, ES, ES, ER}, /* NOAS */
    /* S11 */ {11, 12, 12, 12, 12, 12, 12, ER}, /* NOAS  */
    /* S12 */ {IS, IS, IS, IS, IS, IS, IS, IS}, /* ASWR (KW) */
    /* S13 */ {IS, IS, IS, IS, IS, IS, IS, IS}, /* ASWR (ER)   */
    /* S14 */ {IS, IS, IS, IS, IS, IS, IS, IS}  /* ASNR (ES) */
};

/* CHECK: Define accepting states types */
#define NOAS 0 /* not accepting state */
#define ASNR 1 /* accepting state with no retract */
#define ASWR 2 /* accepting state with retract */

/* List of acceptable states from the transition table */
static zz_int stateType[] = {
    NOAS, /* 00 */
    NOAS, /* 01 */
    ASWR, /* 02 */
    NOAS, /* 03 */
    ASNR, /* 04 */
    NOAS, /* 05 */
    NOAS, /* 06 */
    ASWR, /* 07 */
    NOAS, /* 08 */
    ASNR, /* 09 */
    NOAS, /* 10 */
    NOAS, /* 11 */
    ASWR, /* 12 */
    ASWR, /* 13 */
    ASNR  /* 14 */
};

/* Static (local) function  prototypes */
zz_int startScanner(BufferPointer psc_buf);
static zz_int nextClass(zz_char c);       /* character class function */
static zz_int nextState(zz_int, zz_char); /* state machine function */

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* Pointer to function (of one char * argument) returning Token */
typedef Token (*PTR_ACCFUN)(zz_char *lexeme);

/* Declare accepting states functions */
Token funcVID(zz_char *lexeme);
Token funcIL(zz_char *lexeme);
Token funcFL(zz_char *lexeme);
Token funcSL(zz_char *lexeme);
Token funcKW(zz_char *lexeme);
Token funcErr(zz_char *lexeme);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

static PTR_ACCFUN finalStateTable[] = {
    NULL,    /* 00 */
    NULL,    /* 01 */
    funcVID, /* 02 */
    NULL,    /* 03 */
    funcIL,  /* 04 */
    NULL,    /* 05 */
    NULL,    /* 06 */
    funcFL,  /* 07 */
    NULL,    /* 08 */
    funcSL,  /* 09 */
    NULL,    /* 10 */
    NULL,    /* 11 */
    funcKW,  /* 12 */
    funcErr, /* 13 */
    funcErr, /* 14 */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

#define KWT_SIZE 11

static zz_char *keywordTable[KWT_SIZE] = {
    "soit",
    "soit/mut",
    "demande",
    "imprime",
    "change",
    "cond",
    "sinon",
    "chaque",
    "tant-que",
    "def",
    "retourne"};

#endif