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

/* list of nonterminals in the grammar
program
opt_statements
statements
statementsPrime
statement
conditionalExpr
branches
branch
opt_branches
opt_elsebranch
elsebranch
iterationStatement
functionExpr
opt_args
args
argsPrime
arg
*/

/* TODO: Place ALL non-terminal function declarations */
//zz_nul additiveArithmeticExpression();
//zz_nul additiveArithmeticExpressionPrime();
//zz_nul arithmeticExpression();
zz_nul assignmentExpression();
zz_nul assignmentStatement();
zz_nul codeSession(); // not sure
zz_nul conditionalExpression();
zz_nul dataSession(); // not sure
//zz_nul fltVariableIdentifier();
//zz_nul fltVarList();
//zz_nul fltVarListPrime();
zz_nul inputStatement();
//zz_nul intVariableIdentifier();
//zz_nul intVarList();
//zz_nul intVarListPrime();
zz_nul iterationStatement();
//zz_nul logicalAndExpression();
//zz_nul logicalAndExpressionPrime();
//zz_nul logicalNotExpression();
//zz_nul logicalOrExpression();
//zz_nul logicalOrExpressionPrime();
//zz_nul multiplicativeArithmeticExpression();
//zz_nul multiplicativeArithmeticExpressionPrime();
//zz_nul fltVarListDeclaration();
//zz_nul intVarListDeclaration();
//zz_nul strVarListDeclaration();
//zz_nul optVarListDeclarations();
zz_nul optionalStatements();
zz_nul outputStatement();
zz_nul outputVariableList();
//zz_nul primaryArithmeticExpression();
//zz_nul primaryRelationalArithmeticExpression();
//zz_nul primaryRelationalStringExpression();
//zz_nul primaryStringExpression();
zz_nul program();
//zz_nul relationalArithmeticExpression();
//zz_nul relationalArithmeticOperator();
//zz_nul relationalExpression();
//zz_nul relationalStringExpression();
//zz_nul relationalStringOperator();
zz_nul selectionStatement();
zz_nul statement();
zz_nul statements();
zz_nul statementsPrime();
//zz_nul stringExpression();
//zz_nul stringExpressionPrime();
//zz_nul strVariableIdentifier();
//zz_nul strVarList();
//zz_nul strVarListPrime();
zz_nul variableIdentifier();
zz_nul variableList();
zz_nul variableListPrime();
zz_nul varListDeclarations();
zz_nul varListDeclaration();
zz_nul varListDeclarationsPrime();

#endif
