/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2021
* Author: Svillen Ranev - Paulo Sousa.
* Contributors: Jon Liu 040967432, Tyson Moyes 040761903
*************************************************************
* File name: Parser.c
* Compiler: MS Visual Studio 2019
* Course: CST 8152 – Compilers, Lab Section: 013
* Assignment: A3.
* Date: May 01 2021
* Professor: Paulo Sousa
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/*************************************************************
 * Process Parser
 ************************************************************/

zz_nul startParser()
{
	lookahead = tokenizer();
	program();
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}

/*************************************************************
 * Match Token
 ************************************************************/
/* TODO: This is the main code for match - check your definition */
zz_nul matchToken(zz_int tokenCode, zz_int tokenAttribute)
{
	zz_int matchFlag = 1;
	switch (lookahead.code)
	{
	case KW_T:
		// TO_DO: Include the other cases
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag)
	{
		lookahead = tokenizer();
		if (lookahead.code == ERR_T)
		{
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*************************************************************
 * Syncronize Error Handler
 ************************************************************/
zz_nul syncErrorHandler(zz_int syncTokenCode)
{
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode)
	{
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*************************************************************
 * Print Error
 ************************************************************/
zz_nul printError()
{
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code)
	{
	case ERR_T:
		printf("%s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case STR_T:
		printf("%s\n", bufferGetSubString(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("%s\n", keywordTable[t.attribute.codeType]);
		break;
	//case ASS_OP_T:
	case LPR_T:
	case RPR_T:
	case LBR_T:
	case RBR_T:
		printf("NA\n");
		break;
	//case EOS_T:
	//	printf("NA\n");
	//	break;
	// TO_DO: Adjust the other cases
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
	}
}

/*************************************************************
 * Program statement
 * BNF: <program> -> (def (entree) <opt_statements>)
 * FIRST(<program>)= {LPR_T}.
 ************************************************************/
zz_nul program()
{
	switch (lookahead.code)
	{
	case LPR_T:
		if (lookahead.attribute.codeType == STR_T)
		{
			matchToken(LPR_T, NO_ATTR);
			dataSession();
			codeSession();
			matchToken(RPR_T, NO_ATTR);
			break;
		}
		else
		{
			printError();
		}
	case SEOF_T:; // Empty: for optional
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

//TODO: Do we need this?

/*************************************************************
 * dataSession
 * BNF: <dataSession> -> DATA { <opt_varlist_declarations> }
 * FIRST(<program>)= {KW_T (DATA)}.
 ************************************************************/
zz_nul dataSession()
{
	//matchToken(KW_T, DATA);
	matchToken(LBR_T, NO_ATTR);
	optVarListDeclarations();
	matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Code Session parsed");
}

/*************************************************************
 * Optional Var List Declarations
 * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (INT), KW_T (FLOAT), KW_T (STRING)}.
 ************************************************************/
zz_nul optVarListDeclarations()
{
	// TO_DO: Basic implementation
	; // Empty
	printf("%s%s\n", STR_LANGNAME, ": Optional Variable List Declarations parsed");
}

/*************************************************************
 * codeSession statement
 * BNF: <codeSession> -> CODE { <opt_statements> }
 * FIRST(<codeSession>)= {KW_T (CODE)}.
 ************************************************************/
zz_nul codeSession()
{
	//matchToken(KW_T, CODE);
	matchToken(LBR_T, NO_ATTR);
	optionalStatements();
	matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Code Session parsed");
}

/* TODO_205: Continue the development (all non-terminal functions) */

/*************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { LPR_T, ϵ }
 ************************************************************/
zz_nul optionalStatements()
{ // TO_DO: Basic implementation
	switch (lookahead.code)
	{
	case KW_T:
		if (lookahead.attribute.codeType == WRITE)
		{
			statements();
			break;
		}
	default:; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { LPR_T }
 ************************************************************/
zz_nul statements()
{
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { LPR_T, ϵ }
 ************************************************************/
zz_nul statementsPrime()
{
	switch (lookahead.code)
	{
	case KW_T:
		if (lookahead.attribute.codeType == WRITE)
		{
			statement();
			statementsPrime();
			break;
		}
	default:; //empty string
	}
}

/*************************************************************
 * Single statement
 * BNF: <statement> -> <conditional expr> | <iteration expr> | <function expr>
 * FIRST(<statement>) = { LPR_T }
 ************************************************************/
zz_nul statement()
{
	switch (lookahead.code)
	{
	case KW_T:
		switch (lookahead.attribute.codeType)
		{
		case WRITE:
			outputStatement();
			break;
		default:
			printError();
		}
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

/*************************************************************
 * Output Statement
 * BNF: <output statement> -> WRITE (<output statementPrime>);
 * FIRST(<output statement>) = { KW_T(WRITE) }
 ************************************************************/
zz_nul outputStatement()
{
	matchToken(STR_T, NO_ATTR);
	matchToken(LPR_T, NO_ATTR);
	outputVariableList();
	matchToken(RPR_T, NO_ATTR);
	//matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <VID_T> | ϵ
 * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
 ************************************************************/
zz_nul outputVariableList()
{
	switch (lookahead.code)
	{
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	default:;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}

/* TO_DO: Continue developing the non-terminal functions */
