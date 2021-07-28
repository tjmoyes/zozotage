/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2021
*************************************************************
* File name: Parser.h
* Compiler: MS Visual Studio 2019
* Author: Svillen Ranev - Paulo Sousa
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A3.
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
sofia_int syntaxErrorNumber = 0;
extern Buffer* stringLiteralTable;
extern sofia_int line;
extern Token tokenizer();
extern sofia_chr* keywordTable[];

/* TO_DO: Define the name of your language */
#define STR_LANGNAME "Sofia"

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */
/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	MAIN,
	DATA,
	CODE,
	INT,
	FLOAT,
	STRING,
	IF,
	THEN,
	ELSE,
	WHILE,
	DO,
	READ,
	WRITE
	/* TO_DO: Continue with your keywords */
};

/* TO_DO: Update the typedefs used in your language */

/* Function definitions */
sofia_nul startParser();
sofia_nul matchToken(sofia_int, sofia_int);
sofia_nul syncErrorHandler(sofia_int);
sofia_nul printError();

/* TODO: Place ALL non-terminal function declarations */
sofia_nul additiveArithmeticExpression();
sofia_nul additiveArithmeticExpressionPrime();
sofia_nul arithmeticExpression();
sofia_nul assignmentExpression();
sofia_nul assignmentStatement();
sofia_nul codeSession();
sofia_nul conditionalExpression();
sofia_nul dataSession();
sofia_nul fltVariableIdentifier();
sofia_nul fltVarList();
sofia_nul fltVarListPrime();
sofia_nul inputStatement();
sofia_nul intVariableIdentifier();
sofia_nul intVarList();
sofia_nul intVarListPrime();
sofia_nul iterationStatement();
sofia_nul logicalAndExpression();
sofia_nul logicalAndExpressionPrime();
sofia_nul logicalNotExpression();
sofia_nul logicalOrExpression();
sofia_nul logicalOrExpressionPrime();
sofia_nul multiplicativeArithmeticExpression();
sofia_nul multiplicativeArithmeticExpressionPrime();
sofia_nul fltVarListDeclaration();
sofia_nul intVarListDeclaration();
sofia_nul strVarListDeclaration();
sofia_nul optVarListDeclarations();
sofia_nul optionalStatements();
sofia_nul outputStatement();
sofia_nul outputVariableList();
sofia_nul primaryArithmeticExpression();
sofia_nul primaryRelationalArithmeticExpression();
sofia_nul primaryRelationalStringExpression();
sofia_nul primaryStringExpression();
sofia_nul program();
sofia_nul relationalArithmeticExpression();
sofia_nul relationalArithmeticOperator();
sofia_nul relationalExpression();
sofia_nul relationalStringExpression();
sofia_nul relationalStringOperator();
sofia_nul selectionStatement();
sofia_nul statement();
sofia_nul statements();
sofia_nul statementsPrime();
sofia_nul stringExpression();
sofia_nul stringExpressionPrime();
sofia_nul strVariableIdentifier();
sofia_nul strVarList();
sofia_nul strVarListPrime();
sofia_nul variableIdentifier();
sofia_nul variableList();
sofia_nul variableListPrime();
sofia_nul varListDeclarations();
sofia_nul varListDeclaration();
sofia_nul varListDeclarationsPrime();
//sofia_nul preCondition();

#endif
