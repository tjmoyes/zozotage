/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2021
*************************************************************
* File name: Scanner.h
* Compiler: MS Visual Studio 2019
* Author: Svillen Ranev - Paulo Sousa
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A2.
* Date: May 01 2021
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 8   /* variable identifier length */
#define ERR_LEN 20  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1   /* Value for run-time error */

/* TO_DO 2: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/* Error token */
	IVID_T,		/* Arithmetic Variable identifier: Integer token (start: #) */
	FVID_T,		/* Arithmetic Variable identifier: Float point token (start: %) */
	SVID_T,		/* String Variable identifier token (start: $) */
	INL_T,		/* Integer literal token */
	FPL_T,		/* Floating point literal token */
	STR_T,		/* String literal token */
	SCC_OP_T,	/* String concatenation operator token: (++) */
	ASS_OP_T,	/* Assignment operator token */
	ART_OP_T,	/* Arithmetic operator token */
	REL_OP_T,	/* Relational operator token */
	LOG_OP_T,	/* Logical operator token */
	LPR_T,		/* Left parenthesis token */
	RPR_T,		/* Right parenthesis token */
	LBR_T,		/* Left brace token */
	RBR_T,		/* Right brace token */
	KW_T,		/* Keyword token */
	COM_T,		/* Comma token */
	EOS_T,		/* End of statement (semicolon) */
	RTE_T,		/* Run-time error token */
	SEOF_T		/* Source end-of-file token */
};

/* CHECK: Operators token attributes */
typedef enum ArithmeticOperators { ADD, SUB, MUL, DIV } AriOperator;
typedef enum RelationalOperators { EQ, NE, GT, LT } RelOperator;
typedef enum LogicalOperators { AND, OR, NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_EOF } EofOperator;

/* TO_DO 3A: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	sofia_int codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	sofia_int intValue;						/* integer literal attribute (value) */
	sofia_int keywordIndex;					/* keyword index in the keyword table */
	sofia_int contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	sofia_flt floatValue;					/* floating-point literal attribute (value) */
	sofia_chr vidLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	sofia_chr errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO 3B: Should be used if no symbol table is implemented */
typedef struct VidAttibutes {
	sofia_flg flags;			/* Flags information */
	union {
		sofia_int intValue;				/* Integer value */
		sofia_flt floatValue;			/* Float value */
		sofia_nul* stringContent;		/* String value */
	} values;
} VidAttibutes;

