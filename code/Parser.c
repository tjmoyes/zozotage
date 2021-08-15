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
	case VID_T:
	case INL_T:
	case FPL_T:
	case STR_T:
	case LPR_T:
	case RPR_T:
	case LBR_T:
	case RBR_T:
		// TODO: Include the other cases
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
		else
			printf("MATCHED TOKEN!!!!\n");
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
	case VID_T:
		printf("%s\n", t.attribute.vidLexeme);
		break;
	case LPR_T:
	case RPR_T:
	case LBR_T:
	case RBR_T:
		printf("NA\n");
		break;
	//case EOS_T:
	//	printf("NA\n");
	//	break;
	// TODO: Adjust the other cases
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
		printf("%i", lookahead.attribute.codeType);
		matchToken(VID_T, VID_T);
		lookahead = tokenizer();
		if (lookahead.code == VID_T)
		{
			if (strcmp(lookahead.attribute.vidLexeme, "def") == 0)
			{
				lookahead = tokenizer();
				// This is the start of the program
				opt_statements();
				matchToken(RPR_T, NO_ATTR);
				break;
			}
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

/*************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { LPR_T, ϵ }
 ************************************************************/
zz_nul opt_statements()
{ // TODO: Basic implementation
	switch (lookahead.code)
	{
	case LPR_T:
		if (lookahead.attribute.codeType == VID_T)
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
		//if (lookahead.attribute.codeType == WRITE)
		//{
		//	statement();
		//	statementsPrime();
		//	break;
		//}
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
		//case WRITE:
		//	outputStatement();
		//	break;
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
 * Function expression
 * BNF: <function expr> -> <function identifier> <opt_args>
 * FIRST(<function expr>) = { VID_T }
 ************************************************************/
zz_nul functionExpr()
{
	// matchToken(VID_T, ???);
}

/*************************************************************
 * Optional arguments
 * BNF: <opt_args> -> <args> | ϵ
 * FIRST(<opt_args>) = { INL_T, FPL_T, STR_T, VID_T, (, ϵ }
 ************************************************************/
zz_nul opt_args()
{
}

/*************************************************************
 * List of arguments
 * BNF: <args> -> <arg><white space><argsPrime>
 * FIRST(<args>) = { INL_T, FPL_T, STR_T, VID_T, ( }
 ************************************************************/
zz_nul args()
{
}

/*************************************************************
 * List of arguments (prime)
 * BNF: <argsPrime> -> <arg><white space><argsPrime> | ϵ
 * FIRST(<argsPrime>) = { INL_T, FPL_T, STR_T, VID_T, (, ϵ }
 ************************************************************/
zz_nul argsPrime()
{
}

/*************************************************************
 * Single argument
 * BNF: <arg> -> <integer literal>
 *				 | <float literal>
 *				 | <string literal>
 *				 | <variable identifier>
 *				 | (<function expr>)
 * FIRST(<arg>) = { INL_T, FPL_T, STR_T, VID_T, ( }
 ************************************************************/
zz_nul arg()
{
}
