/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2021
*************************************************************
* File name: Parser.h
* Compiler: MS Visual Studio 2019
* Author: Svillen Ranev - Paulo Sousa
* Contributors: Jon Liu 040967432, Tyson Moyes 040761903
* Course: CST 8152 - Compilers, Lab Section: 013
* Assignment: A32.
* Date: May 01 2021
* Purpose: This file is the main header for Parser (.h)
* Function list: (...).
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef BUFFER_H_
#include "Buffer.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token lookahead;
zz_int syntaxErrorNumber = 0;
extern Buffer *stringLiteralTable;
extern zz_int line;
extern Token tokenizer();
extern zz_char *keywordTable[];

#define STR_LANGNAME "Zozotage"

/* Constants */
enum KEYWORDS
{
	NO_ATTR = -1,
	v,
	f,
	nul,
};

/* Function definitions */
zz_nul startParser();
zz_nul matchToken(zz_int, zz_int);
zz_nul syncErrorHandler(zz_int);
zz_nul printError();

/* zz non-terminals */
zz_nul program();
zz_nul opt_statements();
zz_nul statements();
zz_nul statementsPrime();
zz_nul statement();
zz_nul functionExpr();
zz_nul opt_args();
zz_nul args();
zz_nul argsPrime();
zz_nul arg();

#endif