/* CHECK: Token declaration */
typedef struct Token {
	sofia_int code;					    /* token code */
	TokenAttribute attribute;		/* token attribute */
	VidAttibutes   vidAttribute;	/* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* CHECK: EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';', 
 *  white space, @comment@ , ',' , ';' , '-' , '+' , '*' , '/', ## , 
 *  .&., .|. , .!. , SEOF.
 */

/* TO_DO 4: Error states and illegal state */
#define ES  16		/* Error state  with no retract */
#define ER  17		/* Error state  with retract */
#define IS -1		/* Illegal state */

 /* TO_DO 5: State transition table definition */
#define TABLE_COLUMNS 10

/* TO_DO 6: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '_'
#define CHRCOL3 '.'
#define CHRCOL4 '#'
#define CHRCOL5 '%'
#define CHRCOL6 '$'
#define CHRCOL7 '\"'
/* These constants will be used on VID function */
#define IVIDPREFIX '#'
#define FVIDPREFIX '%'
#define SVIDPREFIX '$'

/* TO_DO 7: Transition table - type of states defined in separate table */
static sofia_int transitionTable[][TABLE_COLUMNS] = {
	/*			[A-z],	[0-9],	_,		.,		#,		%,		$,		",		SEOF,	other	*/
	/*			L(0),	D(1),	U(2),	P(3),	I(4),	F(5),	S(6),	Q(7),	E(8),	O(9)			*/
	/* S00 */	{14,	7,		ES,		ES,		1,		3,		5,		12,		ER,		ES},	/* NOAS */
	/* S01 */	{1,		1,		1,		2,		2,		2,		2,		2,		ER,		2},		/* NOAS */
	/* S02 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS},	/* ASWR (IVID) */
	/* S03 */	{3,		3,		3,		4,		4,		4,		4,		4,		ER,		4},		/* NOAS */
	/* S04 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS},	/* ASNR (FVID) */
	/* S05 */	{5,		5,		5,		6,		6,		6,		6,		6,		ER,		6},		/* NOAS */
	/* S06 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS},	/* ASWR (SVID) */
	/* S07 */	{8,		7,		8,		9,		8,		8,		8,		8,		ER,		8},		/* NOAS */
	/* S08 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS},	/* ASWR (IL)   */
	/* S09 */	{ES,	10,		ES,		ES,		ES,		ES,		ES,		ES,		ER,		ES},	/* NOAS */
	/* S10 */	{11,	10,		11,		11,		11,		11,		11,		11,		ER,		11},	/* NOAS */
	/* S11 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS},	/* ASWR (FPL)  */
	/* S12 */	{12,	12,		12,		12,		12,		12,		12,		13,		ER,		12},	/* NOAS */
	/* S13 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS},	/* ASNR (SL)   */
	/* S14 */	{14,	15,		15,		15,		15,		15,		15,		15,		ER,		15},	/* NOAS */
	/* S15 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS},	/* ASWR (KEY)  */
	/* S16 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS},	/* ASNR (Err1) */
	/* S17 */	{IS,	IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS,		IS}		/* ASWR (Err2) */ };

/* CHECK: Define accepting states types */
#define NOAS	0		/* not accepting state */
#define ASNR	1		/* accepting state with no retract */
#define ASWR	2		/* accepting state with retract */

/* TO_DO 8: Define list of acceptable states */
static sofia_int stateType[] = {
	NOAS, /* 00 */
	NOAS, /* 01 */
	ASWR, /* 02 (IVID) */
	NOAS, /* 03 */
	ASWR, /* 04 (FVID) */
	NOAS, /* 05 */
	ASWR, /* 06 (SVID) */
	NOAS, /* 07 */
	ASWR, /* 08 (IL) */
	NOAS, /* 09 */
	NOAS, /* 10 */
	ASWR, /* 11 (FPL) */
	NOAS, /* 12 */
	ASNR, /* 13 (SL) */
	NOAS, /* 14 */
	ASWR, /* 15 (KEY) */
	ASNR, /* 16 (Err1) */
	ASWR  /* 17 (Err2) */
};

/*
-------------------------------------------------
TO_DO 9: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
sofia_int startScanner(BufferPointer psc_buf);
static sofia_int nextClass(sofia_chr c);			/* character class function */
static sofia_int nextState(sofia_int, sofia_chr);		/* state machine function */

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO_10A: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(sofia_chr* lexeme);

/* Declare accepting states functions */
Token funcVID	(sofia_chr* lexeme);
Token funcIL	(sofia_chr* lexeme);
Token funcFPL	(sofia_chr* lexeme);
Token funcSL	(sofia_chr* lexeme);
Token funcKEY	(sofia_chr* lexeme);
Token funcErr	(sofia_chr* lexeme);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO_10B: Define final state table */
static PTR_ACCFUN finalStateTable[] = {
	NULL,		/* 00 */
	NULL,		/* 01 */
	funcVID,	/* 02 */
	NULL,		/* 03 */
	funcVID,	/* 04 */
	NULL,		/* 05 */
	funcVID,	/* 06 */
	NULL,		/* 07 */
	funcIL,		/* 08 */
	NULL,		/* 09 */
	NULL,		/* 10 */
	funcFPL,	/* 11 */
	NULL,		/* 12 */
	funcSL,		/* 13 */
	NULL,		/* 14 */
	funcKEY,	/* 15 */
	funcErr,	/* 16 */
	funcErr		/* 17 */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO 11A: Define the number of Keywords from the language */
#define KWT_SIZE 1

/* TO_DO 11B: Define the list of keywords */
static sofia_chr* keywordTable[KWT_SIZE] = {
	"MAIN"
};

#endif
